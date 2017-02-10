//
// SDL_CEGUI_Events.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src
// 
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
// 
// Started on  Sun May 22 22:16:23 2016 Martin Desrumaux
// Last update Tue May 24 14:39:44 2016 Antoine Lempereur
//

#include	<iostream>
#include	"Events/SDL_CEGUI_Events.hpp"

SDL_CEGUI_Events::SDL_CEGUI_Events()
{
  this->initKeyMap();
  this->initMouseMap();
  _functions[SDL_MOUSEBUTTONDOWN] = &SDL_CEGUI_Events::mouseButtonDown;
  _functions[SDL_MOUSEBUTTONUP] = &SDL_CEGUI_Events::mouseButtonUp;
  _functions[SDL_MOUSEWHEEL] = &SDL_CEGUI_Events::mouseWheel;
  _functions[SDL_MOUSEMOTION] = &SDL_CEGUI_Events::mouseMotion;
  _functions[SDL_KEYDOWN] = &SDL_CEGUI_Events::keyDown;
  _functions[SDL_KEYUP] = &SDL_CEGUI_Events::keyUp;
}

SDL_CEGUI_Events::~SDL_CEGUI_Events()
{
}

void			SDL_CEGUI_Events::initMouseMap()
{
  this->_mousemap[SDL_BUTTON_LEFT] = CEGUI::LeftButton;
  this->_mousemap[SDL_BUTTON_MIDDLE] = CEGUI::MiddleButton;
  this->_mousemap[SDL_BUTTON_RIGHT] = CEGUI::RightButton;
}

void			SDL_CEGUI_Events::initKeyMap()
{
  this->_keymap[SDLK_1] = CEGUI::Key::One;
  this->_keymap[SDLK_2] = CEGUI::Key::Two;
  this->_keymap[SDLK_3] = CEGUI::Key::Three;
  this->_keymap[SDLK_4] = CEGUI::Key::Four;
  this->_keymap[SDLK_5] = CEGUI::Key::Five;
  this->_keymap[SDLK_6] = CEGUI::Key::Six;
  this->_keymap[SDLK_7] = CEGUI::Key::Seven;
  this->_keymap[SDLK_8] = CEGUI::Key::Eight;
  this->_keymap[SDLK_9] = CEGUI::Key::Nine;
  this->_keymap[SDLK_0] = CEGUI::Key::Zero;

  this->_keymap[SDLK_q] = CEGUI::Key::Q;
  this->_keymap[SDLK_w] = CEGUI::Key::W;
  this->_keymap[SDLK_e] = CEGUI::Key::E;
  this->_keymap[SDLK_r] = CEGUI::Key::R;
  this->_keymap[SDLK_t] = CEGUI::Key::T;
  this->_keymap[SDLK_y] = CEGUI::Key::Y;
  this->_keymap[SDLK_u] = CEGUI::Key::U;
  this->_keymap[SDLK_i] = CEGUI::Key::I;
  this->_keymap[SDLK_o] = CEGUI::Key::O;
  this->_keymap[SDLK_p] = CEGUI::Key::P;
  this->_keymap[SDLK_a] = CEGUI::Key::A;
  this->_keymap[SDLK_s] = CEGUI::Key::S;
  this->_keymap[SDLK_d] = CEGUI::Key::D;
  this->_keymap[SDLK_f] = CEGUI::Key::F;
  this->_keymap[SDLK_g] = CEGUI::Key::G;
  this->_keymap[SDLK_h] = CEGUI::Key::H;
  this->_keymap[SDLK_j] = CEGUI::Key::J;
  this->_keymap[SDLK_k] = CEGUI::Key::K;
  this->_keymap[SDLK_l] = CEGUI::Key::L;
  this->_keymap[SDLK_z] = CEGUI::Key::Z;
  this->_keymap[SDLK_x] = CEGUI::Key::X;
  this->_keymap[SDLK_c] = CEGUI::Key::C;
  this->_keymap[SDLK_v] = CEGUI::Key::V;
  this->_keymap[SDLK_b] = CEGUI::Key::B;
  this->_keymap[SDLK_n] = CEGUI::Key::N;
  this->_keymap[SDLK_m] = CEGUI::Key::M;

  this->_keymap[SDLK_COMMA] = CEGUI::Key::Comma;
  this->_keymap[SDLK_PERIOD] = CEGUI::Key::Period;
  this->_keymap[SDLK_SLASH] = CEGUI::Key::Slash;
  this->_keymap[SDLK_BACKSLASH] = CEGUI::Key::Backslash;
  this->_keymap[SDLK_MINUS] = CEGUI::Key::Minus;
  this->_keymap[SDLK_EQUALS] = CEGUI::Key::Equals;
  this->_keymap[SDLK_SEMICOLON] = CEGUI::Key::Semicolon;
  this->_keymap[SDLK_LEFTBRACKET] = CEGUI::Key::LeftBracket;
  this->_keymap[SDLK_RIGHTBRACKET] = CEGUI::Key::RightBracket;
  this->_keymap[SDLK_QUOTE] = CEGUI::Key::Apostrophe;
  this->_keymap[SDLK_BACKQUOTE] = CEGUI::Key::Grave;

  this->_keymap[SDLK_RETURN] = CEGUI::Key::Return;
  this->_keymap[SDLK_SPACE] = CEGUI::Key::Space;
  this->_keymap[SDLK_BACKSPACE] = CEGUI::Key::Backspace;
  this->_keymap[SDLK_TAB] = CEGUI::Key::Tab;

  this->_keymap[SDLK_ESCAPE] = CEGUI::Key::Escape;
  this->_keymap[SDLK_PAUSE] = CEGUI::Key::Pause;
  this->_keymap[SDLK_SYSREQ] = CEGUI::Key::SysRq;
  this->_keymap[SDLK_POWER] = CEGUI::Key::Power;

  this->_keymap[SDLK_NUMLOCKCLEAR] = CEGUI::Key::NumLock;
  this->_keymap[SDLK_SCROLLLOCK] = CEGUI::Key::ScrollLock;

  this->_keymap[SDLK_F1] = CEGUI::Key::F1;
  this->_keymap[SDLK_F2] = CEGUI::Key::F2;
  this->_keymap[SDLK_F3] = CEGUI::Key::F3;
  this->_keymap[SDLK_F4] = CEGUI::Key::F4;
  this->_keymap[SDLK_F5] = CEGUI::Key::F5;
  this->_keymap[SDLK_F6] = CEGUI::Key::F6;
  this->_keymap[SDLK_F7] = CEGUI::Key::F7;
  this->_keymap[SDLK_F8] = CEGUI::Key::F8;
  this->_keymap[SDLK_F9] = CEGUI::Key::F9;
  this->_keymap[SDLK_F10] = CEGUI::Key::F10;
  this->_keymap[SDLK_F11] = CEGUI::Key::F11;
  this->_keymap[SDLK_F12] = CEGUI::Key::F12;
  this->_keymap[SDLK_F13] = CEGUI::Key::F13;
  this->_keymap[SDLK_F14] = CEGUI::Key::F14;
  this->_keymap[SDLK_F15] = CEGUI::Key::F15;

  this->_keymap[SDLK_LCTRL] = CEGUI::Key::LeftControl;
  this->_keymap[SDLK_LALT] = CEGUI::Key::LeftAlt;
  this->_keymap[SDLK_LSHIFT] = CEGUI::Key::LeftShift;
  //this->_keymap[SDLK_LSUPER] = CEGUI::Key::LeftWindows;
  this->_keymap[SDLK_RCTRL] = CEGUI::Key::RightControl;
  this->_keymap[SDLK_RALT] = CEGUI::Key::RightAlt;
  this->_keymap[SDLK_RSHIFT] = CEGUI::Key::RightShift;
  //this->_keymap[SDLK_RSUPER] = CEGUI::Key::RightWindows;
  this->_keymap[SDLK_MENU] = CEGUI::Key::AppMenu;

  //this->_keymap[SDLK_KP0] = CEGUI::Key::Numpad0;
  //this->_keymap[SDLK_KP1] = CEGUI::Key::Numpad1;
  //this->_keymap[SDLK_KP2] = CEGUI::Key::Numpad2;
  //this->_keymap[SDLK_KP3] = CEGUI::Key::Numpad3;
  //this->_keymap[SDLK_KP4] = CEGUI::Key::Numpad4;
  //this->_keymap[SDLK_KP5] = CEGUI::Key::Numpad5;
  //this->_keymap[SDLK_KP6] = CEGUI::Key::Numpad6;
  //this->_keymap[SDLK_KP7] = CEGUI::Key::Numpad7;
  //this->_keymap[SDLK_KP8] = CEGUI::Key::Numpad8;
  //this->_keymap[SDLK_KP9] = CEGUI::Key::Numpad9;
  this->_keymap[SDLK_KP_PERIOD] = CEGUI::Key::Decimal;
  this->_keymap[SDLK_KP_PLUS] = CEGUI::Key::Add;
  this->_keymap[SDLK_KP_MINUS] = CEGUI::Key::Subtract;
  this->_keymap[SDLK_KP_MULTIPLY] = CEGUI::Key::Multiply;
  this->_keymap[SDLK_KP_DIVIDE] = CEGUI::Key::Divide;
  this->_keymap[SDLK_KP_ENTER] = CEGUI::Key::NumpadEnter;

  this->_keymap[SDLK_UP] = CEGUI::Key::ArrowUp;
  this->_keymap[SDLK_LEFT] = CEGUI::Key::ArrowLeft;
  this->_keymap[SDLK_RIGHT] = CEGUI::Key::ArrowRight;
  this->_keymap[SDLK_DOWN] = CEGUI::Key::ArrowDown;

  this->_keymap[SDLK_HOME] = CEGUI::Key::Home;
  this->_keymap[SDLK_END] = CEGUI::Key::End;
  this->_keymap[SDLK_PAGEUP] = CEGUI::Key::PageUp;
  this->_keymap[SDLK_PAGEDOWN] = CEGUI::Key::PageDown;
  this->_keymap[SDLK_INSERT] = CEGUI::Key::Insert;
  this->_keymap[SDLK_DELETE] = CEGUI::Key::Delete;
}

bool			SDL_CEGUI_Events::sendCEGUIEvents(const SDL_Event &event)
{
  void (SDL_CEGUI_Events::*func)();

  this->_ceguiContext = &CEGUI::System::getSingleton().getDefaultGUIContext();
  this->_event = event;
  this->_quit = false;
  try {
    func = this->_functions.at(event.type);
  } catch (std::out_of_range) {
    //    std::cerr << "Event: Non-existing element" << std::endl;
    return (this->_quit);
  }
    ((this)->*(func))();
  return (this->_quit);
}

void			SDL_CEGUI_Events::mouseButtonDown()
{
  CEGUI::MouseButton	btn;

  try {
    btn = this->_mousemap.at(this->_event.button.button);
  } catch (std::out_of_range) {
    std::cerr << "mouseBtn: Non-existing element" << std::endl;
    return;
  }
  this->_ceguiContext->injectMouseButtonDown(btn);
}

void			SDL_CEGUI_Events::mouseButtonUp()
{
  CEGUI::MouseButton	btn;

  try {
    btn = this->_mousemap.at(this->_event.button.button);
  } catch (std::out_of_range) {
    std::cerr << "mouseBtn: Non-existing element" << std::endl;
    return;
  }
  this->_ceguiContext->injectMouseButtonUp(btn);
}

void			SDL_CEGUI_Events::mouseMotion()
{
  this->_ceguiContext->injectMousePosition(static_cast<float>(this->_event.motion.x), \
				     static_cast<float>(this->_event.motion.y));
}

void			SDL_CEGUI_Events::mouseWheel()
{
  if (this->_event.wheel.direction == SDL_MOUSEWHEEL_NORMAL)
    this->_ceguiContext->injectMouseWheelChange(this->_event.wheel.y);
  else if (this->_event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
    this->_ceguiContext->injectMouseWheelChange(this->_event.wheel.y * -1);
}

void			SDL_CEGUI_Events::keyDown()
{
  CEGUI::Key::Scan	key;

  try {
    key = this->_keymap.at(this->_event.key.keysym.sym);
  } catch (std::out_of_range) {
    std::cerr << "key: Non-existing element" << std::endl;
    return;
  }
  this->_ceguiContext->injectKeyDown(key);
  // TODO: .injectChar() ?
}

void			SDL_CEGUI_Events::keyUp()
{
  CEGUI::Key::Scan	key;

  try {
    key = this->_keymap.at(this->_event.key.keysym.sym);
  } catch (std::out_of_range) {
    std::cerr << "key: Non-existing element" << std::endl;
    return;
  }
  this->_ceguiContext->injectKeyUp(key);
  // TODO: .injectChar() ?
}

// TODO: SDL_VIDEO_RESIZE
//CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(e.resize.w,e.resize.h));
//TODO: Joystick
