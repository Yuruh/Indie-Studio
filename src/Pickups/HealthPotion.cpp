//
// HealthPotion.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Fri Jun  3 21:37:59 2016 Corentin Descamps
// Last update Sun Jun  5 19:33:36 2016 Antoine Lempereur
//

#include	"Pickups/HealthPotion.hpp"

HealthPotion::HealthPotion()
{
  this->_value = 15;
}

HealthPotion::HealthPotion(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  this->_value = 15;
  this->_entity = sceneManager->createEntity("Flask.mesh");
  this->_entity->setQueryFlags(PICKUP);
  CollisionSingleton::getInstance().addEntity(this);
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 50, 50));
  this->_audio.loadSound("Potion", "media/audio/sound/Potion.ogg");
}

HealthPotion::~HealthPotion()
{

}

void		HealthPotion::applyEffect(Player& player)
{
  player.addHp(this->_value);
  this->_audio.playSound("Potion");
}
