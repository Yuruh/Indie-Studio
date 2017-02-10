//
// AnimatedElem.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon May  2 21:15:15 2016 Antoine Lempereur
// Last update Fri Jun  3 20:14:34 2016 Antoine Lempereur
//

#ifndef ANIMATEDELEM_HPP_
#define ANIMATEDELEM_HPP_

#include "Elem.hpp"
#include "Animation.hpp"

class AnimatedElem : public Elem
{
public:
  enum State { IDLE, WALK, ATTACK, SPECIALATTACK, DIE};
  AnimatedElem();
  virtual ~AnimatedElem ();
  void    	addAnimationTime(float);
  void		launchAnimation(State);
  State		getState() const;
  const  Animation 	*getCurrentAnimation() const;
  void		stopStrongAnim();
protected:
  std::map<State, Animation*>	_animations;
  State				_state;
  Animation*			_currentAnimation;
};

#endif

// TODO: Delete ?
// Ogre::AnimationState		*_animationState;
// Ogre::AnimationStateSet *_set;
