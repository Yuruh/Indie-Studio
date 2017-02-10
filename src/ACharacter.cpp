//
// ACharacter.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May  3 09:16:29 2016 Corentin Descamps
// Last update Sat Jun  4 02:25:03 2016 Wasta-Geek
//

#include		"ACharacter.hpp"
#include		"AI/IAI.hpp"
#include		"CollisionSingleton.hpp"

ACharacter::ACharacter()
{
  this->_isDead = false;
  this->_hasLaunchedAttack = false;
  this->_timeSinceLastAttack = 0;
  this->_AI = NULL;
}

ACharacter::~ACharacter()
{
}

double			ACharacter::getHp() const
{
  return (this->_hp);
}

double			ACharacter::getHpMax() const
{
  return (this->_hpMax);
}

double			ACharacter::getMana() const
{
  return (this->_mana);
}

double			ACharacter::getManaMax() const
{
  return (this->_manaMax);
}

double			ACharacter::getAttackSpeed() const
{
  return (this->_attackSpeed);
}

double			ACharacter::getAttackDmg() const
{
  return (this->_attackDmg);
}

double			ACharacter::getAttackRange() const
{
  return (this->_attackRange);
}

double			ACharacter::getManaRegen() const
{
  return (this->_manaRegen);
}

double			ACharacter::getMvtSpeed() const
{
  return (this->_mvtSpeed);
}

void			ACharacter::setHp(double hp)
{
  this->_hp = ((hp > this->_hpMax) ? _hpMax : hp);
}

void			ACharacter::setHpMax(double hpMax)
{
  this->_hpMax = hpMax;
}

void			ACharacter::setMana(double mana)
{
  this->_mana = ((mana > this->_manaMax) ? _manaMax : mana);
}

void			ACharacter::setManaMax(double manaMax)
{
  this->_manaMax = manaMax;
}

void			ACharacter::setAttackSpeed(double attackSpeed)
{
  this->_attackSpeed = attackSpeed;
}

void			ACharacter::setAttackDmg(double attackDmg)
{
  this->_attackDmg = attackDmg;
}

void			ACharacter::setAttackRange(double attackRange)
{
  this->_attackRange = attackRange;
}

void			ACharacter::setManaRegen(double manaRegen)
{
  this->_manaRegen = manaRegen;
}

void			ACharacter::setMvtSpeed(double value)
{
  this->_mvtSpeed = value;
}

void			ACharacter::takeDamage(const double &value)
{
  if (this->_hp <= value)
    this->_hp = 0;
  else
    this->_hp -= value;
  if (this->_hp == 0)
    this->die();
}

void			ACharacter::die()
{
  this->_isDead = true;
  this->stopStrongAnim();
  this->_audio.playSound("Death");
  this->launchAnimation(DIE);
  CollisionSingleton::getInstance().removeEntity(this);
}

bool			ACharacter::hasLaunchedAttack() const
{
  return (this->_hasLaunchedAttack);
}

double			ACharacter::getTimeSinceLastAttack() const
{
  return (this->_timeSinceLastAttack);
}

void			ACharacter::addTimeSinceAttack(double timeSinceLastFrame)
{
  this->_timeSinceLastAttack += timeSinceLastFrame;
}

bool			ACharacter::isDead() const
{
  return (this->_isDead);
}

void			ACharacter::resetTimeSinceLastAttack()
{
  this->_timeSinceLastAttack = 0;
}

void			ACharacter::setLaunchedAttack(bool to_set)
{
  this->_hasLaunchedAttack = to_set;
}

IAI const		*ACharacter::getAI() const
{
  return (this->_AI);
}
