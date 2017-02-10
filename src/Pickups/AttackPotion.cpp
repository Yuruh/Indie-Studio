//
// AttackPotion.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Sat Jun  4 10:09:19 2016 Corentin Descamps
// Last update Sun Jun  5 19:33:53 2016 Antoine Lempereur
//

#include	"Pickups/AttackPotion.hpp"

AttackPotion::AttackPotion()
{
  this->_value = 4;
}

AttackPotion::AttackPotion(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  this->_value = 4;
  this->_entity = sceneManager->createEntity("Flask3.mesh");
	  this->_entity->setQueryFlags(PICKUP);
  CollisionSingleton::getInstance().addEntity(this);
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 50, 50));
  this->_audio.loadSound("Potion", "media/audio/sound/Potion.ogg");
}

AttackPotion::~AttackPotion()
{

}

void		AttackPotion::applyEffect(Player& player)
{
  player.setAttackDmg(player.getAttackDmg() + this->_value);
  this->_audio.playSound("Potion");
}
