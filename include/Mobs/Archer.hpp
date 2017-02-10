//
// Archer.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat May 21 14:14:46 2016 Antoine Lempereur
// Last update Sun Jun  5 18:12:37 2016 Antoine Lempereur
//

#ifndef ARCHER_HPP_
#define ARCHER_HPP_

#define ARCHER_MAX_HP 50
#define ARCHER_MAX_MANA 0
#define ARCHER_ATTACK_DMG 4
#define ARCHER_ATTACK_SPEED 1 // coup / s
#define ARCHER_ATTACK_DIST 800
#define ARCHER_ATTACK_RANGE 400
#define ARCHER_PATHNAME "northrendskeletonmale.mesh"

#include	"CollisionSingleton.hpp"
#include	"ANonPlayable.hpp"
#include	"Projectile.hpp"

class Archer : public ANonPlayable
{
  Projectile	_arrow;
  void		launchArrow();
public:
  Archer();
  virtual ~Archer();

  // A implementer dans la classe NPC, entre ACharacter et Archer
  void	initGfx(Ogre::SceneManager*, Ogre::SceneNode*, Ogre::Vector3 const&);
  // private:x
  void		attack(bool);
  void		update(double);
};

#endif /* end of include guard: ARCHER_HPP_ */
