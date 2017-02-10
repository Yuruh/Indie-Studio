//
// SDL_CEGUI_Events.hpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/include
// 
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
// 
// Started on  Sun May 22 20:21:56 2016 Martin Desrumaux
// Last update Mon May 23 01:31:49 2016 Martin Desrumaux
//

#ifndef		SDL_CEGUI_Events_HPP_
# define	SDL_CEGUI_Events_HPP_

# include 	<CEGUI/CEGUI.h>
# define	Display X11_Display_Conflict_Fix
# include	<SDL.h>
# undef		True
# undef		False
# undef		None
# undef		Display

class SDL_CEGUI_Events
{
  public:
    SDL_CEGUI_Events();
    ~SDL_CEGUI_Events();
  public:
    bool		sendCEGUIEvents(const SDL_Event &event);
  private:
    void		initKeyMap();
    void		initMouseMap();
  private:
    void		mouseButtonDown();
    void		mouseButtonUp();
    void		mouseWheel();
    void		mouseMotion();
    void		keyDown();
    void		keyUp();
  private:
    std::map<SDL_Keycode, CEGUI::Key::Scan>			_keymap;
    std::map<Uint8, CEGUI::MouseButton>				_mousemap;
    std::map<Uint32, void (SDL_CEGUI_Events::*)()>		_functions;
    SDL_Event							_event;
    bool							_quit;
    CEGUI::GUIContext						*_ceguiContext;
};

#endif		// !SDL_CEGUI_Events_HPP_
