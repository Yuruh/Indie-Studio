//
// ParserMap.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed May 18 20:58:01 2016 Antoine Lempereur
// Last update Mon May 23 18:27:15 2016 Antoine Lempereur
//

#ifndef		PARSER_MAP_HPP_
# define	PARSER_MAP_HPP_

# include	<map>
# include	<regex>
# include	"AParser.hpp"
# include	"Map.hpp"
# include	"Mobs/MobFactory.hpp"
# include	"CollisionSingleton.hpp"

class ParserMap : public AParser
{

    enum RegexEnum {
      R_WALL,
      R_PLAN,
      R_MOB,
      R_MOB_SCRIPT,
      R_P_CONTROL,
      R_ELEM,
      R_L_DIR,
      R_L_POI,
    };

  typedef void(ParserMap::*ptr)(const std::string&);

  protected:
  Map 									_result;
  std::map<std::string, ptr> 				_fmap;
  std::map<RegexEnum, std::regex> 		_regexMap;
  std::smatch 							_regexMatch;
  Ogre::SceneManager						*_sceneManager;
  Ogre::SceneNode							*_node;
  MobFactory 								*_mobFactory;

  public:
  ParserMap(Ogre::SceneManager*, Ogre::SceneNode*);
  ~ParserMap();

  void	initRegex();
  void	initMobFactory();

  void  parseWall(const std::string&);
  void	parseMob(const std::string&);
  void	parseControlPoint(const std::string&);
  void	parsePlan(const std::string&);
  void	parseElem(const std::string&);
  void	parseDirectionalLight(const std::string&);
  void	parsePointLight(const std::string&);

  void	parseData(std::string);
  void  reset();

  const Map &getMap() const;
  Ogre::SceneNode	*getNode() const;
};

#endif		//!PARSER_MAP_HPP_
