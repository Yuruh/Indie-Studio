//
// Warrior.cpp for indie in /home/archie/workspace/C++/cpp_indie_studio/src/PlayableClass/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Wed May 18 22:39:45 2016 Corentin Descamps
// Last update Sun Jun  5 18:01:45 2016 Antoine Lempereur
//

#include	"AI/PlayerAI.hpp"
#include	"PlayableClass/Warrior.hpp"
#include	"Mobs/ANonPlayable.hpp"

Warrior::Warrior(const Controller &controller): Player(controller)
{
  this->setHpMax(250);
  this->setHp(this->getHpMax());
  this->setManaMax(0);
  this->setMana(this->getManaMax());
  this->setAttackDmg(20);
  this->setAttackSpeed(1);
  this->setAttackRange(120);
  this->setManaRegen(0);
  this->setMvtSpeed(300);
  this->_name = "Warrior";
  if (controller.type == IA)
    this->_AI = PlayerAI::getInstance();
}

Warrior::~Warrior()
{

}

void		Warrior::specialAttack(bool launch)
{
  std::vector<t_collide> ret;
  ACharacter	*elem;

  if (launch && this->_state != SPECIALATTACK)
    {
      this->launchAnimation(SPECIALATTACK);
      this->_audio.playSound("Axe_Special");
    }
  if (this->_currentAnimation->isStrong() && this->_state != SPECIALATTACK)
    return;
  if (!this->_hasLaunchedSpec && this->_state == SPECIALATTACK)
    {
      if (this->_currentAnimation->isCasted())
	{
	  this->_hasLaunchedSpec = true;
	  ret = CollisionSingleton::getInstance().check_sphere_collision(*this, this->getPos(), this->_attackRange, ENEMY);
	  if (ret.size() > 0)
	    this->_audio.playSound("Axe_Shot");
          if (this->_entity->isAttached())
	    for (auto it = ret.begin(); it != ret.end(); it++)
	      {
		elem = dynamic_cast<ACharacter*>(it->elem);
		if (elem != NULL)
		  elem->takeDamage(this->_attackDmg / 2);
	      }
	  }
      }
else if (this->_state != SPECIALATTACK)
  this->_hasLaunchedSpec = false;
}

void		Warrior::attack(bool launch)
{
  t_collide	ret;
  ACharacter	*ennemy;
  Ogre::Vector3	dir;

  if (launch && this->_state != ATTACK)
    {
      this->launchAnimation(ATTACK);
      this->_audio.playSound("Axe_Launch");
    }
if (this->_currentAnimation->isStrong() && this->_state != ATTACK)
  return;
if (!this->_hasLaunchedAttack && this->_state == ATTACK)
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
		this->_audio.playSound("Axe_Shot");
	      }
      }
    }
else if (this->_state != ATTACK)
  this->_hasLaunchedAttack = false;
}

void		Warrior::initGfx(Ogre::SceneManager* sceneManager, Ogre::SceneNode *node, Ogre::Vector3 const& pos)
{
  Ogre::Entity *mesh = sceneManager->createEntity("warrior.mesh");
  Ogre::Entity *weapon = sceneManager->createEntity("axe_2h_gorehowl_d_01_hd.mesh");

  mesh->attachObjectToBone("warrior_bone_108", weapon);
  this->setEntity(mesh);
  this->getEntity()->setQueryFlags(PLAYER);
  CollisionSingleton::getInstance().addEntity(this);
  this->setNode(node->createChildSceneNode(), pos, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 150, 50));
  this->_facingDir = Ogre::Vector3::UNIT_X;
  this->_audio.loadSound("Death", "media/audio/sound/Warrior_Death.wav");
  this->_audio.loadSound("Axe_Launch", "media/audio/sound/Axe_Launch.flac");
  this->_audio.loadSound("Axe_Shot", "media/audio/sound/Axe_Shot.flac");
  this->_audio.loadSound("Axe_Special", "media/audio/sound/Axe_Special.wav");
  this->_animations[IDLE] = new Animation("idle", false, 2);
  this->_animations[WALK] = new Animation("run", false, this->_mvtSpeed, 200);
  this->_animations[ATTACK] = new Animation("attack", true, 0.5, 0, 0.2);
  this->_animations[SPECIALATTACK] = new Animation("special", true, 0.4, 0, 0.2);
  this->_animations[DIE] = new Animation("death", true, 2);
  this->_state = WALK;
  this->_currentAnimation = this->_animations[WALK]; // pour l'instant, ne pas mettre les deux meme ici et en dessous
  this->launchAnimation(IDLE);
}

void		Warrior::takeDamage(const double &value)
{
  ACharacter::takeDamage(value);
  static_cast<CEGUI::ProgressBar*>(this->_overlay->getChild("Warrior_hp"))->setProgress(this->_hp / this->_hpMax);
  if (this->_hp == 0)
    {
      this->_overlay->getChild("WarriorImg")->setAlpha(0);
      this->_overlay->getChild("WarriorDeath")->setAlpha(1);
      this->_audio.playSound("Death_Laugh");
    }
}
