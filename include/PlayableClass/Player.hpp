//
// Player.hpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Wed May 18 23:03:22 2016 Martin Desrumaux
// Last update Sun Jun  5 19:18:16 2016 Antoine Lempereur
//

#ifndef		PLAYER_HPP_

# define	PLAYER_HPP_

# include 	<CEGUI/CEGUI.h>
# include 	<OGRE/OgreEntity.h>
# include	"ACharacter.hpp"
# include	"Events/PlayerInputHandler.hpp"
# include	"Projectile.hpp"

class	Player : public ACharacter
{
public:
  Player(const Controller &controller);
  ~Player();
  virtual void	update(float timeSinceLastFrame);
  virtual void	initGfx(Ogre::SceneManager*,
			Ogre::SceneNode*,
			Ogre::Vector3 const&) = 0;
  virtual void	attack(bool) = 0;
  virtual void	specialAttack(bool) = 0;
  virtual void	takeDamage(const double&);
  void		moveInput(const Ogre::Vector3 &rotate, const Ogre::Vector3 &move, bool moving);
  void		reviveMe();
  void		bindOverlay(CEGUI::Window*);
  void		ActionAI(const double&);
  size_t	getScore() const;
  virtual void	setMvtSpeed(double);
  void		addScore(int score);
  void		addHp(int hp);
  std::string const&	getName() const;

protected:
  CEGUI::Window*	_overlay;
  std::string		_name;
  bool			_hasLaunchedSpec;
private:
  PlayerInputHandler	_inputs;
  size_t		_score;
};

#endif		// PLAYER_HPP_
