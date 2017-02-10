//
// Elf.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May 24 13:36:12 2016 Corentin Descamps
// Last update Tue May 31 17:43:35 2016 Antoine Lempereur
//

#ifndef		ELF_HPP_
# define	ELF_HPP_

# include	"CollisionSingleton.hpp"
# include	"Player.hpp"

class		Elf : public Player
{
private:
  Projectile	_arrow;

  void		launchArrow();
public:
  Elf(const Controller &controller);
  ~Elf();
  void		initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode*, Ogre::Vector3 const&);
  virtual void	update(float);
  void		takeDamage(const double&);
  void		attack(bool);
  void		specialAttack(bool);
};

#endif		/* !ELF_HPP_ */
