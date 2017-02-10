//
// NonPlayable.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/Mobs/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sun May 22 15:15:56 2016 Antoine Lempereur
// Last update Tue May 31 16:23:07 2016 Wasta-Geek
//

#ifndef A_NON_PLAYABLE_HPP_
#define A_NON_PLAYABLE_HPP_

#include "ACharacter.hpp"

class ANonPlayable : public ACharacter
{
public:
  ANonPlayable();
  virtual ~ANonPlayable();
  virtual void	initGfx(Ogre::SceneManager*, Ogre::SceneNode*, Ogre::Vector3 const&) = 0;
  virtual void	attack(bool) = 0;
  void		ActionAI(const double&);
  virtual void	update(double) = 0;
};

#endif /* NON_PLAYABLE_HPP_ */
