//
// MoveCommands.hpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include/Events
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Wed Jun 01 20:30:40 2016 Martin Desrumaux
// Last update Thu Jun  2 15:28:54 2016 Antoine Lempereur
//

#ifndef		MOVECOMMANDS_HPP_
# define	MOVECOMMANDS_HPP_

# include	"PlayableClass/Player.hpp"
# include	"Events/Controller.hpp"
# include	"Events/Commands.hpp"

class IMoveCommand : public ICommand
{
  public:
    virtual ~IMoveCommand() {}
  public:
    virtual void	update(float timeSinceLastFrame) = 0;
};

class KeyMoveCommand : public IMoveCommand
{
  public:
    KeyMoveCommand(Player &player, SDL_Keycode up, SDL_Keycode down,
		SDL_Keycode left, SDL_Keycode right);
    ~KeyMoveCommand();
  public:
    bool		execute(const SDL_Event &event);
    void		update(float timeSinceLastFrame);
  private:
    Player		&player;
    SDL_Keycode		up;
    SDL_Keycode		down;
    SDL_Keycode		left;
    SDL_Keycode		right;
    bool		bool_up;
    bool		bool_down;
    bool		bool_left;
    bool		bool_right;
};

class JoystickMoveCommand : public IMoveCommand
{
  public:
    JoystickMoveCommand(Player &player, const SDL_JoystickID id);
    ~JoystickMoveCommand();
  public:
    bool		execute(const SDL_Event &event);
    void		update(float timeSinceLastFrame);
  private:
    Player		&player;
    SDL_JoystickID	id;
    float		x;
    float		y;
};

#endif		// !MOVECOMMANDS_HPP_
