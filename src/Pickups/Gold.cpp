//
// Gold.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/Pickups/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Wed Jun  1 21:33:59 2016 Corentin Descamps
// Last update Sun Jun  5 00:12:40 2016 Antoine Lempereur
//

#include	"Pickups/Gold.hpp"

Gold::Gold()
{
  this->_value = 10;
}

Gold::Gold(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  this->_value = 10;
  this->_entity = sceneManager->createEntity("PotCoin.mesh");
  this->_entity->setQueryFlags(PICKUP);
  CollisionSingleton::getInstance().addEntity(this);
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(90, 0, 0), Ogre::Vector3(50, 50, 50));
  this->_audio.loadSound("Gold", "media/audio/sound/Gold.wav");
}

Gold::~Gold()
{

}

void		Gold::applyEffect(Player& player)
{
  player.addScore(this->_value);
  this->_audio.playSound("Gold");
}
