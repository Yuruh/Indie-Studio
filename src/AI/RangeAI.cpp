//
// RangeAI.cpp for  in /home/wasta-geek/rendu/CPP/cpp_indie_studio
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Thu May 19 17:39:59 2016 Wasta-Geek
// Last update Sat Jun  4 20:10:34 2016 Wasta-Geek
//

#include	"AI/PathFinding.hpp"
#include	"AI/RangeAI.hpp"

RangeAI::RangeAI()
{
}

RangeAI::~RangeAI()
{
}

static void	fillTabPlayer(std::pair<Ogre::Vector3, Player*> (&tab)[4], const PlayerManager *players)
{
  std::map<ClassPlayer, Player*>                _players = players->getMap();
  std::map<ClassPlayer, Player*>::iterator      it = _players.end();

  tab[0].first = (_players.find(WARRIOR) != it) ? _players[WARRIOR]->getPos() : Ogre::Vector3(0, -1, 0);
  tab[0].second = (tab[0].first.y == -1) ? NULL : _players[WARRIOR];
  tab[1].first = (_players.find(ARCHER) != it) ? _players[ARCHER]->getPos() : Ogre::Vector3(0, -1, 0);
  tab[1].second = (tab[1].first.y == -1) ? NULL : _players[ARCHER];
  tab[2].first = (_players.find(MAGE) != it) ? _players[MAGE]->getPos() : Ogre::Vector3(0, -1, 0);
  tab[2].second = (tab[2].first.y == -1) ? NULL : _players[MAGE];
  tab[3].first = (_players.find(VALKYRIE) != it) ? _players[VALKYRIE]->getPos() : Ogre::Vector3(0, -1, 0);
  tab[3].second = (tab[3].first.y == -1) ? NULL : _players[VALKYRIE];
}

void	RangeAI::chooseAction(ACharacter *start, const double &timeSinceLastFrame)
{
  Ogre::Vector3         start_pos = start->getPos();
  double                range = start->getAttackRange();
  unsigned int          counter = -1;
  std::pair<Ogre::Vector3, Player*>             tab[4];

  fillTabPlayer(tab, this->_players);
  start->addTimeSinceAttack(timeSinceLastFrame);
  if (start->hasLaunchedAttack() == true)
    dynamic_cast<ANonPlayable*>(start)->update(timeSinceLastFrame);
  if (this->_players->areAllDead() == true)
    start->launchAnimation(AnimatedElem::IDLE);
  if (start->getHp() == 0 || this->_players->areAllDead() == true)
    return;
  while (++counter < 4 )
    if (tab[counter].second != NULL && tab[counter].second->getHp() > 0
	&& PathFinding::getDistance(start_pos, tab[counter].first) <= range)
      {
	if (start->hasLaunchedAttack() == false && start->getTimeSinceLastAttack() >= 1 / start->getAttackSpeed())
	  {
	    start->rotate(Ogre::Vector3(tab[counter].first.x - start_pos.x, 0, tab[counter].first.z - start_pos.z));
	    dynamic_cast<ANonPlayable*>(start)->attack(timeSinceLastFrame);
	  }
	else if (PathFinding::getDistance(start_pos, tab[counter].second->getPos()) < (4 * start->getAttackRange()) / 5
		 && start->getCurrentAnimation()->isStrong() == false)
	  PathFinding::NextMove(start, PathFinding::getNearPlayer(start_pos, tab), timeSinceLastFrame, false);
	return ;
      }
  PathFinding::NextMove(start, PathFinding::getNearPlayer(start_pos, tab), timeSinceLastFrame, true);
}

RangeAI			*RangeAI::getInstance()
{
  static RangeAI	instance;

  return &instance;
}

void	RangeAI::setPlayers(const PlayerManager *players)
{
  this->_players = players;
}
