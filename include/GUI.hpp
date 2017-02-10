//
// GUI.hpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Wed May 18 16:59:13 2016 Martin Desrumaux
// Last update Sun Jun  5 04:26:20 2016 Raphael Thiebault
//

#ifndef		GUI_HPP_
# define	GUI_HPP_

# include 	<CEGUI/CEGUI.h>
# include	<CEGUI/RendererModules/Ogre/Renderer.h>
# include	<OGRE/OgreRoot.h>
# include 	<OGRE/OgreRenderWindow.h>
# include 	<OGRE/OgreEntity.h>
# include	<fstream>
# include	<math.h>
# include	"Parsing/ParserConfig.hpp"
# include	"Parsing/ParserScore.hpp"
# include	"PlayerManager.hpp"
# include	"Events/Controller.hpp"
# include 	"AnimatedLayout.hpp"


namespace Display
{
	class Application;
}

namespace CEGUI
{
	enum GUIState
	{
		INTRO,
		MENU,
		CREDIT,
		LOBBY,
		GAME,
		PAUSE,
		END,
	 };

	class 		GUI
	{
	public:
		GUI(Ogre::Root *, Display::Application*);
		~GUI();

		void			initWindowMap();
		void			initAnimatedLayoutMap();
		void			initSound();
		void			initButtons();
		void			initOverlay();
		void			initOptions();
		void			initLobby();
		void			initHighScore();

		void			launchMenu();
		void			backToMenu();

		void			launchLobby();
		void			nextPlayerLobby(struct Controller*);
		void			reloadLobby();
		bool			assignInput(struct Controller*, const std::string&);

		void			toggleOptions();
		void			loadConfig();
		void			applyConfig();
		void			writeConfig() const;
		void			validateOptions();
		void			togglePause();

		void			changeVolume();
		void			changeSon();
		void			changeMusique();

		void			runGame();
		void			quitGame();
		void			bindOverlay(PlayerManager &);

		CEGUI::GUIState getState() const;
		void			setState(CEGUI::GUIState);
		CEGUI::AnimatedLayout* getAnimatedLayout(const std::string&);
      		CEGUI::Window		*getStaticLayout(const std::string&);

	protected:
		Display::Application					*_application;
		ParserConfig							*_parserConfig;
		ParserScore								_parserScore;

		CEGUI::OgreRenderer 					*_renderer;
		CEGUI::Window 							*_rootWindow;
		GUIState								_GUIState;

		std::map<std::string, CEGUI::Window*>	_windowMap;
		std::map<std::string, CEGUI::AnimatedLayout*> _aLayoutMap;
		std::map<std::string, int>			_menuInputIds;
		std::map<std::string, float>			_optionMap;
		std::map<std::string, size_t>			_scoreMap;

		std::vector<struct Controller*>			_playerInput;
		std::vector<std::string>				_selectLobby;
		size_t									_idxLobby;
	};
}

#endif		//!GUI_HPP_
