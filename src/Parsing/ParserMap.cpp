//
// ParserMap.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue May  3 17:09:12 2016 Antoine Lempereur
// Last update Fri Jun  3 21:54:56 2016 Antoine Lempereur
//

#include	"Parsing/ParserMap.hpp"
#include	"Parsing/ParserError.hpp"
#include	"Pickups/Gold.hpp"
#include	"Room.hpp"

ParserMap::ParserMap(Ogre::SceneManager *sceneManager, Ogre::SceneNode *node) : _sceneManager(sceneManager), _node(node)
{
  this->initRegex();
  this->initMobFactory();
  this->_result.setWall("defaultWall.mesh");
}

ParserMap::~ParserMap()
{
}

void		ParserMap::initRegex()
{
  std::string 	regD;
  std::string 	regFilename;
  std::string 	regCoor;
  std::string 	regPairCoor;

  regD = "((?:-?[0-9]+)|(?:-?[0-9]+[.,][0-9]+))";
  regCoor = regD + "/" + regD + "/" + regD;
  regPairCoor = regD + "/" + regD;
  regFilename = "([a-z0-9A-Z_.\\/-]+)";
  this->_regexMap[R_WALL] = std::regex("^w +" + regFilename + "$");
  this->_regexMap[R_PLAN] = std::regex("^p +" + regFilename + " +" + regPairCoor + " +" + regFilename + " +" + regPairCoor + "$");
  this->_regexMap[R_MOB] = std::regex("^m +" + regFilename + " +" + regCoor + "$");
  this->_regexMap[R_MOB_SCRIPT] = std::regex("mob/" + regFilename + "$");
  this->_regexMap[R_ELEM] = std::regex("^e +" + regFilename + " +" + regCoor + " +" + regCoor + " +" + regCoor + " +" + "([0-2])/(0|1)$");
  this->_regexMap[R_P_CONTROL] = std::regex("^pc +" + regPairCoor + " +" + regPairCoor + " +" + regPairCoor + " +" + regPairCoor + "$");
  this->_regexMap[R_L_DIR] = std::regex("^ld +" + regCoor + " +" + regCoor + " +" + regCoor + " +" + regD);
  this->_regexMap[R_L_POI] = std::regex("^lp +" + regCoor + " +" + regCoor + " +" + regCoor + " +" + regD);
  this->_fmap["p"] = &ParserMap::parsePlan;
  this->_fmap["e"] = &ParserMap::parseElem;
  this->_fmap["m"] = &ParserMap::parseMob;
  this->_fmap["w"] = &ParserMap::parseWall;
  this->_fmap["pc"] = &ParserMap::parseControlPoint;
  this->_fmap["ld"] = &ParserMap::parseDirectionalLight;
  this->_fmap["lp"] = &ParserMap::parsePointLight;
}

// TODO Retirer le ptr
void		ParserMap::initMobFactory()
{
  this->_mobFactory = new MobFactory();
}

void        ParserMap::parseWall(const std::string &value)
{
  std::vector<std::string>	s_elem;

  std::regex_match(value, this->_regexMatch, this->_regexMap[R_WALL]);
  if (this->_regexMatch.size() != 2)
    throw ParserError("The wall line is not correct. l-" + this->toString(this->_nbLine));
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  this->_result.setWall(s_elem[1]);
}

void        ParserMap::parseMob(const std::string &value)
{
  ANonPlayable      *mob;
  std::vector<std::string>  s_elem;
  std::vector<std::string>	s_elem_script;
  std::vector<double>		nb_elem;

  std::regex_match(value, this->_regexMatch, this->_regexMap[R_MOB]);
  if (this->_regexMatch.size() != 5)
    throw ParserError("The mob line is not correct. l-" + this->toString(this->_nbLine));
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  for (auto it = s_elem.begin(); it != s_elem.end(); it++)
    nb_elem.push_back(atof(it->c_str()));
  std::regex_match(s_elem[1], this->_regexMatch, this->_regexMap[R_MOB_SCRIPT]);
  mob = this->_mobFactory->createMob(s_elem[1]);
  Ogre::Vector3	pos(nb_elem[2], nb_elem[3], nb_elem[4]);
  mob->initGfx(this->_sceneManager, this->_node, pos);
  this->_result.addMob(mob);
}

void		ParserMap::parseControlPoint(const std::string &value)
{
  std::vector<std::string>				s_elem;
  std::vector<double>					nb_elem;
  std::map<Cardinal, std::pair<double, double>> 	elem;

  std::regex_match(value, this->_regexMatch, this->_regexMap[R_P_CONTROL]);
  if (this->_regexMatch.size() != 9)
    throw ParserError("The control point line is not correct. l-" + this->toString(this->_nbLine));
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  for (auto it = s_elem.begin(); it != s_elem.end(); it++)
    nb_elem.push_back(atof(it->c_str()));
  elem[Cardinal::NORTH] = std::make_pair(nb_elem[1], nb_elem[2]);
  elem[Cardinal::SOUTH] = std::make_pair(nb_elem[3], nb_elem[4]);
  elem[Cardinal::EAST] = std::make_pair(nb_elem[5], nb_elem[6]);
  elem[Cardinal::WEST] = std::make_pair(nb_elem[7], nb_elem[8]);
  this->_result.setControlPoint(elem);
}

void		ParserMap::parsePlan(const std::string &value)
{
  Ogre::Entity 				*entity;
  Ogre::SceneNode 			*node;
  std::vector<std::string> 	s_elem;
  t_plane						elem;

  std::regex_match(value, this->_regexMatch, this->_regexMap[R_PLAN]);
  if (this->_regexMatch.size() != 7)
    throw ParserError("The plan line is not correct. l-" + this->toString(this->_nbLine));
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  if ((elem._w = atof(s_elem[2].c_str())) <= 0 ||
      (elem._h = atof(s_elem[3].c_str())) <= 0)
    throw ParserError("The width and height have to be positive. l-" + this->toString(this->_nbLine));
  elem._x = atof(s_elem[5].c_str());
  elem._y = atof(s_elem[6].c_str());
  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane(s_elem[1],
						Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
						plane, elem._w, elem._h, 10, 10, true, 1, 5, 5,
						Ogre::Vector3::UNIT_Z);
  entity = this->_sceneManager->createEntity(s_elem[1]);
  node = this->_node->createChildSceneNode();
  node->attachObject(entity);
  entity->setCastShadows(false);
  entity->setMaterialName(s_elem[4]);
  elem._entity = entity;
  elem._node = node;
  this->_result.addPlane(elem);
}

void		ParserMap::parseElem(const std::string &value)
{
  Elem 					*elem;
  std::vector<std::string>		s_elem;
  std::vector<double>			nb_elem;

  std::regex_match(value, this->_regexMatch, this->_regexMap[R_ELEM]);
  if (this->_regexMatch.size() != 13)
    throw ParserError("The elem line is not correct. l-" + this->toString(this->_nbLine));
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_elem.push_back(*it);
  for (auto it = s_elem.begin(); it != s_elem.end(); it++)
    nb_elem.push_back(atof(it->c_str()));
  try
    {
      if (static_cast<BoundingBox>(nb_elem[11]) == PICK)
	elem = new Gold();
      else
	elem = new Elem();
      elem->setEntity(this->_sceneManager->createEntity(s_elem[1]));
    }
  catch (Ogre::Exception &e)
    {
      std::cerr << e.what() << std::endl;
      throw ParserError("Can't find the file " + s_elem[1] + ". l-" + this->toString(this->_nbLine));
    }
  Ogre::Vector3	pos(nb_elem[2], nb_elem[3], nb_elem[4]);
  Ogre::Vector3	rot(nb_elem[5], nb_elem[6], nb_elem[7]);
  Ogre::Vector3	size(nb_elem[8], nb_elem[9], nb_elem[10]);
  elem->setNode(this->_node->createChildSceneNode(), pos, rot, size);
  elem->setCrossing(static_cast<BoundingBox>(nb_elem[11]));
  if (static_cast<BoundingBox>(nb_elem[11]) == TRANS)
    elem->getEntity()->setQueryFlags(NON_BLOCKING);
  else
    elem->getEntity()->setQueryFlags(BLOCKING);
  if (nb_elem[12])
    elem->getEntity()->getMesh()->buildEdgeList();
  this->_result.addElem(elem);
}

//TODO LightFactory
void 				ParserMap::parseDirectionalLight(const std::string &value)
{
  Light 			light;
  std::vector<std::string>	s_light;
  std::vector<double>		nb_light;

  std::regex_match(value, this->_regexMatch, this->_regexMap[R_L_DIR]);
  if (this->_regexMatch.size() != 11)
    throw ParserError("The directional light line is not correct. l-" + this->toString(this->_nbLine));
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_light.push_back(*it);
  for (auto it = s_light.begin(); it != s_light.end(); it++)
    nb_light.push_back(atof(it->c_str()));
  light.setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
  light.setX(nb_light[1]);
  light.setY(nb_light[2]);
  light.setZ(nb_light[3]);
  light.setDr(nb_light[4]);
  light.setDg(nb_light[5]);
  light.setDb(nb_light[6]);
  light.setSr(nb_light[7]);
  light.setSg(nb_light[8]);
  light.setSb(nb_light[9]);
  if (nb_light[10] >= 0)
    light.setRange(nb_light[10]);
  else
    throw ParserError("The range of the light has to be positive. l-" + this->toString(this->_nbLine));
  this->_result.addLight(light);
}

void 		ParserMap::parsePointLight(const std::string &value)
{
  Light 				light;
  std::vector<std::string>	s_light;
  std::vector<double>			nb_light;

  std::regex_match(value, this->_regexMatch, this->_regexMap[R_L_POI]);
  if (this->_regexMatch.size() != 11)
    throw ParserError("The point light line is not correct. l-" + this->toString(this->_nbLine));
  for (auto it = this->_regexMatch.begin(); it != this->_regexMatch.end(); it++)
    s_light.push_back(*it);
  for (auto it = s_light.begin(); it != s_light.end(); it++)
    nb_light.push_back(atof(it->c_str()));
  light.setType(Ogre::Light::LightTypes::LT_POINT);
  light.setX(nb_light[1]);
  light.setY(nb_light[2]);
  light.setZ(nb_light[3]);
  light.setDr(nb_light[4]);
  light.setDg(nb_light[5]);
  light.setDb(nb_light[6]);
  light.setSr(nb_light[7]);
  light.setSg(nb_light[8]);
  light.setSb(nb_light[9]);
  if (nb_light[10] >= 0)
    light.setRange(nb_light[10]);
  else
    throw ParserError("The range of the light has to be positive. l-" + this->toString(this->_nbLine));
  this->_result.addLight(light);
}

void		ParserMap::parseData(std::string line)
{
  std::map<std::string, ptr>::iterator	it;
  std::string								value;

  line = this->trimLine(line);
  if (line.empty() || line[0] == '#')
    return;
  if ((it = this->_fmap.find(this->getFirstWord(line))) != this->_fmap.end())
    (this->*(this->_fmap.find(this->getFirstWord(line))->second))(line);
  else
    std::cout << "INCONNU = " << line << std::endl;
}

const Map 	&ParserMap::getMap() const
{
  return (this->_result);
}

// TODO pour l'instant il est là mais je suis en train de me rendre compte que ce serait plus logique qu'il soit dans map en fait
Ogre::SceneNode	*ParserMap::getNode() const
{
  return (this->_node);
}

void        ParserMap::reset()
{
  this->_result.reset();
}
