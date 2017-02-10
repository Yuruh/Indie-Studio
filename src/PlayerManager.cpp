//
// PlayerManager.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Tue May 24 13:45:43 2016 Martin Desrumaux
// Last update Sun Jun 05 03:25:01 2016 Martin Desrumaux
//

#include	"PlayerManager.hpp"

static Player		*CreatePlayerWarrior(const Controller &type)
{
  return (new Warrior(type));
}

static Player		*CreatePlayerValkyrie(const Controller &type)
{
  return (new Valkyrie(type));
}

static Player		*CreatePlayerElf(const Controller &type)
{
  return (new Elf(type));
}

static Player		*CreatePlayerMage(const Controller &type)
{
  return (new Mage(type));
}


PlayerFactory::PlayerFactory()
{
  funcs[WARRIOR] = &CreatePlayerWarrior;
  funcs[ARCHER] = &CreatePlayerElf;
  funcs[MAGE] = &CreatePlayerMage;
  funcs[VALKYRIE] = &CreatePlayerValkyrie;
}

//TODO const ptr
Player		*PlayerFactory::create(const ControllerPlayer &type)
{
  auto existing = this->funcs.find(type.player);
  if (existing == this->funcs.end())
    return (NULL);
  return (existing->second(*type.controller));
}

PlayerManager::PlayerManager(std::vector<ControllerPlayer> &cPlayers)
{
  Player *tmp;

  for (auto it = cPlayers.begin(); it != cPlayers.end(); ++it)
  {
    tmp = this->_playerFactory.create((*it));
    if (tmp != NULL)
      this->_players[(*it).player] = tmp;
  }
}

PlayerManager::~PlayerManager()
{
}

bool		PlayerManager::areAllDead() const
{
  for (auto it = _players.begin(); it != _players.end(); it++)
    if (!it->second->isDead())
      return (false);
  return (true);
}

void	PlayerManager::placePlayers(Ogre::Vector3 const& roomPos, Cardinal dir)
{
  double	x = 0;
  double	z = 0;
  double	offsetX = 0;
  double	offsetZ = 0;

  if (dir == NORTH)
    z = -400;
  if (dir == SOUTH)
    z = 400;
  if (dir == WEST)
    x = -400;
  if (dir == EAST)
    x = 400;
  if (dir == NORTH || dir == SOUTH || dir == UNDEFINED)
    offsetX = 40;
  if (dir == WEST || dir == EAST)
    offsetZ = 40;

  if (this->_players.find(WARRIOR) != this->_players.end())
    this->_players[WARRIOR]->setPosition(Ogre::Vector3(roomPos.x + x + offsetX * -3, 0, roomPos.z + z + offsetZ * -3));
  if (this->_players.find(ARCHER) != this->_players.end())
    this->_players[ARCHER]->setPosition(Ogre::Vector3(roomPos.x + x + offsetX * -1, 0, roomPos.z + z + offsetZ * -1));
  if (this->_players.find(MAGE) != this->_players.end())
    this->_players[MAGE]->setPosition(Ogre::Vector3(roomPos.x + x + offsetX * 3, 0, roomPos.z + z + offsetZ * 3));
  if (this->_players.find(VALKYRIE) != this->_players.end())
    this->_players[VALKYRIE]->setPosition(Ogre::Vector3(roomPos.x + x + offsetX * 1, 0, roomPos.z + z + offsetZ * 1));
}

void			PlayerManager::initGfx(Ogre::SceneManager *sceneManager)
{
  for (auto it = _players.begin(); it != _players.end(); it++)
      {
	it->second->initGfx(sceneManager,
			    sceneManager->getRootSceneNode(),
			    Ogre::Vector3(0, 0, 0));
      }
      this->placePlayers(Ogre::Vector3(0, 0, 0), UNDEFINED);
    //   i += 300;
    //   if (i == 800)
    //
    //  = 0;
    //  += 300;
    //
    // }
}

void			PlayerManager::frameUpdate(float timeSinceLastFrame)
{
  for (auto it = _players.begin(); it != _players.end(); it++)
    {
      it->second->addAnimationTime(timeSinceLastFrame);
      it->second->update(timeSinceLastFrame);
    }
}

const std::map<ClassPlayer, Player*>	&PlayerManager::getMap() const
{
  return (this->_players);
}


Player			*PlayerManager::getPlayer(ClassPlayer player) // pas const sinon compilo aime pas
{
  if (this->_players.find(player) != this->_players.end())
    return (this->_players[player]);
  else
    return (NULL);
}
