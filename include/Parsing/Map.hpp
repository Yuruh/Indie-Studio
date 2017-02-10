//
// Map.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed May 18 20:57:50 2016 Antoine Lempereur
// Last update Sun Jun  5 14:02:54 2016 Wasta-Geek
//

#ifndef		MAP_HPP_
# define	MAP_HPP_

# include	<iostream>
# include	<vector>
# include	<map>
# include	"Elem.hpp"
# include	"Light.hpp"
# include	"Mobs/ANonPlayable.hpp"

enum Cardinal {
  NORTH = -2,
  SOUTH = 2,
  UNDEFINED = 0,
  WEST = -1,
  EAST = 1,
};

typedef struct s_plane
{
  Ogre::Entity    *_entity;
  Ogre::SceneNode *_node;
  double          _w;
  double          _h;
  double          _x;
  double          _y;
}              t_plane;

class 		Map
{
  protected:
  std::vector<ANonPlayable*>				_mob;
  std::vector<Elem*>					_map;
  std::vector<Light>					_light;
  std::vector<t_plane> 					                  _plane;
  std::map<Cardinal, std::pair<double, double>> 	_controlPoint;
  std::string			                       _wall;

  public:
  Map();
  ~Map();


  const std::vector<ANonPlayable*>			&getMob() const;
  const std::vector<Elem*>				&getElems() const;
  const std::vector<Light>				&getLight() const;
  const std::vector<t_plane>				&getPlane() const;
  const std::map<Cardinal, std::pair<double, double>>	&getControlPoint() const;
  const std::string					&getWall() const;
  ANonPlayable						*getBoss() const;

  void							deleteMob(ANonPlayable*);
  void							addMob(ANonPlayable*);
  void							addElem(Elem*);
  void							addLight(Light);
  void							addPlane(t_plane);
  void							setControlPoint(std::map<Cardinal, std::pair<double, double>>);
  void							setWall(const std::string&);
  void							detachAllEntity();
  void							attachAllEntity();
  void							reset();
};

#endif		//!MAP_HPP_
