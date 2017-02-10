//
// Animation.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon May 23 14:02:44 2016 Antoine Lempereur
// Last update Sun Jun  5 19:09:45 2016 Antoine Lempereur
//

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <string>
#include <OGRE/OgreEntity.h>

#define	TRANSITION_TIME 0.25

class Animation
{
private:
  bool		_isStrong;
  double	_dist;
  double	_speed;
  Ogre::Real	_weight;
  double	_castingTime;
  Ogre::AnimationState	*_animationState;
  std::string	_name;
public:
  Animation(std::string const&, bool, double speed = 1.0, double dist = 0.0, double castingTime = 0.5);
  virtual ~Animation();
  bool		isStrong() const;
  bool		isCasted() const;
  void		addTime(float);
  void 		disable();
  void		setSpeed(double);
  void 		enable();
  const std::string 	&getName() const;
  void		launch(Ogre::Entity*);
  bool		hasEnded() const;
  void		updateWeight(double);
};

#endif /* end of include guard: ANIMATION_HPP_ */
