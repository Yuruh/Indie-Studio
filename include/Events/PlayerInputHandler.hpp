//
// PlayerInputHandler.hpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include/Events
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Mon May 23 02:42:18 2016 Martin Desrumaux
// Last update Wed Jun 01 02:03:31 2016 Martin Desrumaux
//

#ifndef			PLAYER_INPUT_HANDLER_HPP_
# define		PLAYER_INPUT_HANDLER_HPP_

# include		"Events/Controller.hpp"
# include		"PlayableClass/Player.hpp"

class	IMoveCommand;
class	AttackCommand;
class	SpecialAttackCommand;
class	Player;

class PlayerInputHandler
{
  public:
    PlayerInputHandler(Player &player, const Controller &controller);
    ~PlayerInputHandler();
  public:
    void					update(float timeSinceLastFrame);
  private:
    std::vector<unsigned int>			layout;
    IMoveCommand				*movements;
    AttackCommand				*attacks;
    SpecialAttackCommand			*specialAttacks;
};

#endif			// !PLAYER_INPUT_HANDLER_HPP_
