  //
// Application.hpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed Apr 27 21:23:14 2016 Antoine Lempereur
// Last update Mon May 23 23:02:22 2016 Martin Desrumaux
//

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

# include	<exception>
# include   <sys/time.h>

# include	  <OGRE/OgreRoot.h>
# include 	<OGRE/OgreConfigFile.h>
# include 	<OGRE/OgreException.h>
# include 	<OGRE/OgreRenderWindow.h>
# include 	<OGRE/OgreEntity.h>
# include 	<OGRE/OgreWindowEventUtilities.h>
# include 	<OGRE/OgreMeshManager.h>

// Here we have to tricks to avoid conflicts
// between SDL (X11 ?) and CEGUI :
// typedef Display
// define True
// define False

# define	Status	X11_Status_Conflict_Fix
# define	Display X11_Display_Conflict_Fix
# include	<SDL.h>
# include	<SDL_syswm.h>
# undef		True
# undef		False
# undef		None
# undef		Display
# undef		Status

# include   "Parsing/ParserMap.hpp"
# include	  "Parsing/ParserScore.hpp"
# include 	"Parsing/ParserError.hpp"
# include 	"Gauntlet.hpp"
# include 	"AnimatedElem.hpp"
# include	  "GUI.hpp"
# include	  "Events/Commands.hpp"
# include	  "Events/InputHandler.hpp"
# include   "Audio/AudioSystem.hpp"
# include   "Audio/AudioEffect.hpp"

namespace CEGUI
{
  class GUI;
}

namespace Display
{
  // Herite	de WindowEventListener pour bien shutdown InputSystem,
  //		de FrameListener pour les input mouse et keyboard
  class   Application :
    public Ogre::WindowEventListener,
    public Ogre::FrameListener
  {
  public:
    Application();
    virtual ~Application();
    void  go();
    virtual void windowClosed();

    Ogre::RenderWindow*   getOgreWindow() const;
    Ogre::SceneManager*   getSceneManager() const;
    Gauntlet              &getGauntlet();
    AudioSystem           &getAudioMusic();
    AudioEffect           &getAudioSound();


  private:
    struct timeval      _timeval;
    AudioSystem         _audio;
    AudioEffect         _sound;
    Ogre::RenderWindow  *_ogreWindow;
    SDL_Window          *_sdlWindow;
    Ogre::Root          *_root;
    Ogre::SceneManager  *_sceneManager;
    CEGUI::GUI          *_cegui;
    Gauntlet            _gauntlet;
    bool    _quit;
  
  private:
    void    writeScore();
    void    manageIntro();
    void		initRessources();
    virtual bool	frameRenderingQueued(Ogre::FrameEvent const&);
    void		initInputs();
  };
};

#endif
