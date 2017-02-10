//
// RoomGenerator.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu May 12 17:04:32 2016 Antoine Lempereur
// Last update Sun Jun  5 13:19:02 2016 Raphael Thiebault
//

#ifndef ROOMGENERATOR_HPP
#define ROOMGENERATOR_HPP

#include <queue>
#include <stdlib.h>

#include "Room.hpp"

class RoomGenerator
{
public:
  RoomGenerator();
  virtual ~RoomGenerator();
  Room      *generateRoom(Ogre::SceneManager *sm);
private:
  size_t    _nbRoom;
  void			addTemplate(RoomType, size_t);
  void			loadDir(const std::string &, RoomType);
  std::map<RoomType, std::vector<std::string>>	_templateTypes;
  std::vector<std::pair<RoomType, std::string> >	_roomTemplates;
  Room			*placeRoom(Room *, std::vector<Room *> const&);
};

#endif
