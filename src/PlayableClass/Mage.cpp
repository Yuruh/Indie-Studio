//
// Mage.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Tue May 24 13:35:46 2016 Corentin Descamps
// Last update Sun Jun  5 18:12:17 2016 Antoine Lempereur
//

#include	"AI/PlayerAI.hpp"
#include	"PlayableClass/Mage.hpp"

Mage::Mage(const Controller &controller) : Player(controller), _fireball(400, 40, 750, this)
{
  this->setHpMax(150);
  this->setHp(this->getHpMax());
  this->setManaMax(0);
  this->setMana(this->getManaMax());
  this->setAttackDmg(50);
  this->setAttackSpeed(10);
  this->setAttackRange(500);
  this->setManaRegen(0);
  this->setMvtSpeed(300);
  this->_name = "Mage";
  if (controller.type == IA)
    this->_AI = PlayerAI::getInstance();
  for (size_t i = 0; i < 4; i++)
    this->_rain.push_back(Projectile(1000, 40, 1200, this));
}

Mage::~Mage()
{

}

void		Mage::launchRain()
{
  unsigned int i = 0;

  if (this->_rain.size() >= 4)
  {
      this->_rain[0].setPosition(Ogre::Vector3(this->getPos().x - 100, 1000, this->getPos().z));
      this->_rain[1].setPosition(Ogre::Vector3(this->getPos().x + 100, 1000, this->getPos().z));
      this->_rain[2].setPosition(Ogre::Vector3(this->getPos().x, 1000, this->getPos().z - 100));
      this->_rain[3].setPosition(Ogre::Vector3(this->getPos().x, 1000, this->getPos().z + 100));
  }
  while (i < this->_rain.size())
    {
      this->_rain[i].attachEntity();
      this->_rain[i].rotate(Ogre::Vector3(0, -1, 0));
      this->_rain[i].initDirection();
      this->_rain[i].setDirection(Ogre::Vector3(0, -1, 0));
      i++;
    }
  this->_audio.playSound("Fireball_Launch");
}

void		Mage::specialAttack(bool launch)
{
  if (launch && this->_rain.size() >= 4 && !this->_rain[0].getEntity()->isAttached()
      && !this->_rain[1].getEntity()->isAttached() && !this->_rain[2].getEntity()->isAttached()
      && !this->_rain[3].getEntity()->isAttached())
    this->launchAnimation(SPECIALATTACK);
  if (this->_currentAnimation->isStrong() && this->_state != SPECIALATTACK)
    return;
  if (!this->_hasLaunchedSpec && !this->_rain[0].getEntity()->isAttached()) // && stuff probably
    {
      if (this->_currentAnimation->isCasted())
	{
	  this->_hasLaunchedSpec = true;
	  for (size_t i = 0; i < this->_rain.size(); i++)
	    this->_rain[i].setDamage(this->_attackDmg / 2);
	  this->launchRain();
	}
    }
}

void		Mage::attack(bool launch)
{
  if (launch && !this->_fireball.getEntity()->isAttached())
    this->launchAnimation(ATTACK);
  if (this->_currentAnimation->isStrong() && this->_state != ATTACK)
    return;
  if (!this->_hasLaunchedAttack && !this->_fireball.getEntity()->isAttached())
    {
      if (this->_currentAnimation->isCasted())
	{
	  this->_hasLaunchedAttack = true;
	  this->_fireball.setDamage(this->_attackDmg);
	  this->launchFireball();
	}
    }
}

void		Mage::launchFireball()
{
  this->_fireball.attachEntity();
  this->_fireball.setPosition(this->getPos() + this->getDirection());
  this->_fireball.rotate(this->getDirection());
  this->_fireball.initDirection();
  this->_audio.playSound("Fireball_Launch");
}

void		Mage::update(float timeSinceLastFrame)
{
  Player::update(timeSinceLastFrame);
  if (this->_fireball.getEntity()->isAttached())
    {
      if (this->_fireball.update(timeSinceLastFrame, true))
	this->_audio.playSound("Fireball_Shot");
    }
  for (size_t i = 0; i < this->_rain.size(); i++) {
      if (this->_rain[i].getEntity()->isAttached())
	{
	  if (this->_rain[i].update(timeSinceLastFrame, true))
	    this->_audio.playSound("Fireball_Shot");
	  this->_rain[i].yaw(Ogre::Degree(rand() % 720 * timeSinceLastFrame));
	  this->_rain[i].getNode()->pitch(Ogre::Degree(rand() % 720 * timeSinceLastFrame));
	  this->_rain[i].getNode()->roll(Ogre::Degree(rand() % 720 * timeSinceLastFrame));
	}
  }
}

void		Mage::takeDamage(const double &value)
{
  ACharacter::takeDamage(value);
  static_cast<CEGUI::ProgressBar*>(this->_overlay->getChild("Mage_hp"))->setProgress(this->_hp / this->_hpMax);
  if (this->_hp == 0)
    {
      this->_overlay->getChild("MageImg")->setAlpha(0);
      this->_overlay->getChild("MageDeath")->setAlpha(1);
      this->_audio.playSound("Death_Laugh");
    }
}

void		Mage::initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, Ogre::Vector3 const& pos)
{
  this->setEntity(sceneManager->createEntity("mage.mesh"));
  this->getEntity()->setQueryFlags(PLAYER);
  CollisionSingleton::getInstance().addEntity(this);
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 150, 50));
  this->_facingDir = Ogre::Vector3::UNIT_X;

  this->_fireball.setEntity(sceneManager->createEntity("Fireball.mesh"));
  this->_fireball.setNode(node->createChildSceneNode(), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(100, 50, 100));
  this->_fireball.detachEntity();
    for (size_t i = 0; i < this->_rain.size(); i++) {
      this->_rain[i].setEntity(sceneManager->createEntity("Fireball.mesh"));
      this->_rain[i].setNode(node->createChildSceneNode(), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(100, 100, 100));
      this->_rain[i].detachEntity();
    }
  this->_audio.loadSound("Fireball_Launch", "media/audio/sound/Fireball_Launch.flac");
  this->_audio.loadSound("Fireball_Shot", "media/audio/sound/Fireball_Shot.flac");
  this->_audio.loadSound("Death", "media/audio/sound/Mage_Death.wav");
  this->_animations[IDLE] = new Animation("idle", false, 2);
  this->_animations[WALK] = new Animation("run", false, this->_mvtSpeed, 125);
  this->_animations[ATTACK] = new Animation("attack", true, 0.5, 0, 0.2);
  this->_animations[SPECIALATTACK] = new Animation("special", true, 0.5, 0, 0.1);
  this->_animations[DIE] = new Animation("death", true, 3);
  this->_state = WALK;
  this->_currentAnimation = this->_animations[WALK]; // pour l'instant, ne pas mettre les deux meme ici et en dessous
  this->launchAnimation(IDLE);
}
