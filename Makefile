##
## Makefile for  in /home/descam_d/workspace/cpp_nanotekspice
##
## Made by Corentin Descamps
## Login   <descam_d@epitech.net>
##
## Started on  Mon Feb  8 12:01:38 2016 Corentin Descamps
## Last update Sun Jun  5 19:12:39 2016 Corentin Descamps
##

NAME		=	gauntlet

SRC		=	src/main.cpp 			\
			src/Elem.cpp 			\
			src/ACharacter.cpp 		\
			src/Light.cpp 			\
			src/Parsing/Map.cpp 		\
			src/Parsing/AParser.cpp 	\
			src/Parsing/ParserMap.cpp 	\
			src/Parsing/ParserConfig.cpp	\
			src/Parsing/ParserScore.cpp	\
			src/Parsing/ParserError.cpp	\
			src/Application.cpp 		\
			src/AnimatedElem.cpp 		\
			src/Errors.cpp 				\
			src/Gauntlet.cpp 		\
			src/Room.cpp 			\
			src/CameraManager.cpp		\
			src/RoomGenerator.cpp		\
			src/GUI.cpp					\
			src/AnimatedLayout.cpp		\
			src/PlayableClass/Player.cpp	\
			src/PlayableClass/Warrior.cpp	\
			src/Audio/AudioSystem.cpp	\
			src/Audio/AudioEffect.cpp	\
			src/Events/SDL_CEGUI_Events.cpp	\
			src/Events/Commands.cpp		\
			src/Events/MoveCommands.cpp	\
			src/Events/InputHandler.cpp 	\
			src/Events/PlayerInputHandler.cpp \
			src/AI/MeleeAI.cpp		\
			src/AI/RangeAI.cpp		\
			src/AI/PathFinding.cpp		\
			src/Mobs/MobFactory.cpp		\
			src/Mobs/Zombie.cpp		\
			src/Mobs/Boss.cpp		\
			src/CollisionSingleton.cpp	\
			src/Mobs/ANonPlayable.cpp	\
			src/Animation.cpp		\
			src/PlayerManager.cpp		\
			src/PlayableClass/Valkyrie.cpp	\
			src/PlayableClass/Elf.cpp	\
			src/PlayableClass/Mage.cpp	\
			src/Projectile.cpp		\
			src/BouncingProjectile.cpp	\
			src/Mobs/Archer.cpp		\
			src/AI/PlayerAI.cpp		\
			src/Pickups/Pickup.cpp		\
			src/Pickups/Gold.cpp		\
			src/Pickups/PickupFactory.cpp	\
			src/Pickups/HealthPotion.cpp	\
			src/Pickups/AttackPotion.cpp	\
			src/Pickups/SpeedBoots.cpp	\

OBJ		=	$(SRC:.cpp=.o)

CC		=	g++

CPPFLAGS	=	-I /usr/local/include
CPPFLAGS	+=	-I /usr/include/SDL
CPPFLAGS	+=	-I /usr/include/cegui-0/
CPPFLAGS	+=	-I /usr/local/include/cegui-0/
CPPFLAGS	+=	-I include/

CXXFLAGS	+= 	$(INC)
CXXFLAGS	+= 	-std=c++11
CXXFLAGS	+= 	-W -Wall -Wextra
CXXFLAGS	+=	$(shell pkg-config --cflags sdl2)

ifeq ($(DEBUG), yes)
  CXXFLAGS	+=	-g
endif

LDFLAGS		+= 	-pthread
LDFLAGS		+= 	-lboost_system
# This aims to be used if you manually installed libs
LDFLAGS		+= 	-L/usr/local/lib
LDFLAGS    	+= 	-lOgreOverlay
LDFLAGS		+= 	-lCEGUIOgreRenderer-0
LDFLAGS		+= 	-lCEGUIBase-0
LDFLAGS		+= 	-lOgreMain
LDFLAGS		+= 	-lOIS
LDFLAGS		+= 	-lOgreTerrain
LDFLAGS		+=	-lsfml-system
LDFLAGS		+=	-lsfml-audio
LDFLAGS		+=	$(shell pkg-config --libs sdl2)

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:		clean
	rm -rf $(NAME)

re:		fclean all
