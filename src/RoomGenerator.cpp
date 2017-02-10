//
// RoomGenerator.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu May 12 17:08:54 2016 Antoine Lempereur
// Last update Sun Jun  5 17:51:28 2016 Antoine Lempereur
//

#include	<algorithm>
#include	<dirent.h>
#include	<random>
#include	<chrono>
#include	"Parsing/ParserError.hpp"
#include 	"RoomGenerator.hpp"

RoomGenerator::RoomGenerator()
{
  this->_nbRoom = 20;
  this->loadDir("map/combat/", COMBAT);
  this->loadDir("map/none/", NONE);
  this->loadDir("map/start/", START);
  this->loadDir("map/boss/", BOSS);
}

RoomGenerator::~RoomGenerator()
{
}

void		RoomGenerator::loadDir(const std::string &dirname, RoomType type)
{
  struct dirent	*dir;
  DIR		*dirp;

  if ((dirp = opendir(dirname.c_str())))
    {
      while ((dir = readdir(dirp)))
	{
	  if (dir->d_name[0] != '.')
	    _templateTypes[type].push_back(dirname + std::string(dir->d_name));
	}
    }
}

void		RoomGenerator::addTemplate(RoomType type, size_t nb = 1)
{
  auto		it = _templateTypes.find(type);
  std::string	name;

  if (it != _templateTypes.end() && _templateTypes[type].size() > 0)
    {
      for (size_t i = 0; i < nb; i++)
	_roomTemplates.push_back(std::make_pair(type, _templateTypes[type][rand() % _templateTypes[type].size()]));
    }
  else
    throw ParserError("Not enough map files to use");
}

Room		*RoomGenerator::placeRoom(Room *room, std::vector<Room *> const& placed)
{
  size_t	idx;

  if (placed.empty())
    return (room);
  idx = rand() % placed.size();
  if (!placed[idx]->linkRoom(room))
    this->placeRoom(room, placed);
  return (room);
}

Room		*RoomGenerator::generateRoom(Ogre::SceneManager *sm)
{
  std::vector<Room *>	placed;

  placed.push_back(new Room());
  this->addTemplate(START);
  for (size_t i = 0; i < this->_nbRoom; i++)
    {
      this->addTemplate(((rand() % 10) > 6) ? NONE : COMBAT);
      placed.push_back(this->placeRoom(new Room(), placed));
    }
  placed.push_back(this->placeRoom(new Room(), placed));
  this->addTemplate(BOSS);
  if (_nbRoom)
    shuffle(_roomTemplates.begin() + 1, _roomTemplates.end() - 1,
	    std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
  placed[0]->init(_roomTemplates, sm);
  placed[0]->initPosition(UNDEFINED, Ogre::Vector3(0, 0, 0));
  return (placed[0]);
}
