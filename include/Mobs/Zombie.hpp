//
// Zombie.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat May 21 14:14:46 2016 Antoine Lempereur
// Last update Sat Jun  4 20:46:17 2016 Antoine Lempereur
//

#ifndef ZOMBIE_HPP_
#define ZOMBIE_HPP_

#define ZOMBIE_MAX_HP 100
#define ZOMBIE_MAX_MANA 0
#define ZOMBIE_ATTACK_DMG 10
#define ZOMBIE_ATTACK_SPEED 1.5 // = 2 coup par seconde
#define ZOMBIE_ATTACK_RANGE 75
#define ZOMBIE_PATHNAME "northrendskeletonmale.mesh"

#include	"CollisionSingleton.hpp"
#include	"ANonPlayable.hpp"

class Zombie : public ANonPlayable
{
public:
  Zombie();
  virtual ~Zombie();

  // A implementer dans la classe NPC, entre ACharacter et Zombie
  void	initGfx(Ogre::SceneManager*, Ogre::SceneNode*, Ogre::Vector3 const&);
  // private:
  void	attack(bool);
  void	update(double);
};

#endif /* end of include guard: ZOMBIE_HPP_ */
