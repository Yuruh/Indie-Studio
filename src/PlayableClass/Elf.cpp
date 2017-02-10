//
// Elf.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May 24 13:35:24 2016 Corentin Descamps
// Last update Sun Jun  5 15:17:30 2016 Antoine Lempereur
//

#include	"AI/PlayerAI.hpp"
#include	"PlayableClass/Elf.hpp"

Elf::Elf(const Controller &controller) : Player(controller), _arrow(800, 10, 500, this)
{
  this->setHpMax(100);
  this->setHp(this->getHpMax());
  this->setManaMax(0);
  this->setMana(this->getManaMax());
  this->setAttackDmg(10);
  this->setAttackSpeed(10);
  this->setAttackRange(500);
  this->setManaRegen(0);
  this->setMvtSpeed(300);
  this->_name = "Archer";
  if (controller.type == IA)
    this->_AI = PlayerAI::getInstance();
}

Elf::~Elf()
{

}

void		Elf::specialAttack(bool launch)
{
  if (launch)
    this->launchAnimation(SPECIALATTACK);
  if (!this->_hasLaunchedSpec && this->_state == SPECIALATTACK)
    {
      if (this->_currentAnimation->isCasted())
	{
	  this->_hasLaunchedSpec = true;
	  if (this->_mvtSpeed > 1)
	    {
	      this->_mvtSpeed = 1;
	      this->_arrow.setSpeed(3000);
              this->_arrow.setDamage(this->_attackDmg * 2);
	    }
	  else
	    {
	      this->_mvtSpeed = 300;
	      this->_arrow.setSpeed(800);
	      this->_arrow.setDamage(this->_attackDmg / 2);
	    }
	}
    }
}

void		Elf::launchArrow()
{
  this->_arrow.attachEntity();
  this->_arrow.setPosition(this->getPos() + this->getDirection() // * 10
			   );
  this->_arrow.rotate(this->getDirection());
  this->_arrow.initDirection();
  this->_audio.playSound("Arrow_Launch");
}

void		Elf::update(float timeSinceLastFrame)
{
  Player::update(timeSinceLastFrame);
  if (this->_arrow.getEntity()->isAttached())
    {
      if (this->_arrow.update(timeSinceLastFrame, true))
	this->_audio.playSound("Arrow_Shot");
    }
  else if (this->_state != ATTACK)
    this->_hasLaunchedAttack = false;
}

void		Elf::attack(bool launch)
{
  if (launch && !this->_arrow.getEntity()->isAttached())
    this->launchAnimation(ATTACK);
  if (this->_currentAnimation->isStrong() && this->_state != ATTACK)
    return;
  if (!this->_hasLaunchedAttack && !this->_arrow.getEntity()->isAttached())
    {
      if (this->_currentAnimation->isCasted())
	{
	  this->_hasLaunchedAttack = true;
	  this->launchArrow();
	}
    }
}

void		Elf::takeDamage(const double &value)
{
  ACharacter::takeDamage(value);
  static_cast<CEGUI::ProgressBar*>(this->_overlay->getChild("Archer_hp"))->setProgress(this->_hp / this->_hpMax);
  if (this->_hp == 0)
    {
      this->_overlay->getChild("ArcherImg")->setAlpha(0);
      this->_overlay->getChild("ArcherDeath")->setAlpha(1);
      this->_audio.playSound("Death_Laugh");
    }
}

void		Elf::initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  Ogre::Entity *mesh = sceneManager->createEntity("hunter.mesh");
  Ogre::Entity *weapon = sceneManager->createEntity("bow_1h_hyjal_d_01.mesh");

  mesh->attachObjectToBone("hunter_bone_134", weapon);
  this->setEntity(mesh);
  this->getEntity()->setQueryFlags(PLAYER);
  CollisionSingleton::getInstance().addEntity(this);
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 150, 50));
  this->_arrow.setEntity(sceneManager->createEntity("Arrow.mesh"));
  this->_arrow.setNode(node->createChildSceneNode(), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(30, 30, 30));
  this->_arrow.setManualScale(Ogre::Vector3(50, 50, 50));
  this->_arrow.detachEntity();
  this->_audio.loadSound("Arrow_Launch", "media/audio/sound/Arrow_Launch.flac");
  this->_audio.loadSound("Arrow_Shot", "media/audio/sound/Arrow_Shot.flac");
  this->_audio.loadSound("Death", "media/audio/sound/Archer_Death.wav");
  this->_animations[IDLE] = new Animation("idle", false, 2);
  this->_animations[WALK] = new Animation("run", false, this->_mvtSpeed, 200);
  this->_animations[ATTACK] = new Animation("attack", true, 0.2, 0, 0.1);
  this->_animations[SPECIALATTACK] = new Animation("special", true, 1, 0, 0.5);
  this->_animations[DIE] = new Animation("death", true, 3);
  this->_state = WALK;
  this->_currentAnimation = this->_animations[WALK]; // pour l'instant, ne pas mettre les deux meme ici et en dessous
  this->launchAnimation(IDLE);
}
