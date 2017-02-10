//
// Mage.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May 24 13:37:02 2016 Corentin Descamps
// Last update Thu Jun  2 22:12:55 2016 Antoine Lempereur
//

#ifndef		MAGE_HPP_
# define	MAGE_HPP_

# include	"CollisionSingleton.hpp"
# include	"Player.hpp"

class		Mage : public Player
{
public:
  Mage(const Controller &controller);
  ~Mage();
  void		initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode*, Ogre::Vector3 const&);
  virtual void	update(float);
  void		takeDamage(const double&);
  void		attack(bool);
  void		specialAttack(bool);
private:
  Projectile	_fireball;
  std::vector<Projectile> _rain;

  void		launchFireball();
  void		launchRain();
};

#endif		/* !MAGE_HPP_ */
