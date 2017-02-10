//
// Zombie.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/Mobs/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat May 21 14:21:06 2016 Antoine Lempereur
// Last update Sun Jun  5 19:00:42 2016 Antoine Lempereur
//

#include "Mobs/Zombie.hpp"
#include "AI/MeleeAI.hpp"

Zombie::Zombie()
{
  this->_hpMax = ZOMBIE_MAX_HP;
  this->_hp = this->_hpMax;
  this->_manaMax = ZOMBIE_MAX_MANA;
  this->_mana = this->_manaMax;
  this->_attackSpeed = ZOMBIE_ATTACK_SPEED;
  this->_attackDmg = ZOMBIE_ATTACK_DMG;
  this->_attackRange = ZOMBIE_ATTACK_RANGE;
  this->_mvtSpeed = 130;
  this->_AI = MeleeAI::getInstance();
}

Zombie::~Zombie()
{

}

void	Zombie::initGfx(Ogre::SceneManager *sm, Ogre::SceneNode *node, Ogre::Vector3 const& pos)
{
  this->_entity = sm->createEntity(ZOMBIE_PATHNAME);
  this->getEntity()->setQueryFlags(ENEMY);
  CollisionSingleton::getInstance().addEntity(this);
  this->_facingDir = Ogre::Vector3::UNIT_X;
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(40, 150, 40));
  this->_animations[IDLE] = new Animation("idle", false);
  this->_animations[WALK] = new Animation("walk", false, this->_mvtSpeed, 125);
  this->_animations[ATTACK] = new Animation("attack", true, 1, 0, 0.5);
  this->_animations[DIE] = new Animation("death", true, 3);
  this->_audio.loadSound("Death", "media/audio/sound/Skeleton_Death.wav");
  this->_currentAnimation = this->_animations[IDLE];
}

void	Zombie::attack(bool launch)
{
  this->launchAnimation(AnimatedElem::ATTACK);
  this->_hasLaunchedAttack = true;
  (void)launch;
}

void	Zombie::update(double timeSinceLastFrame)
{
  (void)timeSinceLastFrame;
}
