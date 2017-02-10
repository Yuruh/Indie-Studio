//
// Boss.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat May 21 14:14:46 2016 Antoine Lempereur
// Last update Sun Jun  5 14:09:48 2016 Wasta-Geek
//

#ifndef BOSS_HPP_
#define BOSS_HPP_

#include	<GUI.hpp>
#include	"CollisionSingleton.hpp"
#include	"ANonPlayable.hpp"

class Boss : public ANonPlayable
{
  CEGUI::Window	*_overlay;

public:
  Boss();
  virtual ~Boss();

  // A implementer dans la classe NPC, entre ACharacter et Boss
  void	initGfx(Ogre::SceneManager*, Ogre::SceneNode*, Ogre::Vector3 const&);
  // private:
  void	attack(bool);
  void	update(double);
  void	bindOverlay(CEGUI::Window*);
  void	takeDamage(const double&);
};

#endif /* end of include guard: Boss_HPP_ */
