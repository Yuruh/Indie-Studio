//
// BouncingProjectile.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu Jun  2 16:06:47 2016 Antoine Lempereur
// Last update Sun Jun  5 19:07:08 2016 Antoine Lempereur
//

#include "BouncingProjectile.hpp"

BouncingProjectile::BouncingProjectile(double speed, double dmg, double maxRange, Elem *launcher) :
	Projectile(speed, dmg, maxRange, launcher)
{
  this->_initSpeed = speed;
}

BouncingProjectile::~BouncingProjectile()
{

}

bool		BouncingProjectile::update(float timeSinceLastFrame, bool isPlayerShot)
{
  Ogre::Vector3	dir;
  Ogre::Vector3 value;
  ACharacter	*ennemy;
  Ogre::Vector3	oldPos;
  t_collide	ret;
  bool		retValue = false;

  if (this->_range >= this->_maxRange)
    {
      this->detachEntity();
      this->_range = 0;
      this->_speed = this->_initSpeed;
      return (false);
    }
  dir = this->getDirection();
  dir.normalise();
  value = dir * this->_speed * timeSinceLastFrame;
  this->_range += value.distance(Ogre::Vector3(0, 0, 0));
  oldPos = this->getPos();
  this->move(value);
  ret = CollisionSingleton::getInstance().check_box_collision(*this, *(this->_launcher), static_cast<QueryFlags>(ENEMY | BLOCKING));
  if (ret.collided && this->_entity->isAttached())
    {
      if ((isPlayerShot == true && (ennemy = dynamic_cast<ANonPlayable*>(ret.elem)) != NULL)
	  || (isPlayerShot == false && (ennemy = dynamic_cast<Player*>(ret.elem)) != NULL))
	{
	  ennemy->takeDamage(this->_dmg);
	  retValue = true;
          this->detachEntity();
          this->_speed = this->_initSpeed;
          this->_range = 0;
	}
      else
	{
	//   this->move(value * -1);
	  if (abs(this->getPos().x - ret.elem->getPos().x) > abs(this->getPos().z - ret.elem->getPos().z))
	    this->rotate(Ogre::Vector3(dir.x, dir.y, dir.z * -1));
	  else
	    this->rotate(Ogre::Vector3(dir.x * -1, dir.y, dir.z));
	}
    }
  return (retValue);
}
