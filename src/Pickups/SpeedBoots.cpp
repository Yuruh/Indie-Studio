//
// SpeedBoots.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Sun Jun  5 19:00:22 2016 Corentin Descamps
// Last update Sun Jun  5 19:32:51 2016 Antoine Lempereur
//

#include	"Pickups/SpeedBoots.hpp"

SpeedBoots::SpeedBoots()
{
  this->_value = 30;
}

SpeedBoots::SpeedBoots(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  this->_value = 30;
  this->_entity = sceneManager->createEntity("Boots.mesh");
  this->_entity->setQueryFlags(PICKUP);
  CollisionSingleton::getInstance().addEntity(this);
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 100, 50));
}

SpeedBoots::~SpeedBoots()
{

}

void		SpeedBoots::applyEffect(Player& player)
{
  player.setMvtSpeed(player.getMvtSpeed() + this->_value);
}
