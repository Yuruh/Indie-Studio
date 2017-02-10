//
// BouncingProjectile.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu Jun  2 16:03:53 2016 Antoine Lempereur
// Last update Thu Jun  2 16:26:38 2016 Antoine Lempereur
//

#ifndef BOUNCING_PROJECTILE_HPP
#define BOUNCING_PROJECTILE_HPP

#include "Projectile.hpp"
#include "Mobs/ANonPlayable.hpp"
#include "PlayableClass/Player.hpp"

class BouncingProjectile : public Projectile
{
private:
  double  _initSpeed;
public:
  BouncingProjectile(double, double, double, Elem*);
  virtual ~BouncingProjectile();
  bool     update(float, bool);

};

#endif /* end of include guard: BOUNCING_PROJECTILE_HPP */
