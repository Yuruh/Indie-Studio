//
// MobFactory.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri May 20 17:07:45 2016 Antoine Lempereur
// Last update Wed Jun  1 21:55:29 2016 Antoine Lempereur
//

#include "Mobs/Archer.hpp"
#include "Mobs/Zombie.hpp"
#include "Mobs/Boss.hpp"
#include "Mobs/MobFactory.hpp"

MobFactory::MobFactory()
{
  this->_fptr["zombie"] = &MobFactory::createZombie;
  this->_fptr["archer"] = &MobFactory::createArcher;
  this->_fptr["boss"] = &MobFactory::createBoss;
}

MobFactory::~MobFactory()
{

}

ANonPlayable*		MobFactory::createZombie()
{
  return (new Zombie());
}

ANonPlayable*		MobFactory::createArcher()
{
  return (new Archer());
}

ANonPlayable*		MobFactory::createBoss()
{
  return (new Boss());
}

ANonPlayable*	MobFactory::createMob(std::string const& id)
{
  if (this->_fptr.find(id) != this->_fptr.end())
    return ((this->*_fptr[id])());
  else
    throw Ogre::Exception(0, "Could not load " + id, "MobFactory");
}
