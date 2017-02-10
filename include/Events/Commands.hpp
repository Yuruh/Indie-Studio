//
// Commands.hpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Fri May 20 15:41:36 2016 Martin Desrumaux
// Last update Sun Jun 05 01:31:43 2016 Martin Desrumaux
//

#ifndef		COMMANDS_HPP_
# define	COMMANDS_HPP_

# include	"SDL.h"
# include	"PlayableClass/Player.hpp"
# include	"GUI.hpp"
# include	"Events/Controller.hpp"

namespace Display
{
  class Application;
};

typedef enum
{
    MY_SDL_CONTROLLER_BUTTON_INVALID = -1,
    MY_SDL_CONTROLLER_BUTTON_A = 0,
    MY_SDL_CONTROLLER_BUTTON_B = 1,
    MY_SDL_CONTROLLER_BUTTON_X = 2,
    MY_SDL_CONTROLLER_BUTTON_Y = 3,
    MY_SDL_CONTROLLER_BUTTON_BACK = 6,
    MY_SDL_CONTROLLER_BUTTON_GUIDE = 8,
    MY_SDL_CONTROLLER_BUTTON_START = 7,
    MY_SDL_CONTROLLER_BUTTON_LEFTSTICK = 4, // LB
    MY_SDL_CONTROLLER_BUTTON_RIGHTSTICK = 5, // RB
    MY_SDL_CONTROLLER_BUTTON_LEFTSHOULDER = 9,
    MY_SDL_CONTROLLER_BUTTON_RIGHTSHOULDER = 10,
    MY_SDL_CONTROLLER_BUTTON_DPAD_UP,
    MY_SDL_CONTROLLER_BUTTON_DPAD_DOWN,
    MY_SDL_CONTROLLER_BUTTON_DPAD_LEFT,
    MY_SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
    MY_SDL_CONTROLLER_BUTTON_MAX
} MY_SDL_GameControllerButton;

class ICommand
{
  public:
    virtual ~ICommand() {}
    virtual bool execute(const SDL_Event &event) = 0;
};

class QuitCommand : public ICommand
{
  public:
    QuitCommand(Display::Application &app);
    ~QuitCommand();
  public:
    bool		execute(const SDL_Event &event);
  private:
    Display::Application		&app;
};

class PauseCommand : public ICommand
{
  public:
    PauseCommand(CEGUI::GUI &cegui, SDL_Keycode key);
    ~PauseCommand();
  public:
    bool    execute(const SDL_Event &event);
  private:
    CEGUI::GUI		&_cegui;
    SDL_Keycode		_key;
};

class AttackCommand : public ICommand
{
  public:
    AttackCommand(Player &player, SDL_Keycode key, const Controller &type);
    ~AttackCommand();
  public:
    bool		execute(const SDL_Event &event);
    void		update(float timeSinceLastFrame);
  private:
    Player		&player;
    const Controller	&_controller;
    int			_key;
    bool		bool_attack;
};

class SpecialAttackCommand : public ICommand
{
  public:
    SpecialAttackCommand(Player &player, SDL_Keycode key, const Controller &type);
    ~SpecialAttackCommand();
  public:
    bool		execute(const SDL_Event &event);
    void		update(float timeSinceLastFrame);
  private:
    Player		&player;
    const Controller	&_controller;
    SDL_Keycode		_key;
    bool		bool_attack;
};

class InitPlayerCommand : public ICommand
{
  public:
    InitPlayerCommand(CEGUI::GUI &cegui,
		      SDL_Keycode key, Uint8 joyBtnm,
		      SDL_Keycode botKey, Uint8 botJoyBtn);
    ~InitPlayerCommand();
  public:
    bool    execute(const SDL_Event &event);
  private:
    CEGUI::GUI		&_cegui;
    SDL_Keycode		_key;
    SDL_Keycode		_botKey;
    Uint8		_joyBtn;
    Uint8		_botJoyBtn;
};

class InitControllerCommand : public ICommand
{
  public:
    InitControllerCommand(CEGUI::GUI &cegui,
			  Display::Application &application);
    ~InitControllerCommand();
  public:
    bool    execute(const SDL_Event &event);
  private:
    CEGUI::GUI		&_cegui;
    Display::Application	&_app;
};

class GenericJoystickGUICommand : public ICommand
{
  public:
    GenericJoystickGUICommand(CEGUI::GUI &cegui,
			      void (CEGUI::GUI::*)(void), \
			      SDL_Keycode key);
    ~GenericJoystickGUICommand();
  public:
    bool    execute(const SDL_Event &event);
  private:
    CEGUI::GUI			&_cegui;
    int				_key;
    void			(CEGUI::GUI::*_func)(void);
};

#endif		// !COMMANDS_HPP_
