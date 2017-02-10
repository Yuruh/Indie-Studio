//
// InputHandler.hpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include
// 
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
// 
// Started on  Fri May 20 15:51:44 2016 Martin Desrumaux
// Last update Mon May 23 23:45:17 2016 Martin Desrumaux
//

#ifndef		INPUT_HANDLER_H
# define	INPUT_HANDLER_H

# include	"Events/Commands.hpp"
# include	"Events/SDL_CEGUI_Events.hpp"

// Singleton class

class InputHandler
{
  public:
    InputHandler();
    ~InputHandler();
  public:
    void			handleInput();
    unsigned int		addInputHandler(ICommand *cmd);
    void			removeInputHandler(unsigned int id);
  private:
    std::map<unsigned int, ICommand *>		mapped;
    static InputHandler				*inputHandler_instance;
  public:
    static InputHandler				*instance();
    SDL_CEGUI_Events				_ceguiEvents;
};

#endif		// !INPUT_HANDLER_HPP_
