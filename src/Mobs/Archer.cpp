//
// Archer.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/Mobs/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat May 21 14:21:06 2016 Antoine Lempereur
// Last update Sun Jun  5 19:00:58 2016 Antoine Lempereur
//

#include "AI/RangeAI.hpp"
#include "Mobs/Archer.hpp"

Archer::Archer() : _arrow(ARCHER_ATTACK_DIST, ARCHER_ATTACK_DMG, ARCHER_ATTACK_RANGE, this)
{
  this->_hpMax = ARCHER_MAX_HP;
  this->_hp = this->_hpMax;
  this->_manaMax = ARCHER_MAX_MANA;
  this->_mana = this->_manaMax;
  this->_attackSpeed = ARCHER_ATTACK_SPEED;
  this->_attackDmg = ARCHER_ATTACK_DMG;
  this->_attackRange = ARCHER_ATTACK_RANGE;
  this->_mvtSpeed = 150;
  this->_AI = RangeAI::getInstance();
}

Archer::~Archer()
{

}

void	Archer::initGfx(Ogre::SceneManager *sm, Ogre::SceneNode *node, Ogre::Vector3 const& pos)
{
  this->_entity = sm->createEntity(ARCHER_PATHNAME);
  this->getEntity()->setQueryFlags(ENEMY);
  CollisionSingleton::getInstance().addEntity(this);
  this->_facingDir = Ogre::Vector3::UNIT_X;
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(30, 100, 30));
  this->_arrow.setEntity(sm->createEntity("Arrow.mesh"));
  this->_arrow.setNode(sm->getRootSceneNode()->createChildSceneNode(), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(20, 200, 20));
  this->_arrow.setManualScale(Ogre::Vector3(50, 50, 50));
  this->_arrow.detachEntity();
  this->_audio.loadSound("Arrow_Launch", "media/audio/sound/Arrow_Launch.flac");
  this->_audio.loadSound("Arrow_Shot", "media/audio/sound/Arrow_Shot.flac");
  this->_audio.loadSound("Death", "media/audio/sound/Skeleton_Death.wav");
  this->_animations[IDLE] = new Animation("idle", false);
  this->_animations[WALK] = new Animation("walk", false, this->_mvtSpeed, 125);
  this->_animations[ATTACK] = new Animation("bow", true, 0.5, 0, 0.2);
  this->_animations[DIE] = new Animation("death", true, 3);
  this->_currentAnimation = this->_animations[IDLE];
}

void	Archer::attack(bool launch)
{
  if (launch && !this->_arrow.getEntity()->isAttached())
    this->launchAnimation(ATTACK);
  if (!this->_hasLaunchedAttack)
    if (this->_currentAnimation->isCasted())
      {
	this->_timeSinceLastAttack = 0;
  	this->_hasLaunchedAttack = true;
  	this->launchArrow();
      }
}

void	Archer::launchArrow()
{
  this->_arrow.attachEntity();
  this->_arrow.setPosition(this->getPos() + this->getDirection() * 20);
  this->_arrow.rotate(this->getDirection());
  this->_arrow.initDirection();
  this->_audio.playSound("Arrow_Launch");
}

void	Archer::update(double timeSinceLastFrame)
{
  if (this->_arrow.getEntity()->isAttached())
    {
      if (this->_arrow.update(timeSinceLastFrame, false) == true)
	this->_audio.playSound("Arrow_Shot");
      if (this->_arrow.getEntity()->isAttached() == false)
	this->_hasLaunchedAttack = false;
    }
}
