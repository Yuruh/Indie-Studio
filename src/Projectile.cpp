//
// Projectile.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu May 26 13:38:13 2016 Antoine Lempereur
// Last update Sun Jun  5 13:20:58 2016 Antoine Lempereur
//

#include "Mobs/ANonPlayable.hpp"
#include "Projectile.hpp"
#include "PlayableClass/Player.hpp"

Projectile::Projectile(double speed, double dmg, double maxRange, Elem *launcher)
{
  this->_speed = speed;
  this->_dmg = dmg;
  this->_range = 0;
  this->_maxRange = maxRange;
  this->_launcher = launcher;
  this->_facingDir = Ogre::Vector3::UNIT_Z;
}

Projectile::~Projectile()
{

}

void		Projectile::setSpeed(double value)
{
  this->_speed = value;
}

void		Projectile::setDamage(double value)
{
  this->_dmg = value;
}

void		Projectile::initDirection()
{
  this->_direction = this->getDirection();
  this->_direction.normalise();
}

void		Projectile::setDirection(Ogre::Vector3 const& dir)
{
  this->_direction = dir;
}

bool		Projectile::update(float timeSinceLastFrame, bool isPlayerShot)
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
      return (false);
    }
  value = this->_direction * this->_speed * timeSinceLastFrame;
  this->_range += value.distance(Ogre::Vector3(0, 0, 0));
  oldPos = this->getPos();
  this->move(value);
  if (isPlayerShot)
    ret = CollisionSingleton::getInstance().check_box_collision(*this, *(this->_launcher), static_cast<QueryFlags>(ENEMY | BLOCKING));
  else
    ret = CollisionSingleton::getInstance().check_box_collision(*this, *(this->_launcher), (QueryFlags)(PLAYER | BLOCKING));
  if (ret.collided && this->_entity->isAttached())
    {
      if ((isPlayerShot == true && (ennemy = dynamic_cast<ANonPlayable*>(ret.elem)) != NULL)
	  || (isPlayerShot == false && (ennemy = dynamic_cast<Player*>(ret.elem)) != NULL))
	{
	  ennemy->takeDamage(this->_dmg);
	  retValue = true;
	}
      this->detachEntity();
      this->_range = 0;
    }
  return (retValue);
}
