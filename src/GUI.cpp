//
// GUI.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Wed May 18 16:58:49 2016 Martin Desrumaux
// Last update Sun Jun  5 04:40:07 2016 Raphael Thiebault
//

#include  "GUI.hpp"
#include  "Application.hpp"

CEGUI::GUI::GUI(Ogre::Root *root, Display::Application *application)
{
  Ogre::RenderTarget* renderTarget = root->getRenderTarget("OGRE Window");
  this->_renderer = &CEGUI::OgreRenderer::bootstrapSystem(*renderTarget);
  this->_application = application;
  this->_parserConfig = new ParserConfig();
  CEGUI::SchemeManager::getSingleton().createFromFile("GlossySerpent.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("GameMenu.scheme");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("GlossySerpentCursors/MouseArrow");
  this->_rootWindow = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "_MasterRoot" );
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(this->_rootWindow);
  this->initWindowMap();
  this->initAnimatedLayoutMap();
  this->initButtons();
  this->initOptions();
  this->initSound();
  this->initLobby();
  this->initHighScore();
  this->_GUIState = CEGUI::INTRO;
  this->_menuInputIds["SkipIntro"] = InputHandler::instance()->addInputHandler(
									  new GenericJoystickGUICommand(*this, \
									  &CEGUI::GUI::launchMenu, \
									  MY_SDL_CONTROLLER_BUTTON_A));
}

CEGUI::GUI::~GUI()
{
}

void    CEGUI::GUI::initAnimatedLayoutMap()
{
  this->_aLayoutMap["Intro"] = new CEGUI::AnimatedLayout("Intro.layout");
  this->_aLayoutMap["MainMenu"] = new CEGUI::AnimatedLayout("MainMenu.layout");
  this->_aLayoutMap["End"] = new CEGUI::AnimatedLayout("End.layout");
  for (auto it = this->_aLayoutMap.begin(); it != this->_aLayoutMap.end(); it++)
   {
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(it->second->getLayout());
    if (it->first != "Intro")
      it->second->getLayout()->hide();
   }
}

void    CEGUI::GUI::initWindowMap()
{
  this->_windowMap["Background"] = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Background.layout");
  this->_windowMap["Lobby"] = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Lobby.layout");
  this->_windowMap["Options"] = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Options.layout");
  this->_windowMap["Overlay"] = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Overlay.layout");
  this->_windowMap["Pause"] = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Pause.layout");
  this->_windowMap["Options"]->setAlwaysOnTop(true);
  for (auto it = this->_windowMap.begin(); it != this->_windowMap.end(); it++)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(it->second);
    if (it->first != "Background")
      it->second->hide();
  }
}

// TODO FLAC to wav -->
void    CEGUI::GUI::initSound()
{
  this->_application->getAudioMusic().loadMusic("media/audio/theme.flac");
  this->_application->getAudioSound().loadSound("SwitchMenu", "media/audio/sound/switchMenu.flac");
  this->_application->getAudioSound().loadSound("Button", "media/audio/sound/Button.flac");
  this->_application->getAudioSound().loadSound("Thunder", "media/audio/sound/Thunder.wav");
  this->_application->getAudioSound().loadSound("Defeat", "media/audio/Defeat.ogg");
  this->_application->getAudioSound().loadSound("Warrior_Lobby", "media/audio/sound/Warrior_Lobby.flac");
  this->_application->getAudioSound().loadSound("Archer_Lobby", "media/audio/sound/Archer_Lobby.flac");
  this->_application->getAudioSound().loadSound("Mage_Lobby", "media/audio/sound/Mage_Lobby.flac");
  this->_application->getAudioSound().loadSound("Valkyrie_Lobby", "media/audio/sound/Valkyrie_Lobby.flac");
  this->_application->getAudioMusic().playMusic();
}

void    CEGUI::GUI::initButtons()
{
  this->_aLayoutMap["MainMenu"]->getLayout()->getChild("HighscoreListPanel/ButtonExit")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::quitGame, this));
  this->_aLayoutMap["MainMenu"]->getLayout()->getChild("HighscoreListPanel/ButtonNewGame")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::launchLobby, this));
  this->_aLayoutMap["MainMenu"]->getLayout()->getChild("HighscoreListPanel/ButtonOptions")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::toggleOptions, this));

  this->_windowMap["Options"]->getChild("BtnOptOk")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::validateOptions, this));
  this->_windowMap["Options"]->getChild("BtnOptCancel")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::toggleOptions, this));

  this->_windowMap["Pause"]->getChild("PauseWindow/PauseResume")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::togglePause, this));
  this->_windowMap["Pause"]->getChild("PauseWindow/PauseOption")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::toggleOptions, this));
  this->_windowMap["Pause"]->getChild("PauseWindow/PauseQuit")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::quitGame, this));

  this->_windowMap["Lobby"]->getChild("BtnBack")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::backToMenu, this));
  this->_windowMap["Lobby"]->getChild("BtnPlay")->subscribeEvent(
                        CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::runGame, this));
}

void  CEGUI::GUI::bindOverlay(PlayerManager &players)
{
  Player  *player;

  if ((player = players.getPlayer(WARRIOR)) != NULL)
    player->bindOverlay(this->_windowMap["Overlay"]->getChild("Warrior_Overlay"));
  if ((player = players.getPlayer(ARCHER)) != NULL)
    player->bindOverlay(this->_windowMap["Overlay"]->getChild("Archer_Overlay"));
  if ((player = players.getPlayer(MAGE)) != NULL)
    player->bindOverlay(this->_windowMap["Overlay"]->getChild("Mage_Overlay"));
  if ((player = players.getPlayer(VALKYRIE)) != NULL)
    player->bindOverlay(this->_windowMap["Overlay"]->getChild("Valkyrie_Overlay"));
}

void    CEGUI::GUI::initOverlay()
{
  this->_windowMap["Overlay"]->show();
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Warrior_Overlay/Warrior_hp"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Warrior_Overlay/Warrior_mana"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Archer_Overlay/Archer_hp"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Archer_Overlay/Archer_mana"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Mage_Overlay/Mage_hp"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Mage_Overlay/Mage_mana"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Valkyrie_Overlay/Valkyrie_hp"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Valkyrie_Overlay/Valkyrie_mana"))->setProgress(100);
  static_cast<CEGUI::ProgressBar*>(this->_windowMap["Overlay"]->getChild("Boss_Overlay/Boss_hp"))->setProgress(100);
}

void    CEGUI::GUI::initHighScore()
{
  std::map<std::string, size_t> defaultScoreMap;

  try
  {
    this->_parserScore.parseFile("score/gauntlet.score");
    this->_scoreMap = this->_parserScore.getResult();
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }
  defaultScoreMap["WARRIOR"] = 0;
  defaultScoreMap["ARCHER"] = 0;
  defaultScoreMap["MAGE"] = 0;
  defaultScoreMap["VALKYRIE"] = 0;
  for (auto it = this->_scoreMap.begin(); it != this->_scoreMap.end(); it++)
  {
    defaultScoreMap[it->first] = it->second;
  }
  this->_windowMap["Overlay"]->getChild("Warrior_Overlay/Warrior_score")->setText("H-Score: " + std::to_string(defaultScoreMap["WARRIOR"]));
  this->_windowMap["Overlay"]->getChild("Archer_Overlay/Archer_score")->setText("H-Score: " + std::to_string(defaultScoreMap["ARCHER"]));
  this->_windowMap["Overlay"]->getChild("Mage_Overlay/Mage_score")->setText("H-Score: " + std::to_string(defaultScoreMap["MAGE"]));
  this->_windowMap["Overlay"]->getChild("Valkyrie_Overlay/Valkyrie_score")->setText("H-Score: " + std::to_string(defaultScoreMap["VALKYRIE"]));
}

void    CEGUI::GUI::initOptions()
{
  static_cast<CEGUI::TabControl*>(this->_windowMap["Options"]->getChild("OptionsWindowTab"))->setSelectedTab("Tab_Video");
  static_cast<CEGUI::Spinner*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Video/Option_Ombre"))->setMinimumValue(1);
  static_cast<CEGUI::Spinner*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Video/Option_Ombre"))->setMaximumValue(3);
  this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Volume")->subscribeEvent(
                        CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::changeVolume, this));
  this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Son")->subscribeEvent(
                        CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::changeSon, this));
  this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Musique")->subscribeEvent(
                        CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(
                        &CEGUI::GUI::changeMusique, this));
}

void    CEGUI::GUI::initLobby()
{
  this->_selectLobby.insert(this->_selectLobby.end(), { "Warrior", "Archer", "Mage", "Valkyrie", "Play"} );
  this->_idxLobby = 0;
}

void    CEGUI::GUI::launchMenu()
{
  this->_GUIState = MENU;
  this->_aLayoutMap["MainMenu"]->getLayout()->show();
  this->_aLayoutMap["Intro"]->getLayout()->hide();
  this->loadConfig();
  this->_application->getAudioSound().playSound("SwitchMenu");
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["SkipIntro"]);
  this->_menuInputIds["NewGame"] = InputHandler::instance()->addInputHandler(
									  new GenericJoystickGUICommand(*this, \
									  &CEGUI::GUI::launchLobby, \
									  MY_SDL_CONTROLLER_BUTTON_A));
  this->_menuInputIds["QuitFromMenu"] = InputHandler::instance()->addInputHandler(
									  new GenericJoystickGUICommand(*this, \
									  &CEGUI::GUI::quitGame, \
									  MY_SDL_CONTROLLER_BUTTON_B));
}

void    CEGUI::GUI::backToMenu()
{
  for (auto it = this->_windowMap.begin(); it != this->_windowMap.end(); it++)
    it->second->hide();
  this->_GUIState = CEGUI::MENU;
  this->_aLayoutMap["MainMenu"]->setAlpha(0);
  this->_aLayoutMap["MainMenu"]->setMode(CEGUI::FADE_IN);
  this->_aLayoutMap["MainMenu"]->getLayout()->show();
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["LobbySelect"]);
  this->_menuInputIds.erase("LobbySelect");
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["BackMenu"]);
  this->_menuInputIds.erase("BackMenu");
  this->_menuInputIds["NewGame"] = InputHandler::instance()->addInputHandler(
									  new GenericJoystickGUICommand(*this, \
									  &CEGUI::GUI::launchLobby, \
									  MY_SDL_CONTROLLER_BUTTON_A));
  this->_menuInputIds["QuitFromMenu"] = InputHandler::instance()->addInputHandler(
									  new GenericJoystickGUICommand(*this, \
									  &CEGUI::GUI::quitGame, \
									  MY_SDL_CONTROLLER_BUTTON_B));
}

void    CEGUI::GUI::launchLobby()
{
  this->_GUIState = LOBBY;
  this->reloadLobby();
  this->_application->getAudioSound().playSound("SwitchMenu");
  this->_aLayoutMap["MainMenu"]->getLayout()->hide();
  this->_windowMap["Lobby"]->show();
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["NewGame"]);
  this->_menuInputIds.erase("NewGame");
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["QuitFromMenu"]);
  this->_menuInputIds.erase("QuitFromMenu");
  this->_menuInputIds["LobbySelect"] = InputHandler::instance()->addInputHandler(
									new InitPlayerCommand(*this, SDLK_SPACE,
									MY_SDL_CONTROLLER_BUTTON_A,
									SDLK_DELETE,
									MY_SDL_CONTROLLER_BUTTON_Y));
  this->_menuInputIds["BackMenu"] = InputHandler::instance()->addInputHandler(
									new GenericJoystickGUICommand(*this, \
									&CEGUI::GUI::backToMenu, \
									MY_SDL_CONTROLLER_BUTTON_B));
  this->_menuInputIds["LobbyLaunch"] = InputHandler::instance()->addInputHandler(
									new GenericJoystickGUICommand(*this, \
									&CEGUI::GUI::runGame, \
									MY_SDL_CONTROLLER_BUTTON_START));
  this->_menuInputIds["ResetLobby"] = InputHandler::instance()->addInputHandler(
									new GenericJoystickGUICommand(*this, \
									&CEGUI::GUI::reloadLobby, \
									MY_SDL_CONTROLLER_BUTTON_BACK));
}

void    CEGUI::GUI::nextPlayerLobby(struct Controller *input)
{
  std::string currentClass;
  std::string nextClass;

  if (this->_GUIState == LOBBY &&
      this->_selectLobby[this->_idxLobby] != "Play")
  {
    currentClass = this->_selectLobby[this->_idxLobby];
    nextClass = this->_selectLobby[this->_idxLobby + 1];
    if (!this->assignInput(input, currentClass))
      return;
    this->_application->getAudioSound().playSound(currentClass + "_Lobby");
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Connected_Text")->setAlpha(1.0);
    if (nextClass != "Play")
    {
      this->_windowMap["Lobby"]->getChild(nextClass + "_Panel")->setAlpha(1.0);
      this->_windowMap["Lobby"]->getChild(nextClass + "_Panel/" + nextClass + "Controller_Text")->setAlpha(1.0);
      this->_windowMap["Lobby"]->getChild(nextClass + "_Panel/" + nextClass + "Keyboard")->setAlpha(1.0);
      this->_windowMap["Lobby"]->getChild(nextClass + "_Panel/" + nextClass + "Gamepad")->setAlpha(1.0);
      this->_windowMap["Lobby"]->getChild(nextClass + "_Panel/" + nextClass + "IA")->setAlpha(1.0);
    }
    this->_idxLobby++;
    this->_windowMap["Lobby"]->getChild("BtnPlay")->setDisabled(false);
  }
}

// TODO concaténer le getChild() -->
void    CEGUI::GUI::reloadLobby()
{
  std::string   currentClass;

  if (this->_GUIState != LOBBY)
    return;
  this->_idxLobby = 0;
  this->_playerInput.clear();
  for (auto it = this->_selectLobby.begin(); it != this->_selectLobby.end() - 1; it++)
  {
    currentClass = *it;
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Connected_Text")->setAlpha(0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Controller_Text")->setText("Choisissez un controleur");
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel")->setAlpha(0.5);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Controller_Text")->setAlpha(0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Keyboard")->setAlpha(0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "KeyboardOK")->setAlpha(0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Gamepad")->setAlpha(0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "GamepadOK")->setAlpha(0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "IA")->setAlpha(0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "IAOK")->setAlpha(0);
  }
  this->_windowMap["Lobby"]->getChild("Warrior_Panel")->setAlpha(1.0);
  this->_windowMap["Lobby"]->getChild("Warrior_Panel/WarriorController_Text")->setAlpha(1.0);
  this->_windowMap["Lobby"]->getChild("Warrior_Panel/WarriorKeyboard")->setAlpha(1.0);
  this->_windowMap["Lobby"]->getChild("Warrior_Panel/WarriorGamepad")->setAlpha(1.0);
  this->_windowMap["Lobby"]->getChild("Warrior_Panel/WarriorIA")->setAlpha(1.0);
  this->_windowMap["Lobby"]->getChild("BtnPlay")->setDisabled(true);
}

bool    CEGUI::GUI::assignInput(struct Controller *input, const std::string &currentClass)
{
  if (input->type == KEYBOARD)
  {
    for (auto it = this->_playerInput.begin(); it != this->_playerInput.end(); it++)
    {
      if ((*it)->type == KEYBOARD)
        return (false);
    }
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "KeyboardOK")->setAlpha(1.0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Controller_Text")->setText("Joueur " + this->_parserConfig->toString(this->_idxLobby + 1));
  }
  else if (input->type == GAMECONTROLLER)
  {
    for (auto it = this->_playerInput.begin(); it != this->_playerInput.end(); it++)
    {
      if ((*it)->type == GAMECONTROLLER &&
          (static_cast<GameController*>(*it))->id == static_cast<GameController*>(input)->id)
        return (false);
    }
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "GamepadOK")->setAlpha(1.0);
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Controller_Text")->setText("Joueur " + this->_parserConfig->toString(this->_idxLobby + 1));
  }
  else if (input->type == IA)
  {
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Controller_Text")->setText("Ordi");
    this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "IAOK")->setAlpha(1.0);
  }
  this->_playerInput.push_back(input);
  this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Keyboard")->setAlpha(0);
  this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "Gamepad")->setAlpha(0);
  this->_windowMap["Lobby"]->getChild(currentClass + "_Panel/" + currentClass + "IA")->setAlpha(0);
  return (true);
}

void    CEGUI::GUI::toggleOptions()
{
  this->_application->getAudioSound().playSound("Button");
  if (!this->_windowMap["Options"]->isVisible())
    this->_windowMap["Options"]->show();
  else
    this->_windowMap["Options"]->hide();
  this->loadConfig();
}

void    CEGUI::GUI::loadConfig()
{
  std::map<std::string, double>   configParsed;

  this->_optionMap["VOLUME"] = 1.0;
  this->_optionMap["SON"] = 1.0;
  this->_optionMap["MUSIQUE"] = 1.0;
  this->_optionMap["MUTE"] = 0;
  this->_optionMap["OMBRE"] = 1;
  this->_optionMap["DEBUG"] = 0;
  try
  {
    this->_parserConfig->parseFile("config/config.gauntlet");
    configParsed = this->_parserConfig->getResult();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  for (auto it = configParsed.begin(); it != configParsed.end(); it++)
  {
    this->_optionMap[it->first] = it->second;
  }
  this->applyConfig();
}

void    CEGUI::GUI::applyConfig()
{
  if (this->_optionMap["MUTE"])
  {
    this->_optionMap["VOLUME"] = 0;
    this->_optionMap["MUSIQUE"] = 0;
    this->_optionMap["SON"] = 0;
  }
  static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Musique"))->setCurrentValue(this->_optionMap["MUSIQUE"]);
  static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Son"))->setCurrentValue(this->_optionMap["SON"]);
  static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Volume"))->setCurrentValue(this->_optionMap["VOLUME"]);
  static_cast<CEGUI::Spinner*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Video/Option_Ombre"))->setCurrentValue(this->_optionMap["OMBRE"]);
  static_cast<CEGUI::ToggleButton*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Video/Option_Debug"))->setSelected(this->_optionMap["DEBUG"]);
  this->_application->getAudioMusic().setGlobalVolume(this->_optionMap["VOLUME"] * 100.0);
  this->_application->getAudioMusic().setMusicVolume(this->_optionMap["MUSIQUE"] * 100.0);
  this->_application->getAudioSound().setVolume(this->_optionMap["SON"] * 100.0);
  this->_application->getSceneManager()->showBoundingBoxes(this->_optionMap["DEBUG"]);
  if (this->_optionMap["OMBRE"] > 1)
    this->_application->getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
  else
    this->_application->getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
  static_cast<CEGUI::ToggleButton*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Mute"))->setSelected(this->_optionMap["MUTE"]);
}

void    CEGUI::GUI::writeConfig() const
{
  std::ofstream fd("config/config.gauntlet", std::ios::out | std::ios::trunc);

  if (fd)
  {
    for (auto it = this->_optionMap.begin(); it != this->_optionMap.end(); it++)
    {
      fd << it->first << "=" << it->second << std::endl;
    }
  }
}

void    CEGUI::GUI::validateOptions()
{
  this->_optionMap["SON"] = static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Son"))->getCurrentValue();
  this->_optionMap["MUSIQUE"] = static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Musique"))->getCurrentValue();
  this->_optionMap["VOLUME"] = static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Volume"))->getCurrentValue();
  this->_optionMap["MUTE"] = static_cast<CEGUI::ToggleButton*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Mute"))->isSelected();
  this->_optionMap["OMBRE"] = static_cast<CEGUI::Spinner*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Video/Option_Ombre"))->getCurrentValue();
  this->_optionMap["DEBUG"] = static_cast<CEGUI::ToggleButton*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Video/Option_Debug"))->isSelected();
  this->applyConfig();
  this->writeConfig();
  this->toggleOptions();
}

void    CEGUI::GUI::togglePause()
{
  this->_application->getAudioSound().playSound("Button");
  if (this->_GUIState == MENU || this->_GUIState == END)
    this->quitGame();
  else if (this->_GUIState == INTRO)
    this->launchMenu();
  else if (this->_GUIState == GAME ||
           this->_GUIState == PAUSE)
  {
    if (!this->_windowMap["Pause"]->isVisible())
    {
      this->_windowMap["Pause"]->show();
      this->_windowMap["Overlay"]->hide();
      this->_GUIState = PAUSE;
      this->_menuInputIds["QuitFromPause"] = InputHandler::instance()->addInputHandler(
										       new GenericJoystickGUICommand(*this, \
										       &CEGUI::GUI::quitGame, \
										       MY_SDL_CONTROLLER_BUTTON_Y));
    }
    else
    {
      InputHandler::instance()->removeInputHandler(this->_menuInputIds["QuitFromPause"]);
      this->_menuInputIds.erase("QuitFromPause");
      this->_windowMap["Overlay"]->show();
      this->_windowMap["Pause"]->hide();
      this->_GUIState = GAME;
    }
  }
}

void    CEGUI::GUI::changeVolume()
{
  double  volume;

  volume = static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Volume"))->getCurrentValue();
  this->_application->getAudioMusic().setGlobalVolume(volume * 100.0);
}

void    CEGUI::GUI::changeSon()
{
  double  son;

  son = static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Son"))->getCurrentValue();
  this->_application->getAudioSound().setVolume(son * 100.0);
  this->_application->getAudioSound().playSound("Button");
}

void    CEGUI::GUI::changeMusique()
{
  double  music;

  music = static_cast<CEGUI::Slider*>(this->_windowMap["Options"]->getChild("OptionsWindowTab/Tab_Son/Option_Musique"))->getCurrentValue();
  this->_application->getAudioMusic().setMusicVolume(music * 100.0);
}

void    CEGUI::GUI::runGame()
{
  std::vector<ControllerPlayer> cPlayer;

  if (this->_idxLobby == 0)
    return;
  this->_windowMap["Background"]->hide();
  this->_application->getAudioSound().playSound("SwitchMenu");
  this->_GUIState = GAME;
  this->_application->getAudioMusic().loadMusic("media/audio/Level1.flac");
  this->_application->getAudioMusic().playMusic();
  this->_application->getGauntlet().init(this,
				  &this->_application->getAudioMusic(),
				  this->_application->getSceneManager(),
				  this->_application->getOgreWindow());
  if (this->_playerInput.size() > 0)
    cPlayer.push_back(ControllerPlayer(this->_playerInput[0], WARRIOR));
  if (this->_playerInput.size() > 1)
    cPlayer.push_back(ControllerPlayer(this->_playerInput[1], ARCHER));
  if (this->_playerInput.size() > 2)
    cPlayer.push_back(ControllerPlayer(this->_playerInput[2], MAGE));
  if (this->_playerInput.size() > 3)
    cPlayer.push_back(ControllerPlayer(this->_playerInput[3], VALKYRIE));
  this->_application->getGauntlet().createPlayers(cPlayer);
  this->bindOverlay(this->_application->getGauntlet().getPlayerManager());
  this->initOverlay();
  this->_windowMap["Lobby"]->hide();
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["BackMenu"]);
  this->_menuInputIds.erase("BackMenu");
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["LobbyLaunch"]);
  this->_menuInputIds.erase("LobbyLaunch");
  InputHandler::instance()->removeInputHandler(this->_menuInputIds["ResetLobby"]);
  this->_menuInputIds.erase("ResetLobby");
  this->_menuInputIds["Pause"] = InputHandler::instance()->addInputHandler(
									  new GenericJoystickGUICommand(*this, \
									  &CEGUI::GUI::togglePause, \
									  MY_SDL_CONTROLLER_BUTTON_START));
}

void    CEGUI::GUI::quitGame()
{
  this->_application->windowClosed();
}

CEGUI::GUIState   CEGUI::GUI::getState() const
{
  return (this->_GUIState);
}

void              CEGUI::GUI::setState(CEGUI::GUIState state)
{
  this->_GUIState = state;
}

CEGUI::AnimatedLayout*  CEGUI::GUI::getAnimatedLayout(const std::string &layout)
{
  CEGUI::AnimatedLayout*        window;

  window = this->_aLayoutMap[layout];
  return (window);
}

CEGUI::Window		*CEGUI::GUI::getStaticLayout(const std::string &layout)
{
  CEGUI::Window*        window;

  window = this->_windowMap[layout];
  return (window);
}
