//
// Valkyrie.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May 24 13:37:42 2016 Corentin Descamps
// Last update Thu Jun  2 16:20:38 2016 Antoine Lempereur
//

#ifndef		VALKYRIE_HPP_
# define	VALKYRIE_HPP_

# include	"Player.hpp"
# include	"CollisionSingleton.hpp"
# include 	"BouncingProjectile.hpp"

class		Valkyrie : public Player
{
private:
  BouncingProjectile	_shield;

  void			launchShield();
public:
  Valkyrie(const Controller &controller);
  ~Valkyrie();
  void		initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode*, Ogre::Vector3 const&);
  virtual void 	takeDamage(const double&);
  void		specialAttack(bool);
  void		attack(bool);
  void		update(float);
};

#endif		/* !VALKYRIE_HPP_ */
