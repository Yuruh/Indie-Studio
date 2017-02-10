//
// Gauntlet.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed May  4 19:58:14 2016 Antoine Lempereur
// Last update Sun Jun  5 15:38:53 2016 Antoine Lempereur
//

#include "Gauntlet.hpp"
#include "AI/MeleeAI.hpp"
#include "AI/RangeAI.hpp"
#include "AI/PlayerAI.hpp"

Gauntlet::Gauntlet()
{
  this->_sceneManager = NULL;
  this->_cameraManager = NULL;
  this->_players = NULL;
  this->_menu = NULL;
  try
  {
    this->_parserScore.parseFile("score/gauntlet.score");
    this->_mapScore = this->_parserScore.getResult();
    this->loadScore();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    this->_mapScore["WARRIOR"] = 0;
    this->_mapScore["ARCHER"] = 0;
    this->_mapScore["MAGE"] = 0;
    this->_mapScore["VALKYRIE"] = 0;
  }
}

Gauntlet::~Gauntlet()
{

}

bool	Gauntlet::isDefeat() const
{
  if (!this->_players || this->_players->areAllDead())
    return (true);
  return (false);
}

bool	Gauntlet::isVictory() const
{
  if (this->_room->getType() == BOSS && this->_room->getMob().size() == 0)
    return (1);
  return (0);
}

bool	Gauntlet::isBoss() const
{
  if (this->_room->getType() == BOSS)
    return (1);
  return (0);
}

void            Gauntlet::loadScore()
{
  std::map<std::string, size_t> defaultScoreMap;

  defaultScoreMap["WARRIOR"] = 0;
  defaultScoreMap["ARCHER"] = 0;
  defaultScoreMap["MAGE"] = 0;
  defaultScoreMap["VALKYRIE"] = 0;
  for (auto it = this->_mapScore.begin(); it != this->_mapScore.end(); it++)
  {
    defaultScoreMap[it->first] = it->second;
  }
}

void		Gauntlet::playVictoryMusic()
{
  this->_musicSystem->loadMusic("media/audio/Victory.wav");
  this->_musicSystem->playMusic();
}

void            Gauntlet::writeScore()
{
  std::ofstream fd("score/gauntlet.score", std::ios::out | std::ios::trunc);
  auto map = this->_players->getMap();

  if (this->_mapScore["WARRIOR"] < map[WARRIOR]->getScore())
    this->_mapScore["WARRIOR"] = map[WARRIOR]->getScore();
  if (map.find(ARCHER) != map.end() && this->_mapScore["ARCHER"] < map[ARCHER]->getScore())
    this->_mapScore["ARCHER"] = map[ARCHER]->getScore();
  if (map.find(MAGE) != map.end() && this->_mapScore["MAGE"] < map[MAGE]->getScore())
    this->_mapScore["MAGE"] = map[MAGE]->getScore();
  if (map.find(VALKYRIE) != map.end() && this->_mapScore["VALKYRIE"] < map[VALKYRIE]->getScore())
    this->_mapScore["VALKYRIE"] = map[VALKYRIE]->getScore();
  if (fd)
  {
    for (auto it = this->_mapScore.begin(); it != this->_mapScore.end(); it++)
    {
      fd << it->first << "=" << it->second << std::endl;
    }
  }
}

bool  Gauntlet::updateFrame(float timeSinceLastFrame)
{
  Room		*newRoom;
  Cardinal	card;

  if (this->_players == NULL)
    return (true);
  if (this->_room->open() == true)
    this->revivePlayers();
  this->_cameraManager->updatePos(timeSinceLastFrame);
  this->_players->frameUpdate(timeSinceLastFrame);
  this->_room->update(timeSinceLastFrame);
  if ((newRoom = this->_room->getNextRoom(this->_players->getMap(), &card)) != NULL)
{
      this->_room->hide(true);
      this->_room = newRoom;
      this->_room->show(true);
      if (this->isBoss() == true)
	{
	  this->_room->setOverlayBoss(this->_menu->getStaticLayout("Overlay")->getChild("Boss_Overlay/Boss_hp"));
	  this->_menu->getStaticLayout("Overlay")->getChild("Boss_Overlay")->setAlpha(1);
	  this->_musicSystem->loadMusic("media/audio/Boss.ogg");
	  this->_musicSystem->playMusic();
	}
      this->_room->close();
      PlayerAI::getInstance()->setRoom(this->_room);
      this->_players->placePlayers(this->_room->getPos(), card);
      this->_cameraManager->setFinalPos(Ogre::Vector3(this->_room->getCameraPos()));
    }
  return (true);
}

// Called by the GUI
void  Gauntlet::createPlayers(std::vector<ControllerPlayer> &cPlayers)
{
  this->_players = new PlayerManager(cPlayers);
  this->_players->initGfx(this->_sceneManager);

  this->_room = this->_rg.generateRoom(this->_sceneManager);
  this->_room->show(true);
  MeleeAI::getInstance()->setPlayers(this->_players);
  RangeAI::getInstance()->setPlayers(this->_players);
  PlayerAI::getInstance()->setRoom(this->_room);
}

void  Gauntlet::init(CEGUI::GUI *gui, AudioSystem *sys,
		     Ogre::SceneManager *sm, Ogre::RenderWindow *win)
{
  this->_sceneManager = sm;
  this->_menu = gui;
  this->_musicSystem = sys;
  PickupFactory::getInstance().init(sm);
  this->_sceneManager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
  // this->_sceneManager->setShadowFarDistance(200);
  this->_cameraManager = new CameraManager(_sceneManager, "MainCam");
  this->_cameraManager->setViewport(*win);
}

PlayerManager	&Gauntlet::getPlayerManager()
{
  return (*this->_players);
}

void	Gauntlet::revivePlayers() const
{
  std::map<ClassPlayer, Player*>	players = this->_players->getMap();

  if (players.find(WARRIOR) != players.end() &&
      (*players.find(WARRIOR)).second->getHp() == 0)
    (*players.find(WARRIOR)).second->reviveMe();
  if (players.find(VALKYRIE) != players.end() &&
      (*players.find(VALKYRIE)).second->getHp() == 0)
    (*players.find(VALKYRIE)).second->reviveMe();
  if (players.find(ARCHER) != players.end() &&
      (*players.find(ARCHER)).second->getHp() == 0)
    (*players.find(ARCHER)).second->reviveMe();
  if (players.find(MAGE) != players.end() &&
      (*players.find(MAGE)).second->getHp() == 0)
    (*players.find(MAGE)).second->reviveMe();
}
