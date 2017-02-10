//
// CollisionSingleton.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Sat May 21 15:47:40 2016 Corentin Descamps
// Last update Thu Jun  2 20:27:44 2016 Antoine Lempereur
//

#include	"CollisionSingleton.hpp"

CollisionSingleton::CollisionSingleton()
{

}

CollisionSingleton::~CollisionSingleton()
{

}

CollisionSingleton&	CollisionSingleton::getInstance()
{
  static CollisionSingleton	instance;

  return (instance);
}

void			CollisionSingleton::addEntity(Elem *elem)
{
  this->m_elems.push_back(elem);
}

void			CollisionSingleton::removeEntity(Elem *elem)
{
  for (auto it = this->m_elems.begin(); it != this->m_elems.end(); it++)
    {
      if ((*it) == elem)
	{
	  this->m_elems.erase(it);
	  return;
	}
    }
}

t_collide		CollisionSingleton::check_collision(Elem const& self, Ogre::Vector3 const& oldPos, Ogre::Vector3 const& toPoint, QueryFlags flags)
{
  Ogre::AxisAlignedBox	toCheck;
  t_collide		ret;

  ret.collided = false;
  ret.elem = NULL;
  for (auto it = this->m_elems.begin(); it != this->m_elems.end(); it++)
    {
      toCheck = (*it)->getEntity()->getWorldBoundingBox(true);
      // std::cout << (*it)->getEntity()->getQueryFlags() << " " << flags << std::endl;
      if ((*it)->getEntity()->getQueryFlags() & flags
	  && self.getEntity() != (*it)->getEntity()
	  && toCheck.intersects(toPoint))
	{
	  if (!toCheck.intersects(oldPos))
	    {
	      ret.elem = (*it);
	      ret.collided = true;
	      return (ret);
	    }
	}
    }
  return (ret);
}

t_collide			CollisionSingleton::check_ray_collision(Elem const& self, Ogre::Vector3& direction, float range, QueryFlags flags)
{
  Ogre::Ray			ray_query;
  Ogre::AxisAlignedBox		toCheck;
  std::pair<bool, Ogre::Real>	query_result;
  t_collide			ret;

  direction.normalise();
  ray_query.setDirection(direction);
  ray_query.setOrigin(self.getPos());
  ret.collided = false;
  ret.elem = NULL;
  for (auto it = this->m_elems.begin(); it != this->m_elems.end(); it++)
    {
      toCheck = (*it)->getEntity()->getWorldBoundingBox(true);

      query_result = ray_query.intersects(toCheck);
      if ((*it)->getEntity()->getQueryFlags() & flags &&
	  self.getEntity() != (*it)->getEntity() &&
	  query_result.first && query_result.second <= range)
	{
	  ret.collided = true;
	  ret.elem = (*it);
	  return (ret);
	}
    }
  return (ret);
}

t_collide		CollisionSingleton::check_box_collision(Elem const& self, Elem const& ignore, QueryFlags flags)
{
  Ogre::AxisAlignedBox	self_box = self.getEntity()->getWorldBoundingBox(true);
  Ogre::AxisAlignedBox	toCheck;
  t_collide		ret;

  ret.collided = false;
  ret.elem = NULL;
  for (auto it = this->m_elems.begin(); it != this->m_elems.end(); it++)
    {
      toCheck = (*it)->getEntity()->getWorldBoundingBox(true);

      if ((*it)->getEntity()->getQueryFlags() & flags
	  && self.getEntity() != (*it)->getEntity() && ignore.getEntity() != (*it)->getEntity()
	  && toCheck.intersects(self_box))
	{
	  ret.collided = true;
	  ret.elem = (*it);
	  return (ret);
	}
    }
  return (ret);
}

std::vector<t_collide>	CollisionSingleton::check_sphere_collision(Elem const& ignore, Ogre::Vector3 const& position, float radius, QueryFlags flags)
{
  std::vector<t_collide>	ret;
  Ogre::Sphere			sphere(position, radius);
  Ogre::AxisAlignedBox		toCheck;
  t_collide			col;

  for (auto it = this->m_elems.begin(); it != this->m_elems.end(); it++)
    {
      toCheck = (*it)->getEntity()->getWorldBoundingBox(true);

      if ((*it)->getEntity()->getQueryFlags() & flags
	  && ignore.getEntity() != (*it)->getEntity()
	  && toCheck.intersects(sphere))
	{
	  col.collided = true;
	  col.elem = (*it);
	  ret.push_back(col);
	}
    }
  return (ret);
}
