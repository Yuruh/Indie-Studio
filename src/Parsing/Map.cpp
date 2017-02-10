//
// Map.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue May 17 17:21:06 2016 Antoine Lempereur
// Last update Sun Jun  5 22:21:04 2016 Antoine Zanardi
//

#include "Parsing/Map.hpp"
#include "CollisionSingleton.hpp"
#include "Mobs/Boss.hpp"

Map::Map()
{
  this->_controlPoint[Cardinal::NORTH] = std::make_pair(0,0);
  this->_controlPoint[Cardinal::SOUTH] = std::make_pair(0,0);
  this->_controlPoint[Cardinal::EAST] = std::make_pair(0,0);
  this->_controlPoint[Cardinal::WEST] = std::make_pair(0,0);
}

Map::~Map()
{
}

void					Map::detachAllEntity()
{
  for (auto it = this->_mob.begin(); it != this->_mob.end(); it++)
    {
      (*it)->detachEntity();
      CollisionSingleton::getInstance().removeEntity(*it);
    }
  for (auto it = this->_map.begin(); it != this->_map.end(); it++)
    {
      CollisionSingleton::getInstance().removeEntity(*it);
      (*it)->detachEntity();
    }
  for (auto it = this->_plane.begin(); it != this->_plane.end(); it++)
    if (it->_entity->isAttached())
      it->_node->detachObject(it->_entity);
}

void					Map::attachAllEntity()
{
  for (auto it = this->_mob.begin(); it != this->_mob.end(); it++)
      {
	(*it)->attachEntity();
        CollisionSingleton::getInstance().addEntity(*it);
    }
  for (auto it = this->_map.begin(); it != this->_map.end(); it++)
  {
   (*it)->attachEntity();
   if ((*it)->getEntity()->getQueryFlags() != NON_BLOCKING)
	  CollisionSingleton::getInstance().addEntity(*it);
      }
  for (auto it = this->_plane.begin(); it != this->_plane.end(); it++)
    if (!it->_entity->isAttached())
	it->_node->attachObject(it->_entity);
}

const std::vector<ANonPlayable*>	&Map::getMob() const
{
  return (this->_mob);
}

const std::vector<Elem*>		&Map::getElems() const
{
  return (this->_map);
}

const std::vector<Light>		&Map::getLight() const
{
  return (this->_light);
}

const std::vector<t_plane>		&Map::getPlane() const
{
  return (this->_plane);
}

const std::map<Cardinal, std::pair<double, double>>	&Map::getControlPoint() const
{
  return (this->_controlPoint);
}

const std::string				&Map::getWall() const
{
  return (this->_wall);
}

void				Map::addMob(ANonPlayable *mob)
{
  this->_mob.push_back(mob);
}

void				Map::addElem(Elem *elem)
{
  this->_map.push_back(elem);
}

void				Map::addLight(Light light)
{
  this->_light.push_back(light);
}

void				Map::addPlane(t_plane plane)
{
  this->_plane.push_back(plane);
}

void				Map::setControlPoint(std::map<Cardinal, std::pair<double, double>> controlPoint)
{
  this->_controlPoint = controlPoint;
}

void				Map::setWall(const std::string &wall)
{
  this->_wall = wall;
}

void				Map::reset()
{
  this->_mob.clear();
  this->_map.clear();
  this->_light.clear();
  this->_plane.clear();
  this->_wall = "defaultWall.mesh";
}

void	Map::deleteMob(ANonPlayable *to_del)
{
  to_del->detachEntity();
  this->_mob.erase(find(this->_mob.begin(), this->_mob.end(), to_del));
}

ANonPlayable	*Map::getBoss() const
{
  for (auto it = this->_mob.begin(); it != this->_mob.end(); it++)
    {
      if (dynamic_cast<Boss*>(*it) != NULL)
	return (*it);
    }
  return (NULL);
}
