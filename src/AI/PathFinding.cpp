//
// PathFinding.cpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
//
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
//
// Started on  Fri May 20 14:56:35 2016 Wasta-Geek
// Last update Fri Jun  3 17:26:41 2016 Wasta-Geek
//

#include	<algorithm>
#include	"AnimatedElem.hpp"
#include	"CollisionSingleton.hpp"
#include	"math.h"
#include	"AI/PathFinding.hpp"

PathFinding::PathFinding()
{
}

PathFinding::~PathFinding()
{
}

double	PathFinding::getDistance(const Ogre::Vector3 &pos, const Ogre::Vector3 &target)
{
  return (sqrt(pow(target.x - pos.x, 2) + pow(target.z - pos.z, 2)));
}

bool	PathFinding::checkEnd(const std::vector<Ogre::Vector3> &result, const Ogre::Vector3 &end,
			      const double &_mvtspeed, const double &timeSinceLastFrame)
{
  if (PathFinding::getDistance(result[result.size() - 1], end) <= _mvtspeed * timeSinceLastFrame)
    return (true);
  return (false);
}

bool							PathFinding::isInList(const std::vector<link> &list, const Ogre::Vector3 &to_test)
{
  std::vector<PathFinding::link>::const_iterator	it = list.begin();
  std::vector<PathFinding::link>::const_iterator	last = list.end();

  while (it != last)
    {
      if ((*it).pos == to_test)
	return (true);
      it++;
    }
  return (false);
}

static void	checkForANeighbour(std::vector<PathFinding::link> &list,
				   const Ogre::Vector3 &end, const PathFinding::link &actual,
				   Ogre::Vector3 &test, ACharacter *me)
{
  PathFinding::link	tmp;
  Ogre::Vector3		start_pos = me->getPos();

  tmp.pos = test;
  tmp.coutSinceBegin = PathFinding::getDistance(test, actual.pos);
  tmp.coutToEnd = PathFinding::getDistance(test, end);
  tmp.coutSumPrev = tmp.coutToEnd + tmp.coutSinceBegin;
  me->setRelativePos(test);
  // me->rotate(test - actual.pos);
  if (CollisionSingleton::getInstance().check_collision(*me, start_pos, test).collided == false)
    list.push_back(tmp);
  // me->rotate(-(test - actual.pos));
  me->setRelativePos(actual.pos);
}

static void	getBestChoice(const std::vector<PathFinding::link> &opened_list, PathFinding::link &actual,
			      enum PathFinding::move &old_dir)
{
  double	cout;

  if (opened_list.empty() == true)
    return ;
  cout = 0;
  for (auto it = opened_list.begin(); it != opened_list.end(); it++)
    if (cout == 0 || (*it).coutToEnd < cout)
      {
	if ((*it).pos.x > actual.pos.x)
	  old_dir = PathFinding::LEFT;
	else if ((*it).pos.x < actual.pos.x)
	  old_dir = PathFinding::RIGHT;
	else if ((*it).pos.z > actual.pos.z)
	  old_dir = PathFinding::UP;
	else
	  old_dir = PathFinding::DOWN;
	cout = (*it).coutToEnd;
	actual = (*it);	
      }
}

static void			addNeighbours(std::vector<PathFinding::link> &list,
					      PathFinding::link &actual, double unit, const Ogre::Vector3 &end, ACharacter *me)
{
  static PathFinding::move	old_dir = PathFinding::NONE;
  Ogre::Vector3			up = actual.pos;
  Ogre::Vector3			down = actual.pos;
  Ogre::Vector3			left = actual.pos;
  Ogre::Vector3			right = actual.pos;

  up.z += unit;
  down.z -= unit;
  left.x += unit;
  right.x -= unit;
  if (old_dir != PathFinding::DOWN)
    checkForANeighbour(list, end, actual, up, me);
  if (old_dir != PathFinding::UP)
    checkForANeighbour(list, end, actual, down, me);
  if (old_dir != PathFinding::RIGHT)
    checkForANeighbour(list, end, actual, left, me);
  if (old_dir != PathFinding::LEFT)
    checkForANeighbour(list, end, actual, right, me);  
  getBestChoice(list, actual, old_dir);
}

void	PathFinding::MoveObstacle(ACharacter *start, const Ogre::Vector3 &end,
				  double _mvtUnit)
{
  std::vector<link>	list;
  Ogre::Vector3		start_pos = start->getPos();
  link			actual(start_pos, 0, 0, 0);

  list.push_back({start_pos, 0, 0, 0});
  addNeighbours(list, actual, _mvtUnit, end, start);
  start->setRelativePos(actual.pos);
  // start->rotate(actual.pos - start_pos);
}


void		PathFinding::NextMove(ACharacter *start, const Ogre::Vector3 &end,
				      const double &timeSinceLastFrame, bool NearDir)
{
  Ogre::Vector3		start_pos = start->getPos();
  Ogre::Vector3		tmp = (NearDir == true) ? end - start_pos : start_pos - end;

  if (end == start->getPos())
    start->launchAnimation(AnimatedElem::IDLE);
  tmp.normalise();
  tmp *= start->getMvtSpeed() * timeSinceLastFrame;
  start->move(tmp);
  start->rotate(tmp);
  start->launchAnimation(AnimatedElem::WALK);
  if (CollisionSingleton::getInstance().check_collision(*start, start_pos, start_pos + tmp).collided == false)
    return ;
  start->move(-tmp);
  if (NearDir == true)
    PathFinding::MoveObstacle(start, end, start->getMvtSpeed() * timeSinceLastFrame);
}

Ogre::Vector3	PathFinding::getNearPlayer(const Ogre::Vector3& my_pos,
					   const std::pair<Ogre::Vector3, Player*> (&tab)[4])
{
  double        dist[4];
  unsigned int  counter = -1;
  int           min = -1;

  while (++counter < 4)
    if (tab[counter].first.y != -1 && tab[counter].second->getHp())
      dist[counter] = PathFinding::getDistance(my_pos, tab[counter].first);
    else
      dist[counter] = -1;
  counter = 0;
  while (counter < 4)
    {
      if ((min == -1 || dist[min] > dist[counter]) && dist[counter] != -1)
	min = counter;
      counter++;
    }
  if (tab[min].first.y == -1)
    return (my_pos);
  return (tab[min].first);
}

ANonPlayable					*PathFinding::getNearMob(const Ogre::Vector3 &start_pos, const std::vector<ANonPlayable*> &mobs)
{
  std::vector<ANonPlayable*>::const_iterator	it = mobs.begin();
  std::vector<ANonPlayable*>::const_iterator	last = mobs.end();
  ANonPlayable					*result = NULL;
  double					min_dist = -1;

  while (it != last)
    {
      if ((*it)->getHp() > 0 && (min_dist == -1 || PathFinding::getDistance(start_pos, (*it)->getPos()) < min_dist))
	{
	  result = *it;
	  min_dist = PathFinding::getDistance(start_pos, result->getPos());
	}
      it++;
    }
  return (result);
}

bool		PathFinding::checkRay(ACharacter *me, const ACharacter *target)
{
  Ogre::Vector3	original_pos = me->getPos();
  Ogre::Vector3	dir = target->getPos() - original_pos;
  Ogre::Vector3	actual_pos = original_pos;
  Ogre::Vector3	next_pos;

  dir.normalise();
  while (666)
    {
      next_pos = actual_pos + dir;
      if (dynamic_cast<Player*>(CollisionSingleton::getInstance().check_box_collision(*me, *me).elem) != NULL)
      	{
      	  me->setRelativePos(original_pos);
      	  return (true);
      	}
      if (CollisionSingleton::getInstance().check_box_collision(*me, *me).collided == true)
  	{
  	  me->setRelativePos(original_pos);
  	  return (false);
  	}
      me->move(dir);
      actual_pos = me->getPos();
    }
}
