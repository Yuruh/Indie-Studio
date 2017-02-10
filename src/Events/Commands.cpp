//
// Commands.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src/Events
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Mon May 23 02:03:20 2016 Martin Desrumaux
// Last update Sun Jun 05 01:49:07 2016 Martin Desrumaux
//

#include	"Application.hpp"
#include	"Events/Commands.hpp"

QuitCommand::QuitCommand(Display::Application &app) :
  app(app)
{
}

QuitCommand::~QuitCommand()
{
}

bool			QuitCommand::execute(const SDL_Event &event)
{
  if (event.type == SDL_QUIT)
    {
      app.windowClosed();
      return (true);
    }
  return (false);
}

PauseCommand::PauseCommand(CEGUI::GUI &cegui, SDL_Keycode key) :
  _cegui(cegui),
  _key(key)
{
}

PauseCommand::~PauseCommand()
{
}

bool			PauseCommand::execute(const SDL_Event &event)
{
  if (event.type == SDL_KEYUP && event.key.keysym.sym == this->_key)
  {
    this->_cegui.togglePause();
    return (true);
  }
  return (false);
}

AttackCommand::AttackCommand(Player &player, SDL_Keycode key, \
			     const Controller &controller) :
  player(player),
  _controller(controller),
  _key(key),
  bool_attack(false)
{
}

AttackCommand::~AttackCommand()
{
}

bool			AttackCommand::execute(const SDL_Event &event)
{
  if (this->_controller.type == KEYBOARD && \
      (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN))
    this->bool_attack = event.key.keysym.sym == this->_key;
  else if (this->_controller.type == GAMECONTROLLER && \
	   static_cast<const GameController&>(this->_controller).id \
	   == event.jbutton.which && \
	   (event.type == SDL_JOYBUTTONUP || event.type == SDL_JOYBUTTONDOWN))
    this->bool_attack = event.jbutton.button == this->_key;
  return (false);
}

void				AttackCommand::update(float timeSinceLastFrame)
{
  (void)timeSinceLastFrame;
  if (this->player.getState() == AnimatedElem::ATTACK || this->bool_attack)
    this->player.attack(this->bool_attack);
  this->bool_attack = false;
}

SpecialAttackCommand::SpecialAttackCommand(Player &player, SDL_Keycode key, \
					   const Controller &controller) :
  player(player),
  _controller(controller),
  _key(key),
  bool_attack(false)
{
}

SpecialAttackCommand::~SpecialAttackCommand()
{
}

bool			SpecialAttackCommand::execute(const SDL_Event &event)
{
  if (this->_controller.type == KEYBOARD && \
      (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN))
    this->bool_attack = event.key.keysym.sym == this->_key;
  else if (this->_controller.type == GAMECONTROLLER && \
	   static_cast<const GameController&>(this->_controller).id \
	   == event.jbutton.which && \
	   (event.type == SDL_JOYBUTTONUP || event.type == SDL_JOYBUTTONDOWN))
    this->bool_attack = event.jbutton.button == this->_key;
  return (false);
}

void				SpecialAttackCommand::update(float timeSinceLastFrame)
{
  (void)timeSinceLastFrame;
  if (this->player.getState() == AnimatedElem::SPECIALATTACK || this->bool_attack)
    this->player.specialAttack(this->bool_attack);
  this->bool_attack = false;
}

InitPlayerCommand::InitPlayerCommand(CEGUI::GUI &cegui,
				     SDL_Keycode key, Uint8 joyBtn,
				     SDL_Keycode botKey, Uint8 botJoyBtn) :
  _cegui(cegui),
  _key(key),
  _botKey(botKey),
  _joyBtn(joyBtn),
  _botJoyBtn(botJoyBtn)
{
}

InitPlayerCommand::~InitPlayerCommand()
{
}

bool			InitPlayerCommand::execute(const SDL_Event &event)
{
  if (event.type == SDL_KEYUP && event.key.keysym.sym == this->_key)
  {
    this->_cegui.nextPlayerLobby(new KeyboardController());
  }
  else if ((event.type == SDL_KEYUP && event.key.keysym.sym == this->_botKey) ||
	   (event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == this->_botJoyBtn))
  {
    this->_cegui.nextPlayerLobby(new IAController());
  }
  else if (event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == this->_joyBtn)
  {
    this->_cegui.nextPlayerLobby(new GameController(event.jbutton.which));
  }
  return (false);
}

InitControllerCommand::InitControllerCommand(CEGUI::GUI &cegui,
			  Display::Application &app) :
  _cegui(cegui),
  _app(app)
{
  SDL_GameController	*controller;
  int			njoy;

  njoy = SDL_NumJoysticks();
  for (int i = 0; i < njoy; ++i)
  {
    if (SDL_IsGameController(i))
    {
      if ((controller = SDL_GameControllerOpen(i)) == NULL)
	std::cerr << "Could not open gamecontroller " << i << ": " <<
	  SDL_GetError() << std::endl;
    }
  }
}

InitControllerCommand::~InitControllerCommand()
{
  SDL_GameController	*controller;
  int			njoy;

  njoy = SDL_NumJoysticks();
  for (int i = 0; i < njoy; ++i)
  {
    if (SDL_IsGameController(i))
    {
      controller = SDL_GameControllerFromInstanceID(i);
      SDL_GameControllerClose(controller);
    }
  }
}

bool		InitControllerCommand::execute(const SDL_Event &event)
{
  if (event.type == SDL_JOYDEVICEADDED)
  {
    if ((SDL_GameControllerOpen(event.jdevice.which)) == NULL)
      std::cerr << "Could not open gamecontroller " << event.jdevice.which
	<< ": " << SDL_GetError() << std::endl;
  }
  else if (event.type == SDL_JOYDEVICEREMOVED)
  {
    SDL_GameControllerClose(SDL_GameControllerFromInstanceID(event.jdevice.which));
    this->_cegui.reloadLobby();
  }
  return (false);
}

GenericJoystickGUICommand::GenericJoystickGUICommand(CEGUI::GUI &cegui,
						     void (CEGUI::GUI::*func)(void), \
						     SDL_Keycode key) :
  _cegui(cegui),
  _key(key),
  _func(func)
{
}

GenericJoystickGUICommand::~GenericJoystickGUICommand()
{
}

bool				GenericJoystickGUICommand::execute(const SDL_Event &event)
{
  if (event.type == SDL_JOYBUTTONUP && event.jbutton.button == this->_key)
  {
    ((this->_cegui).*(this->_func))();
    return (true);
  }
  return (false);
}

/*
ActionMouse::ActionMouse(int xbegin, int ybegin, int width, int height):
  xbegin(xbegin),
  ybegin(ybegin),
  width(width),
  height(height)
{
}

ActionMouse::ActionMouse():
  xbegin(-1),
  ybegin(-1),
  width(-1),
  height(-1)
{
}

ActionMouse::~ActionMouse()
{
}

bool		ActionMouse::isAction(const SDL_Event &event)
{
  if (this->width == -1 && this->height == -1)
    return (true);
  if (event.type == SDL_MOUSEBUTTONDOWN && \
      event.button.x >= this->xbegin && \
      event.button.x <= this->xbegin + width && \
      event.button.y >= this->ybegin && \
      event.button.y <= this->ybegin + height)
    return (true);
  else
    return (false);
}
*/
