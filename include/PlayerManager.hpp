//
// PlayerManager.cpp for indie_studio in /home/desrum_m/code/epitech/S4/cpp_indie_studio/src
//
// Made by Martin Desrumaux
// Login   <desrum_m@epitech.net>
//
// Started on  Tue May 24 13:41:57 2016 Martin Desrumaux
// Last update Fri Jun  3 21:17:41 2016 Wasta-Geek
//

#ifndef		PLAYER_MANAGER_HPP_
# define	PLAYER_MANAGER_HPP_

# include	<map>
# include	"PlayableClass/Warrior.hpp"
# include	"PlayableClass/Valkyrie.hpp"
# include	"PlayableClass/Elf.hpp"
# include	"PlayableClass/Mage.hpp"
# include	"Events/Controller.hpp"
# include	"Parsing/Map.hpp"

typedef Player *createPlayerInstance(const Controller &type);

class PlayerFactory
{
  public:
    PlayerFactory();
    Player		*create(const ControllerPlayer &type);
  private:
    std::map<ClassPlayer, createPlayerInstance *> funcs;
};

class PlayerManager
{
  public:
    PlayerManager(std::vector<ControllerPlayer> &cPlayers);
    ~PlayerManager();
  public:
    void		initGfx(Ogre::SceneManager *sceneManager);
    void		frameUpdate(float timeSinceLastFrame);
  const std::map<ClassPlayer, Player*>	&getMap() const;
    Player		*getPlayer(ClassPlayer);
  void			placePlayers(Ogre::Vector3 const&, Cardinal);
  bool			areAllDead() const;
  private:
    std::map<ClassPlayer, Player*> _players;
    PlayerFactory		  _playerFactory;
};

#endif		// !PLAYER_MANAGER_HPP_
