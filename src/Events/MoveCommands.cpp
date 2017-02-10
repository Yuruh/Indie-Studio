//
// MoveCommands.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Wed Jun 01 20:29:31 2016 Martin Desrumaux
// Last update Sun Jun 05 03:21:36 2016 Martin Desrumaux
//

#include	"Events/MoveCommands.hpp"

KeyMoveCommand::KeyMoveCommand(Player &player, SDL_Keycode up, SDL_Keycode down,
			       SDL_Keycode left, SDL_Keycode right) :
  player(player),
  up(up),
  down(down),
  left(left),
  right(right),
  bool_up(false),
  bool_down(false),
  bool_left(false),
  bool_right(false)
{
}

KeyMoveCommand::~KeyMoveCommand()
{
}

bool			KeyMoveCommand::execute(const SDL_Event &event)
{
  if (event.type != SDL_KEYUP && event.type != SDL_KEYDOWN)
    return (false);
  if (event.key.keysym.sym == this->up)
    this->bool_up = (event.type == SDL_KEYDOWN);
  if (event.key.keysym.sym == this->down)
    this->bool_down = (event.type == SDL_KEYDOWN);
  if (event.key.keysym.sym == this->left)
    this->bool_left = (event.type == SDL_KEYDOWN);
  if (event.key.keysym.sym == this->right)
    this->bool_right = (event.type == SDL_KEYDOWN);
  return (false);
}

void				KeyMoveCommand::update(float timeSinceLastFrame)
{
  Ogre::Vector3			tmp(0, 0, 0);

  if (this->bool_up)
    tmp.z += this->player.getMvtSpeed();
  if (this->bool_down)
    tmp.z -= this->player.getMvtSpeed();
  if (this->bool_left)
    tmp.x += this->player.getMvtSpeed();
  if (this->bool_right)
    tmp.x -= this->player.getMvtSpeed();

  this->player.moveInput(tmp, tmp * timeSinceLastFrame, \
			 this->bool_up || this->bool_down \
			 || this->bool_left || this->bool_right);
}

JoystickMoveCommand::JoystickMoveCommand(Player &player, const SDL_JoystickID id) :
  player(player),
  id(id),
  x(0),
  y(0)
{
}

JoystickMoveCommand::~JoystickMoveCommand()
{
}

bool				JoystickMoveCommand::execute(const SDL_Event &event)
{
  SDL_Joystick			*joy;
  Sint16			x;
  Sint16			y;

  (void)event;
  if ((joy = SDL_JoystickFromInstanceID(this->id)) == NULL)
  {
    //std::cerr << "SDL_JoystickFromInstanceID failed: " << SDL_GetError() << std::endl;
    return (false);
  }

  x = SDL_JoystickGetAxis(joy, 0);
  y = SDL_JoystickGetAxis(joy, 1);

  double minVal = INT16_MAX / 4;
  if (x > minVal|| y > minVal || x < -minVal || y < -minVal)
    {
      this->x = (double)x / INT16_MAX * -1;
      this->y = (double)y / INT16_MAX * -1;
    }
  else
    {
      this->x = 0;
      this->y = 0;
    }
  return (false);
}

void				JoystickMoveCommand::update(float timeSinceLastFrame)
{
  Ogre::Vector3			tmp(this->x, 0, this->y);

  this->player.moveInput(tmp, \
			 tmp * this->player.getMvtSpeed() * timeSinceLastFrame, \
			 this->x != 0 || this->y != 0);
}
