//
// Gauntlet.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed May  4 15:39:58 2016 Antoine Lempereur
// Last update Sun Jun  5 19:17:57 2016 Antoine Lempereur
//

#ifndef		GAUNTLET_HPP_
# define	GAUNTLET_HPP_

# include 	<OGRE/OgreRenderWindow.h>
# include 	<OGRE/OgreEntity.h>
# include 	<OGRE/OgreWindowEventUtilities.h>

# include	"Audio/AudioSystem.hpp"
# include 	"Room.hpp"
# include	"Pickups/PickupFactory.hpp"
# include 	"RoomGenerator.hpp"
# include 	"GUI.hpp"
# include	"CameraManager.hpp"
# include	"PlayerManager.hpp"
# include   	"Parsing/ParserScore.hpp"

class Gauntlet
{

public:
  Gauntlet();
  virtual ~Gauntlet();
  void      	init(CEGUI::GUI *, AudioSystem*, Ogre::SceneManager *, Ogre::RenderWindow *);
  PlayerManager	&getPlayerManager();
  bool      	updateFrame(float);
  void		createPlayers(std::vector<ControllerPlayer> &cPlayers);
  bool		isDefeat() const;
  bool		isVictory() const;
  bool		isBoss() const;
  void		revivePlayers() const;
  void    	writeScore();
  void    	loadScore();
  void		setOverlayBoss();
  void		playVictoryMusic();

private:
  AudioSystem			*_musicSystem;
  Ogre::SceneManager		*_sceneManager;
  CEGUI::GUI			       *_menu;
  ParserScore             _parserScore;
  std::map<std::string, size_t> _mapScore;
  Room                		*_room;
  CameraManager        		*_cameraManager;
  PlayerManager			*_players;
  RoomGenerator       		_rg;
};

#endif		// !GAUNTLER_HPP_
