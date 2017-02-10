//
// PickupFactory.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Fri Jun  3 17:12:00 2016 Corentin Descamps
// Last update Sun Jun  5 19:25:55 2016 Antoine Lempereur
//

#include	"Pickups/PickupFactory.hpp"

PickupFactory::PickupFactory()
{
  this->_factory.push_back(&PickupFactory::createGold);
  this->_factory.push_back(&PickupFactory::createHealthPot);
  this->_factory.push_back(&PickupFactory::createAttackPot);
  this->_factory.push_back(&PickupFactory::createSpeedBoots);
}

PickupFactory::~PickupFactory()
{

}

PickupFactory&	PickupFactory::getInstance()
{
  static PickupFactory	factory;

  return (factory);
}

void		PickupFactory::init(Ogre::SceneManager *sceneManager)
{
  std::srand(std::time(0));
  this->_sceneManager = sceneManager;
}

Pickup*		PickupFactory::getRandomPickup(Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  int nb = std::rand() % 4;

  return ((this->*_factory[nb])(node, pos));
}

Pickup*		PickupFactory::createGold(Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  return (new Gold(this->_sceneManager, node, pos));
}

Pickup*		PickupFactory::createHealthPot(Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  return (new HealthPotion(this->_sceneManager, node, pos));
}

Pickup*		PickupFactory::createAttackPot(Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  return (new AttackPotion(this->_sceneManager, node, pos));
}

Pickup*		PickupFactory::createSpeedBoots(Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  return (new SpeedBoots(this->_sceneManager, node, pos));
}
