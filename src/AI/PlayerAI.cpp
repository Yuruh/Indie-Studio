//
// PlayerAI.cpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Thu May 19 17:39:59 2016 Wasta-Geek
// Last update Sat Jun  4 20:07:02 2016 Wasta-Geek
//

#include	"AI/PathFinding.hpp"
#include	"AI/PlayerAI.hpp"

PlayerAI::PlayerAI()
{
}

PlayerAI::~PlayerAI()
{
}

void	PlayerAI::chooseAction(ACharacter *start, const double &timeSinceLastFrame)
{
  Ogre::Vector3			start_pos = start->getPos();
  double			range = start->getAttackRange();
  std::vector<ANonPlayable*>	mobs = this->_room->getMob();

  if (mobs.size() == 0 || (mobs.size() == 1 && mobs[0]->getHp() == 0))
    {
      start->launchAnimation(AnimatedElem::IDLE);
      return ;
    }
  ANonPlayable			*target = PathFinding::getNearMob(start_pos, mobs);

  if (target == NULL || target->getHp() <= 0)
    return;
  start->addTimeSinceAttack(timeSinceLastFrame);
  if (PathFinding::getDistance(start_pos, target->getPos()) <= range)
    {
      if (start->hasLaunchedAttack() == false && start->getTimeSinceLastAttack() >= 1 / start->getAttackSpeed())
	{
	  start->rotate(target->getPos() - start_pos);
	  dynamic_cast<Player*>(start)->attack(true);
	  return;
	}
    }
  if (start->getCurrentAnimation()->isStrong() == false)
    PathFinding::NextMove(start, target->getPos(), timeSinceLastFrame, true);
}

PlayerAI		*PlayerAI::getInstance()
{
  static PlayerAI	instance;

  return (&instance);
}

void	PlayerAI::setRoom(const Room *room)
{
  this->_room = room;
}
