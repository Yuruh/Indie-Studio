//
// Room.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu May 12 17:04:13 2016 Antoine Lempereur
// Last update Sun Jun  5 19:44:54 2016 Antoine Lempereur
//

#include "AI/PlayerAI.hpp"
#include "Room.hpp"

size_t Room::_globalId = 0;

Room::Room()
{
  this->_links[NORTH] = NULL;
  this->_links[SOUTH] = NULL;
  this->_links[EAST] = NULL;
  this->_links[WEST] = NULL;
  this->_state = NO_INIT;
  this->_id = this->_globalId;
  this->_globalId++;
}

bool  Room::linkRoom(Room *room)
{
  size_t  idx;

  std::vector<Cardinal> available;
  std::map<Cardinal, Room*>::iterator it = this->_links.begin();
  while (it != this->_links.end())
  {
    if (it->second == NULL)
      available.push_back(it->first);
    it++;
  }
  if (available.empty())
    return (false);
  idx = rand() % available.size();
  this->_links[available[idx]] = room;
  room->_links[static_cast<Cardinal>(available[idx] * -1)] = this;
  return (true);
}

void	Room::close()
{
  if (this->_state != CLEARED)
    {
      for (auto it = _doors.begin(); it != _doors.end(); it++)
	{
	  (*it)->attachEntity();
	  CollisionSingleton::getInstance().addEntity(*it);
	}
    }
}

bool	Room::open()
{
  if (this->_state != CLEARED && this->getMob().size() == 0)
    {
      this->_state = CLEARED;
      if (this->_type != BOSS)
	for (auto it = _doors.begin(); it != _doors.end(); it++)
	  {
	    (*it)->detachEntity();
	    CollisionSingleton::getInstance().removeEntity(*it);
	  }
      return (true);
    }
  return (false);
}

void	Room::show(bool doRecurse)
{
  this->_map.attachAllEntity();
  for (auto it = _walls.begin(); it != _walls.end(); it++)
    {
      (*it)->attachEntity();
      CollisionSingleton::getInstance().addEntity(*it);
    }
  for (auto it = this->_links.begin(); it != this->_links.end(); it++)
    {
      if (it->first != SOUTH && it->second != NULL && doRecurse)
	it->second->show(false);
    }
}

void	Room::hide(bool doRecurse)
{
  this->_map.detachAllEntity();
  for (auto it = _walls.begin(); it != _walls.end(); it++)
    {
      (*it)->detachEntity();
      CollisionSingleton::getInstance().removeEntity(*it);
    }
  for (auto it = this->_links.begin(); it != this->_links.end(); it++)
    {
      if (it->first != SOUTH && it->second != NULL && doRecurse)
	it->second->hide(false);
  }
}

//C'est un peu dégueu mais rush oblige
bool	Room::isBossRoomOver() const
{
  ANonPlayable *boss;
  for (auto it = this->getMob().begin(); it != this->getMob().end(); it++)
    if ((boss = dynamic_cast<Boss*>(*it)) != NULL && boss->isDead())
      return (true);
  return (false);
}

void	Room::addWall(Ogre::SceneManager *sm, const std::string &mesh,
		      const Ogre::Vector3 &pos, const Ogre::Vector3 &scale,
		      const Ogre::Vector3 rot = {0, 0, 0})
{
  _walls.push_back(new Elem());
  _walls.back()->setEntity(sm->createEntity(mesh));
  CollisionSingleton::getInstance().addEntity(_walls.back());
  _walls.back()->getEntity()->setQueryFlags(BLOCKING);
  _walls.back()->setNode(this->_node->createChildSceneNode(), pos,
	      rot, Ogre::Vector3(1, 1, 1));
  _walls.back()->setManualScale(scale);
}

void	Room::addDoor(Ogre::SceneManager *sm, const std::string &mesh,
		      const Ogre::Vector3 &pos, const Ogre::Vector3 &scale,
		      const Ogre::Vector3 rot = {0, 0, 0})
{
  _doors.push_back(new Elem());
  _doors.back()->setEntity(sm->createEntity(mesh));
  _doors.back()->getEntity()->setQueryFlags(BLOCKING);
  _doors.back()->setNode(this->_node->createChildSceneNode(), pos,
	      rot, Ogre::Vector3(1, 1, 1));
  _doors.back()->setManualScale(scale);
  _doors.back()->detachEntity();
}

void  Room::init(std::vector<std::pair<RoomType, std::string>> &templateNames,
		 Ogre::SceneManager *sm)
{
  ParserMap	parser(sm, sm->getRootSceneNode()->createChildSceneNode());

  parser.parseFile(std::get<1>(templateNames.front()));

  this->_type = std::get<0>(templateNames.front());
  this->_state = NO_POS;
  this->_map = parser.getMap();
  this->_node = parser.getNode();

  templateNames.erase(templateNames.begin());

  std::vector<Light> lights = this->_map.getLight();
  // std::vector<t_plane> planes = map.getPlane();
  std::vector<Ogre::Light*> l;

  // ça faudrait soit le faire directement dans le parsing, soit faire pareil pour tout
  for (size_t i = 0; i < lights.size(); i++) {
      Ogre::Light *pointLight = sm->createLight("light" + std::to_string(i) + std::to_string(this->_id));
      pointLight->setType(lights[i].getType());
      pointLight->setPosition(lights[i].getPos());
      pointLight->setDirection(lights[i].getPos());
      pointLight->setDiffuseColour(lights[i].getDiff());
      pointLight->setSpecularColour(lights[i].getSpec());
    // pointLight->setAttenuation(65, 1.0, 0.07, 0.017);
      l.push_back(pointLight);
  }


  if (_links[WEST])
    {
	this->addWall(sm, "Wall.mesh", Ogre::Vector3(WALL_X, WALL_Y, WALL_Z + 55),
		      Ogre::Vector3(WALL_W, WALL_H, WALL_L));
	this->addWall(sm, "Wall.mesh", Ogre::Vector3(WALL_X, WALL_Y, -WALL_Z + 55),
		      Ogre::Vector3(WALL_W, WALL_H, WALL_L));
	this->addDoor(sm, "6du_highmaulraid_door02.mesh", Ogre::Vector3(500, -30, -12),
		      Ogre::Vector3(WALL_W, WALL_H, DOOR_L));
    }
  else
    {
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(WALL_X + 25, WALL_Y, 110),
		    Ogre::Vector3(WALL_W * 2, WALL_H, 1100));
    }
  if (_links[EAST])
      {
	this->addWall(sm, "Wall.mesh", Ogre::Vector3(-WALL_X, WALL_Y, WALL_Z + 55),
		      Ogre::Vector3(WALL_W, WALL_H, WALL_L));
	this->addWall(sm, "Wall.mesh", Ogre::Vector3(-WALL_X, WALL_Y, -WALL_Z + 55),
		      Ogre::Vector3(WALL_W, WALL_H, WALL_L));
	this->addDoor(sm, "6du_highmaulraid_door02.mesh", Ogre::Vector3(-500, -30, -12),
		      Ogre::Vector3(WALL_W, WALL_H, DOOR_L));
    }
  else
    {
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(-WALL_X - 25, WALL_Y, 110),
		    Ogre::Vector3(WALL_W * 2, WALL_H, 1000));
    }
  if (_links[NORTH])
    {
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(WALL_Z + 55, WALL_Y, WALL_X),
		    Ogre::Vector3(WALL_W, WALL_H, WALL_L),
		    Ogre::Vector3(0, 90, 0));
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(-WALL_Z + 55, WALL_Y, WALL_X),
		    Ogre::Vector3(WALL_W, WALL_H, WALL_L),
		    Ogre::Vector3(0, 90, 0));
	this->addDoor(sm, "6du_highmaulraid_door02.mesh", Ogre::Vector3(0, -30, 500),
		      Ogre::Vector3(WALL_W, WALL_H, DOOR_L),
                      Ogre::Vector3(0, 90, 0));
    }
  else
    {
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(110, WALL_Y, WALL_X + 25),
		    Ogre::Vector3(WALL_W * 2, WALL_H, 1000),
		    Ogre::Vector3(0, 90, 0));
    }
  if (_links[SOUTH])
    {
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(-WALL_Z + 55, WALL_Y, -WALL_X - 25),
		    Ogre::Vector3(WALL_W * 2, WALL_H, WALL_L),
		    Ogre::Vector3(0, 90, 0));
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(WALL_Z + 55, WALL_Y, -WALL_X - 25),
		    Ogre::Vector3(WALL_W * 2, WALL_H, WALL_L),
		    Ogre::Vector3(0, 90, 0));
	this->addDoor(sm, "6du_highmaulraid_door02.mesh", Ogre::Vector3(0, -30, -500),
		      Ogre::Vector3(WALL_W, WALL_H, DOOR_L),
		      Ogre::Vector3(0, 90, 0));
    }
  else
    {
      this->addWall(sm, "Wall.mesh", Ogre::Vector3(110, WALL_Y, -WALL_X - 25),
		    Ogre::Vector3(WALL_W * 2, WALL_H, 1000),
		    Ogre::Vector3(0, 90, 0));
    }

  this->hide(false);
  std::map<Cardinal, Room*>::iterator it = this->_links.begin();
  while (it != this->_links.end())
  {
    if (it->second != NULL && it->second->_state == NO_INIT)
      it->second->init(templateNames, sm);
    it++;
  }
}

//recursively place node rooms
void  Room::initPosition(Cardinal cardinal, Ogre::Vector3 const& posPrevRoom)
{
  //cardinal correspond à la room precedente

  auto controlPoint = this->_map.getControlPoint();

  if (this->getMob().size() == 0)
      this->_state = CLEARED;
  else
      this->_state = READY;

  if (cardinal == NORTH)
    this->_node->setPosition(posPrevRoom.x, 0, posPrevRoom.z + 1000);
  if (cardinal == SOUTH)
    this->_node->setPosition(posPrevRoom.x, 0, posPrevRoom.z - 1000);
  if (cardinal == WEST)
    this->_node->setPosition(posPrevRoom.x + 1000, 0, posPrevRoom.z);
  if (cardinal == EAST)
    this->_node->setPosition(posPrevRoom.x - 1000, 0, posPrevRoom.z);

  std::map<Cardinal, Room*>::iterator it = this->_links.begin();
  while (it != this->_links.end())
  {
    if (it->second != NULL && it->second->_state == NO_POS)
      it->second->initPosition(it->first, this->_node->getPosition());
    it++;
  }
}

void				Room::update(float timeSinceLastFrame)
{
  std::vector<ANonPlayable*>	mobs = this->_map.getMob();
  std::vector<ANonPlayable*>::iterator	tmp;
  std::vector<ANonPlayable*>	to_delete;

  for (auto it = mobs.begin(); it != mobs.end(); it++)
    {
      if ((*it)->isDead() == true && ((*it)->getCurrentAnimation()->hasEnded() ||
				      (*it)->getState() != AnimatedElem::DIE))
	  {
	    PickupFactory::getInstance().getRandomPickup(this->_node, (*it)->getNode()->getPosition());
	    CollisionSingleton::getInstance().removeEntity(*it);
	    this->_map.deleteMob(*it);
	  }
      else
	{
	  if ((*it)->getHp() > 0)
	    {
	      (*it)->ActionAI(timeSinceLastFrame);
	    }
	  (*it)->addAnimationTime(timeSinceLastFrame);
	}
    }
}

Ogre::Vector3		Room::getCameraPos() const
{
  return (Ogre::Vector3(this->_node->getPosition().x, CAMERA_HEIGHT, this->_node->getPosition().z - TILT_VALUE));
}

Room			*Room::getNextRoom(std::map<ClassPlayer, Player*> const& players, Cardinal *card)
{
  for (auto it = players.begin(); it != players.end(); it++)
    {
      if (it->second->getPos().x > this->_node->getPosition().x + 500)
	{
	  *card = WEST;
	  return (this->_links[WEST]);
	}
      if (it->second->getPos().x < this->_node->getPosition().x - 500)
	{
	  *card = EAST;
	  return (this->_links[EAST]);
	}
      if (it->second->getPos().z > this->_node->getPosition().z + 500)
	{
	  *card = NORTH;
	  return (this->_links[NORTH]);
	}
      if (it->second->getPos().z < this->_node->getPosition().z - 500)
	{
	  *card = SOUTH;
	  return (this->_links[SOUTH]);
	}
    }
  return (NULL);
}

const std::vector<ANonPlayable*>	&Room::getMob() const
{
  return (this->_map.getMob());
}

Ogre::Vector3			Room::getPos() const
{
  return (this->_node->getPosition());
}

RoomType			Room::getType() const
{
  return (this->_type);
}

RoomState			Room::getState() const
{
  return (this->_state);
}

Room::~Room()
{
}

void	Room::setOverlayBoss(CEGUI::Window* overlay)
{
  Boss	*boss = dynamic_cast<Boss*>(this->_map.getBoss());

  if (boss != NULL)
    boss->bindOverlay(overlay);
}
