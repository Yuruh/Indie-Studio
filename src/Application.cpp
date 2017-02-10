//
// Application.cpp for  in /home/yuruh/rendu/cpp/cpp_indie_studio/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed Apr 27 21:33:46 2016 Antoine Lempereur
// Last update Sun Jun 05 21:09:21 2016 Martin Desrumaux
//

#include	"Application.hpp"

// TODO  Tout ça dans une classe ? -->
Display::Application::Application()
{
  gettimeofday(&this->_timeval, NULL);
  try
    {
      this->_quit = false;
      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == -1)
	throw std::runtime_error("Failed to init SDL");

      // Create an application window with the following settings:
      this->_sdlWindow = SDL_CreateWindow(
        "An SDL2 window",                  //    window title
        SDL_WINDOWPOS_UNDEFINED,           //    initial x position
        SDL_WINDOWPOS_UNDEFINED,           //    initial y position
        1920,                               //    width, in pixels
        1080,                               //    height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL
      );

      SDL_ShowCursor(SDL_DISABLE);

      // Check that the window was successfully made
      if (this->_sdlWindow == NULL)
      {
	// In the event that the window could not be made...
	std::cerr << "Could not create window: " << SDL_GetError() << '\n';
	// TODO: throw
      }

      Ogre::LogManager * lm = new Ogre::LogManager();
      lm->createLog("Ogre.log", true, false, false);
      this->_root = new Ogre::Root("plugins.cfg", "ogre.cfg", "");
      // TODO: May be managed in plugin.cfg ?
      //this->_root->loadPlugin (std::string("/lib64/OGRE/RenderSystem_GL"));
      this->_root->setRenderSystem(this->_root->getRenderSystemByName("OpenGL Rendering Subsystem"));
      this->initRessources();
      // TODO: A quoi ca sert ? Configuration de la fentre, genre full screen, resolution
      //if (!(this->_root->restoreConfig() || this->_root->showConfigDialog()))
      //throw Ogre::Exception(0, "Could not set root configuration", "Application constructor");
      this->_root->initialise(false);

      //get the native whnd
      struct SDL_SysWMinfo wmInfo;
      SDL_VERSION(&wmInfo.version);

      if (SDL_GetWindowWMInfo(this->_sdlWindow, &wmInfo) == SDL_FALSE)
	throw std::runtime_error("Couldn't get WM Info!");

      Ogre::String winHandle;

      switch (wmInfo.subsystem)
      {
	case SDL_SYSWM_X11:
	  winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.x11.window);
	  break;
	default:
	  throw std::runtime_error("Unexpected WM!");
	  break;
      }
      Ogre::NameValuePairList params;
      params.insert(std::make_pair("title", "OGRE Window"));
      params.insert(std::make_pair("FSAA", "0"));
      params.insert(std::make_pair("vsync", "false"));
      params.insert(std::make_pair("parentWindowHandle",  winHandle));

      this->_ogreWindow = Ogre::Root::getSingleton().createRenderWindow("OGRE Window", 1920, 1080, false, &params);
      this->_ogreWindow->setVisible(true);

      Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
      Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
      this->_cegui = new CEGUI::GUI(this->_root, this);
      this->initInputs();
    }
  catch (Ogre::Exception const& e)
  {
    std::cerr << e.what() << std::endl;
    throw std::exception();
  }
}

Display::Application::~Application()
{
  //delete InputHandler::instance();
  delete this->_cegui;
  this->_root->shutdown();
  delete this->_root;
  SDL_DestroyWindow(this->_sdlWindow);
  SDL_Quit();
}

void  Display::Application::go()
{
  this->_sceneManager = this->_root->createSceneManager(Ogre::ST_GENERIC);
  this->_root->addFrameListener(this);
  this->_root->startRendering();
}

void	Display::Application::initInputs()
{
  InputHandler::instance()->addInputHandler(new QuitCommand(*this));
  InputHandler::instance()->addInputHandler(new PauseCommand(*this->_cegui, SDLK_ESCAPE));
  InputHandler::instance()->addInputHandler(new InitControllerCommand(*this->_cegui,
								      *this));
}

void	Display::Application::initRessources()
{
  Ogre::ConfigFile  config;

  std::cerr << "Loading ressources" << std::endl;
  config.load("resources.cfg");
  Ogre::ConfigFile::SectionIterator it = config.getSectionIterator();
  while (it.hasMoreElements())
  {
    Ogre::ConfigFile::SettingsMultiMap *settings = it.getNext();
    for (Ogre::ConfigFile::SettingsMultiMap::iterator it_map = settings->begin(); it_map != settings->end(); ++it_map)
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(it_map->second, it_map->first);
  }
  std::cerr << "End loading ressources" << std::endl;
}

void            Display::Application::windowClosed()
{
  if (this->_quit == false)
  {
    this->_quit = true;
  }
}

void            Display::Application::manageIntro()
{
  static bool       thunder = false;
  struct timeval    now;
  size_t            passedTime;

  gettimeofday(&now, NULL);
  passedTime = now.tv_sec - this->_timeval.tv_sec;
  if (passedTime > 2)
    this->_cegui->getAnimatedLayout("Intro")->fade();
  if (this->_cegui->getAnimatedLayout("Intro")->getMode() == CEGUI::FADE_IDLE &&
      passedTime > 14)
    this->_cegui->launchMenu();
  else if (this->_cegui->getAnimatedLayout("Intro")->getMode() == CEGUI::FADE_IDLE &&
      passedTime > 14)
    this->_cegui->getAnimatedLayout("Intro")->setMode(CEGUI::FADE_OUT);
  else if (this->_cegui->getAnimatedLayout("Intro")->getMode() == CEGUI::FADE_IDLE &&
      passedTime > 13)
    this->_cegui->getAnimatedLayout("Intro")->setMode(CEGUI::FADE_OUT);
  else if (this->_cegui->getAnimatedLayout("Intro")->getMode() == CEGUI::FADE_IDLE &&
      passedTime > 9)
  {
    this->_cegui->getAnimatedLayout("Intro")->getLayout()->getChild("TextIntro")->setAlpha(0);
    this->_cegui->getAnimatedLayout("Intro")->getLayout()->getChild("TextIntro2")->setAlpha(1);
    this->_cegui->getAnimatedLayout("Intro")->setMode(CEGUI::FADE_IN);
  }
  else if (this->_cegui->getAnimatedLayout("Intro")->getMode() == CEGUI::FADE_IDLE &&
      passedTime > 6)
      this->_cegui->getAnimatedLayout("Intro")->setMode(CEGUI::FADE_OUT);
  else if (passedTime == 3 && thunder == false)
    {
      this->_cegui->loadConfig();
      this->getAudioSound().playSound("Thunder");
      thunder = true;
    }
}

bool Display::Application::frameRenderingQueued(const Ogre::FrameEvent& event)
{
  if (this->_quit == true)
  {
    return (false);
  }
  if (this->_cegui->getState() == CEGUI::INTRO)
    this->manageIntro();
  else if (this->_cegui->getState() == CEGUI::MENU)
    this->_cegui->getAnimatedLayout("MainMenu")->fade();
  else if (this->_cegui->getState() == CEGUI::END)
    this->_cegui->getAnimatedLayout("End")->fade();
  InputHandler::instance()->handleInput();
  if (this->_cegui->getState() == CEGUI::GAME || this->_cegui->getState() == CEGUI::END)
    {
      if (this->_gauntlet.isDefeat() && this->_cegui->getState() == CEGUI::GAME)
	{
	  this->_cegui->setState(CEGUI::END);
	  this->getAudioMusic().stopMusic();
	  this->_cegui->getAnimatedLayout("End")->getLayout()->show();
	  this->_cegui->getAnimatedLayout("End")->getLayout()->getChild("Victory")->setAlpha(0);
	  this->getAudioSound().playSound("Defeat");
	  this->_gauntlet.writeScore();
	}
      else if (this->_gauntlet.isVictory() && this->_cegui->getState() == CEGUI::GAME)
	{
	  this->_cegui->setState(CEGUI::END);
	  this->_cegui->getAnimatedLayout("End")->getLayout()->show();
	  this->_cegui->getAnimatedLayout("End")->getLayout()->getChild("Defeat")->setAlpha(0);
          this->_gauntlet.writeScore();
	  this->_gauntlet.playVictoryMusic();
	//   this->getAudioSound().playSound("Defeat");
	}
      return this->_gauntlet.updateFrame(event.timeSinceLastFrame);
    }
  return (true);
}

Ogre::RenderWindow*   Display::Application::getOgreWindow() const
{
  return (this->_ogreWindow);
}

Gauntlet              &Display::Application::getGauntlet()
{
  return (this->_gauntlet);
}

Ogre::SceneManager*  Display::Application::getSceneManager() const
{
  return (this->_sceneManager);
}

AudioSystem          &Display::Application::getAudioMusic()
{
  return (this->_audio);
}

AudioEffect          &Display::Application::getAudioSound()
{
  return (this->_sound);
}
