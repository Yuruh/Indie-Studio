//
// Room.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu May 12 16:59:29 2016 Antoine Lempereur
// Last update Sun Jun  5 14:50:53 2016 Wasta-Geek
//

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include	<string>
#include	<map>
#include	<OGRE/OgreMeshManager.h>
#include	<OGRE/OgreRoot.h>
#include	"Parsing/ParserMap.hpp"
#include 	"Parsing/Map.hpp"
#include	"Mobs/Zombie.hpp"
#include	"Mobs/MobFactory.hpp"
#include	"PlayableClass/Player.hpp"
#include	"CameraManager.hpp"
#include	"Mobs/Boss.hpp"
#include	"Pickups/PickupFactory.hpp"

enum RoomType
{
  START,
  BOSS,
  NONE,
  COMBAT,
  TRAP,
};

enum RoomState
{
  NO_INIT,
  NO_POS,
  READY,
  CLEARED,
};

# define	WALL_L		400
# define	WALL_W		50
# define	WALL_H		300

# define	WALL_X		475
# define	WALL_Y		150
# define	WALL_Z		300

# define	DOOR_L		260

class Room
{
public:
  Room();
  virtual ~Room();
  void  				init(std::vector<std::pair<RoomType, std::string>>&, Ogre::SceneManager *);
  bool  				linkRoom(Room *);
  void					addWall(Ogre::SceneManager *sm, const std::string&, const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3);
  void					addDoor(Ogre::SceneManager *sm, const std::string&, const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3);
  void  				initPosition(Cardinal, Ogre::Vector3 const&);
  void					update(float timeSinceLastFrame);
  const std::vector<ANonPlayable*>	&getMob() const;
  Room					*getNextRoom(std::map<ClassPlayer, Player*> const& players, Cardinal *);
  Ogre::Vector3				getCameraPos() const;
  Ogre::Vector3				getPos() const;
  RoomType				getType() const;
  RoomState				getState() const;
  void					show(bool);
  void					hide(bool);
  void					close();
  bool					open();
  bool					isBossRoomOver() const;
  void					setOverlayBoss(CEGUI::Window*);
private:
  std::map<Cardinal, Room*>  	_links;
  std::vector<Elem*>		_walls;
  std::vector<Elem*>		_doors;
  Ogre::SceneNode       *_node;
  Map                   _map;
  RoomType		_type;
  RoomState		_state;
  static size_t         _globalId;
  size_t                _id;
};

#endif
