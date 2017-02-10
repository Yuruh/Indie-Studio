//
// Warrior.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Wed May 18 22:40:52 2016 Corentin Descamps
// Last update Tue May 31 17:43:54 2016 Antoine Lempereur
//

#ifndef		WARRIOR_HPP_
# define	WARRIOR_HPP_

# include	<OGRE/OgreSceneManager.h>
# include	"PlayableClass/Player.hpp"
# include	"CollisionSingleton.hpp"

class	Warrior : public Player
{
public:
  Warrior(const Controller &controller);
  ~Warrior();

  void		initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode*, Ogre::Vector3 const&);
  virtual void 	takeDamage(const double&);
  void		specialAttack(bool);
  void		attack(bool);
};

#endif		/* !WARRIOR_HPP_ */
