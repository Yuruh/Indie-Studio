//
// ACharacter.hpp for indie in /home/archie/workspace/C++/cpp_indie_studio/include/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May  3 09:23:38 2016 Corentin Descamps
// Last update Sun Jun  5 19:07:41 2016 Antoine Lempereur
//

#ifndef			ACHARACTER_HPP_
# define		ACHARACTER_HPP_

#include		"AnimatedElem.hpp"
#include		"AI/IAI.hpp"
#include		"Audio/AudioEffect.hpp"

class	IAI;

class	ACharacter : public AnimatedElem
{
public:
  ACharacter();
  virtual ~ACharacter();

  double	getHp() const;
  double	getHpMax() const;
  double	getMana() const;
  double	getManaMax() const;
  double	getAttackSpeed() const;
  double	getAttackDmg() const;
  double	getAttackRange() const;
  double	getManaRegen() const;
  double	getMvtSpeed() const;
  double	getTimeSinceLastAttack() const;
  IAI const	*getAI() const;
  bool		IsAttacking() const;
  bool		hasLaunchedAttack() const;
  bool		isDead() const;

  void		setHp(double);
  void		setHpMax(double);
  void		setMana(double);
  void		setManaMax(double);
  void		setAttackSpeed(double);
  void		setAttackDmg(double);
  void		setAttackRange(double);
  void		setManaRegen(double);
  virtual void	setMvtSpeed(double);
  void		resetTimeSinceLastAttack();
  virtual void	takeDamage(const double&);
  virtual void	ActionAI(const double&) = 0;
  virtual void	initGfx(Ogre::SceneManager*, Ogre::SceneNode*, Ogre::Vector3 const&) = 0;
  void		addTimeSinceAttack(double);
  void		die();
  void		setLaunchedAttack(bool);

protected:
  IAI		*_AI;
  double	_hp;
  double	_hpMax;
  double	_mana;
  double	_manaMax;
  double	_mvtSpeed;
  double	_attackSpeed;
  double	_attackDmg;
  double	_attackRange;
  double	_manaRegen;
  bool		_hasLaunchedAttack;
  AudioEffect	_audio;
  double	_timeSinceLastAttack;
  bool		_isDead;
};

#endif			//!ACHARACTER_HPP_
