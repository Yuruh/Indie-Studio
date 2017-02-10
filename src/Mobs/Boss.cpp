//
// Boss.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/Mobs/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat May 21 14:21:06 2016 Antoine Lempereur
// Last update Sun Jun  5 15:45:09 2016 Antoine Lempereur
//

#include "Mobs/Boss.hpp"
#include "AI/MeleeAI.hpp"

Boss::Boss()
{
  this->_hpMax = 3500;
  this->_hp = this->_hpMax;
  this->_manaMax = 100;
  this->_mana = this->_manaMax;
  this->_attackSpeed = 1;
  this->_attackDmg = 30;
  this->_attackRange = 200;
  this->_mvtSpeed = 300;
  this->_AI = MeleeAI::getInstance();
  this->_overlay = NULL;
}

Boss::~Boss()
{

}

void	Boss::initGfx(Ogre::SceneManager *sm, Ogre::SceneNode *node, Ogre::Vector3 const& pos)
{
  this->_entity = sm->createEntity("kelthuzad.mesh");
  this->getEntity()->setQueryFlags(ENEMY);
  CollisionSingleton::getInstance().addEntity(this);
  this->_facingDir = Ogre::Vector3::UNIT_X;
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(30, 600, 30));
  this->_animations[IDLE] = new Animation("idle", false);
  this->_animations[WALK] = new Animation("walk", false, this->_mvtSpeed, 400);
  this->_animations[ATTACK] = new Animation("attack", true, 1, 0, 0.5);
  this->_animations[DIE] = new Animation("death", true, 3);
  this->_currentAnimation = this->_animations[IDLE];
}

void	Boss::attack(bool launch)
{
  this->launchAnimation(AnimatedElem::ATTACK);
  this->_hasLaunchedAttack = true;
  (void)launch;
}

void	Boss::update(double timeSinceLastFrame)
{
  (void)timeSinceLastFrame;
}

void	Boss::bindOverlay(CEGUI::Window *overlay)
{
  this->_overlay = overlay;
}

void	Boss::takeDamage(const double &value)
{
  if (this->_overlay != NULL)
    {
      ACharacter::takeDamage(value);
      static_cast<CEGUI::ProgressBar*>(this->_overlay)->setProgress(this->_hp / this->_hpMax);
    }
}
