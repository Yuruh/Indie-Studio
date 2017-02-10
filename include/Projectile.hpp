//
// Projectile.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu May 26 12:52:52 2016 Antoine Lempereur
// Last update Fri Jun  3 22:34:33 2016 Antoine Lempereur
//

#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "ACharacter.hpp"
#include "CollisionSingleton.hpp"

class Projectile : public Elem
{
protected:
  double	_speed;
  double	_dmg;
  double	_range;
  double	_maxRange;
  Ogre::Vector3	_direction;
  Elem		*_launcher;
public:
  Projectile(double, double, double, Elem *);
  virtual ~Projectile();
  bool		update(float, bool);
  void		initDirection();
  void		setDirection(Ogre::Vector3 const&);
  void		setSpeed(double);
  void		setDamage(double);
};

#endif /* end of include guard: PROJECTILE_HPP_ */
