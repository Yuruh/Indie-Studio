//
// AnimatedElem.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue May  3 10:47:15 2016 Antoine Lempereur
// Last update Fri Jun  3 20:21:58 2016 Antoine Lempereur
//

#include "AnimatedElem.hpp"

AnimatedElem::AnimatedElem() : Elem()
{
  this->_currentAnimation = NULL;
}

AnimatedElem::~AnimatedElem()
{

}

void			AnimatedElem::stopStrongAnim()
{
  if (this->_currentAnimation)
    {
      this->_currentAnimation->disable();
      this->_state = IDLE;
      this->_currentAnimation = this->_animations[IDLE];
      this->_currentAnimation->enable();
    }
}

AnimatedElem::State	AnimatedElem::getState() const
{
  return (this->_state);
}

//TODO : transition fluides
void	AnimatedElem::launchAnimation(State state)
{
  if (this->_currentAnimation && (!this->_currentAnimation->isStrong() ||
				  this->_currentAnimation->hasEnded()) &&
      this->_animations.find(state) != this->_animations.end() &&
      (this->_animations[state]->getName() != this->_currentAnimation->getName()
       || this->_animations.size() == 1))
    {
      this->_animations[state]->launch(this->_entity);
      this->_state = state;
      this->_currentAnimation->disable();
      this->_currentAnimation = this->_animations[state];
      this->_currentAnimation->enable();
    }
}

void    AnimatedElem::addAnimationTime(float t)
{
  if (this->_currentAnimation && this->_currentAnimation->isStrong() &&
      this->_currentAnimation->hasEnded())
    this->launchAnimation(IDLE);

  if (this->_currentAnimation)
    this->_currentAnimation->addTime(t);

  //pour chaque animation, update weight
}

// TODO ATTENTION ptr -->
const Animation  *AnimatedElem::getCurrentAnimation() const
{
  return (this->_currentAnimation);
}
