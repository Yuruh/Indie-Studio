//
// Animation.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon May 23 14:05:00 2016 Antoine Lempereur
// Last update Sun Jun  5 19:10:01 2016 Antoine Lempereur
//

#include "Animation.hpp"

Animation::Animation(std::string const& name, bool isStrong, double speed, double dist, double castingTime)
{
  this->_name = name;
  this->_animationState = NULL;
  this->_isStrong = isStrong;
  this->_dist = dist; //ditance à parcourir en une animation
  this->_speed = speed; // si la distance est 0, la duree de l'animation, sinon correspond à la vitsse du perso
  this->_castingTime = castingTime;
}

Animation::~Animation()
{

}

void	Animation::setSpeed(double value)
    {
      this->_speed = value;
    }

bool	Animation::isStrong() const
{
  return (this->_isStrong);
}

void	Animation::addTime(float t)
{
  if (this->_animationState && this->_speed > 0.000001)
    {
      if (this->_dist > 0.000001)
	this->_animationState->addTime(t * this->_animationState->getLength() / (this->_dist / this->_speed));
      else
	this->_animationState->addTime(t * this->_animationState->getLength() / this->_speed);
    }
}

bool	Animation::isCasted() const
{
  return (this->_animationState->getTimePosition() / this->_animationState->getLength() > this->_castingTime);
}

bool	Animation::hasEnded() const
{
  return (this->_animationState->hasEnded());
}

void	Animation::launch(Ogre::Entity *entity)
{
  if (!this->_animationState)
    this->_animationState = entity->getAnimationState(this->_name);
  else
    this->_animationState->setTimePosition(0);
  this->_animationState->setLoop(!this->_isStrong);
  this->_animationState->setEnabled(true);
}

void 	Animation::enable()
{
  if (this->_animationState)
    this->_animationState->setEnabled(true);
}

void	Animation::updateWeight(double timeSinceLastFrame)
{
  this->_weight += timeSinceLastFrame / TRANSITION_TIME * 100;
  // value =
  // if (this->_animationState)
  // this->_animationState->setWeight()
}

void 	Animation::disable()
{
  if (this->_animationState)
    this->_animationState->setEnabled(false);
}

const std::string	&Animation::getName() const
{
  return (this->_name);
}
