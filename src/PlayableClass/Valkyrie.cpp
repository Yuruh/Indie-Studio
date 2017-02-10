//
// Valkyrie.cpp for idnie in /home/archie/workspace/C++/cpp_indie_studio/src/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May 24 13:35:58 2016 Corentin Descamps
// Last update Sun Jun  5 18:07:31 2016 Antoine Lempereur
//

#include	"AI/PlayerAI.hpp"
#include	"PlayableClass/Valkyrie.hpp"

Valkyrie::Valkyrie(const Controller &controller): Player(controller), _shield(800, 30, 2000, this)
{
  this->setHpMax(100);
  this->setHp(this->getHpMax());
  this->setManaMax(0);
  this->setMana(this->getManaMax());
  this->setAttackDmg(30);
  this->setAttackSpeed(10);
  this->setAttackRange(200);
  this->setManaRegen(0);
  this->setMvtSpeed(300);
  this->_name = "Valkyrie";
  if (controller.type == IA)
    this->_AI = PlayerAI::getInstance();
}

Valkyrie::~Valkyrie()
{

}

void		Valkyrie::launchShield()
{
  this->_shield.attachEntity();
  this->_shield.setPosition(this->getPos());
  this->_shield.rotate(this->getDirection());
  this->_shield.initDirection();
  // this->_audio.playSound("Arrow_Launch");
}

void		Valkyrie::update(float timeSinceLastFrame)
{
  Player::update(timeSinceLastFrame);
  if (this->_shield.getEntity()->isAttached())
    {
      if (this->_shield.update(timeSinceLastFrame, true))
	return ;
      // >_audio.playSound("Arrow_Shot");
    }
}

void		Valkyrie::specialAttack(bool launch)
{
  if (launch && !this->_shield.getEntity()->isAttached())
    this->launchAnimation(SPECIALATTACK);
  if (this->_currentAnimation->isStrong() && this->_state != SPECIALATTACK)
    return;
  if (!this->_hasLaunchedSpec && !this->_shield.getEntity()->isAttached())
    {
      if (this->_currentAnimation->isCasted())
	{
	  this->_hasLaunchedSpec = true;
	  this->launchShield();
	}
    }
}

void		Valkyrie::attack(bool launch)
{
  t_collide	ret;
  ACharacter	*ennemy;
  Ogre::Vector3	dir;

  if (launch && this->_state != ATTACK)
    {
      this->launchAnimation(ATTACK);
      this->_audio.playSound("Sword_Launch");
    }
  if (this->_currentAnimation->isStrong() && this->_state != ATTACK)
    return;
  if (!this->_hasLaunchedAttack)
    {
      if (this->_currentAnimation->isCasted())
	{
	  this->_hasLaunchedAttack = true;
	  dir = this->getDirection();
	  ret = CollisionSingleton::getInstance().check_ray_collision(*this, dir, this->_attackRange);
	  if (ret.collided && this->_entity->isAttached())
	    if ((ennemy = dynamic_cast<ANonPlayable*>(ret.elem)) != NULL)
	      {
		ennemy->takeDamage(this->_attackDmg);
		this->_audio.playSound("Sword_Shot");
	      }
      }
}
}

void		Valkyrie::takeDamage(const double &value)
{
  ACharacter::takeDamage(value);
  static_cast<CEGUI::ProgressBar*>(this->_overlay->getChild("Valkyrie_hp"))->setProgress(this->_hp / this->_hpMax);
  if (this->_hp == 0)
    {
      this->_overlay->getChild("ValkyrieImg")->setAlpha(0);
      this->_overlay->getChild("ValkyrieDeath")->setAlpha(1);
      this->_audio.playSound("Death_Laugh");
    }
}

void		Valkyrie::initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode* sceneNode, Ogre::Vector3 const& pos)
{
Ogre::Entity *weapon = sceneManager->createEntity("polearm_2h_bladed_c_01.mesh");
Ogre::Entity *shield = sceneManager->createEntity("shield_healer_pvp_c_01.mesh");

  this->_entity = sceneManager->createEntity("valkyrie.mesh");
  this->_entity->attachObjectToBone("valkyrie_bone_110", weapon);
  this->_entity->attachObjectToBone("valkyrie_bone_102", shield);

  this->getEntity()->setQueryFlags(PLAYER);
  CollisionSingleton::getInstance().addEntity(this);
  this->_facingDir = Ogre::Vector3::UNIT_X;
  this->_audio.loadSound("Sword_Launch", "media/audio/sound/Sword_Launch.flac");
  this->_audio.loadSound("Sword_Shot", "media/audio/sound/Sword_Shot.flac");
  this->_audio.loadSound("Death", "media/audio/sound/Valkyrie_Death.wav");
  this->_shield.setEntity(sceneManager->createEntity("shield_healer_pvp_c_01.mesh"));
  this->_shield.setNode(sceneNode->createChildSceneNode(), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(30, 50, 30));
  this->_shield.detachEntity();
  this->_animations[IDLE] = new Animation("idle", false, 2);
  this->_animations[WALK] = new Animation("run", false, this->_mvtSpeed, 125);
  this->_animations[ATTACK] = new Animation("attack", true, 0.5, 0, 0.2);
  this->_animations[SPECIALATTACK] = new Animation("special", true, 1, 0, 0.5);
  this->_animations[DIE] = new Animation("death", true, 2);
  this->setNode(sceneNode->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 150, 50));
  this->_state = WALK;
  this->_currentAnimation = this->_animations[WALK];
  this->launchAnimation(IDLE);
}
