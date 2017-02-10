//
// Player.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Wed May 18 23:05:35 2016 Martin Desrumaux
// Last update Sun Jun  5 19:25:14 2016 Antoine Lempereur
//

#include	"PlayableClass/Player.hpp"
#include	"Pickups/Pickup.hpp"

Player::Player(const Controller &controller) : ACharacter(), _inputs(*this, controller)
{
  this->_score = 0;
  this->_audio.loadSound("Revive", "media/audio/sound/Revive.wav");
  this->_audio.loadSound("Death_Laugh", "media/audio/sound/Death.flac");
}

Player::~Player()
{
}

void			Player::setMvtSpeed(double value)
{
  this->_mvtSpeed = value;
  if (this->_animations.find(WALK) != this->_animations.end())
    this->_animations[WALK]->setSpeed(value);
}

void			Player::update(float timeSinceLastFrame)
{
  if (this->_isDead && (this->_currentAnimation->hasEnded() || this->_state != DIE))
    this->detachEntity();
  if (!this->_entity->isAttached())
    return;
  if (this->_AI == NULL)
    this->_inputs.update(timeSinceLastFrame);
  else
    this->_AI->chooseAction(this, timeSinceLastFrame);
  if (this->_state != ATTACK)
    this->_hasLaunchedAttack = false;
  if (this->_state != SPECIALATTACK)
    this->_hasLaunchedSpec = false;

}

void			Player::bindOverlay(CEGUI::Window* overlay)
{
  this->_overlay = overlay;
}

void	Player::ActionAI(const double &timeSinceLastFrame)
{
  this->_AI->chooseAction(this, timeSinceLastFrame);
}

size_t		Player::getScore() const
{
  return (this->_score);
}

void			Player::moveInput(const Ogre::Vector3 &rotate, \
					  const Ogre::Vector3 &move, \
					  bool moving)
{
  Ogre::Vector3		oldPos;
  t_collide 		ret;

  if (this->getCurrentAnimation()->isStrong())
    return;
  oldPos = this->getPos();
  this->rotate(rotate);
  if (this->_mvtSpeed == 1)
    return;
  this->move(move); //TODO: Diminuer distance sur diagonale, utiliser vecteur directeur
  ret = CollisionSingleton::getInstance()
    .check_collision(*this, oldPos, this->getPos());

  if (ret.collided)
    this->move(move * -1);

  ret = CollisionSingleton::getInstance().check_box_collision(*this, *this, PICKUP);
  if (ret.collided)
    {
      Pickup*	pickup;
      if ((pickup = dynamic_cast<Pickup*>(ret.elem)))
	{
	  pickup->applyEffect(*this);
	  CollisionSingleton::getInstance().removeEntity(pickup);
	  pickup->detachEntity();
	}
    }

  if (moving)
    this->launchAnimation(AnimatedElem::WALK);
  else
    this->launchAnimation(AnimatedElem::IDLE);
}

void			Player::addScore(int score)
{
  this->_score += score;
  this->_overlay->getChild(this->_name + "_gold")->setText(std::to_string(this->getScore()));
}

void			Player::addHp(int hp)
{
  this->_hp += this->_hpMax / hp;
  if (this->_hp > this->_hpMax)
    this->_hp = this->_hpMax;
  static_cast<CEGUI::ProgressBar*>(this->_overlay->getChild(this->_name + "_hp"))->setProgress(this->_hp / this->_hpMax);
}

std::string const&	Player::getName() const
{
  return (this->_name);
}

void            Player::reviveMe()
{
  this->_hp = this->_hpMax / 2;
  this->_isDead = false;
  this->attachEntity();
  CollisionSingleton::getInstance().addEntity(this);
  if (dynamic_cast<CEGUI::ProgressBar*>(this->_overlay->getChild(this->_name + "_hp")) != NULL)
    {
      dynamic_cast<CEGUI::ProgressBar*>(this->_overlay->getChild(this->_name + "_hp"))->setProgress(this->_hp / this->_hpMax);
      this->_overlay->getChild(this->_name + "Img")->setAlpha(1);
      this->_overlay->getChild(this->_name + "Death")->setAlpha(0);
      this->_audio.playSound("Revive");
    }
}

void	Player::takeDamage(const double &value)
{
  ACharacter::takeDamage(value);
  this->_audio.playSound("Death_Laugh");
}
