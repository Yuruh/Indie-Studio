# Install script for directory: /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUICoreWindowRendererSet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUICoreWindowRendererSet.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUICoreWindowRendererSet.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999" TYPE SHARED_LIBRARY FILES "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib/libCEGUICoreWindowRendererSet.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUICoreWindowRendererSet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUICoreWindowRendererSet.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUICoreWindowRendererSet.so"
         OLD_RPATH "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUICoreWindowRendererSet.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/WindowRendererSets/Core" TYPE FILE FILES
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Scrollbar.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Titlebar.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Editbox.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/TabButton.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ScrollablePane.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/TabControl.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Tooltip.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MultiColumnList.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/PopupMenu.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/StaticText.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/StaticImage.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/FrameWindow.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Slider.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Menubar.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MultiLineEditbox.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Static.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Tree.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ProgressBar.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Default.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Listbox.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MenuItem.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ItemEntry.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Button.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Module.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ListHeaderSegment.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ItemListbox.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ListHeader.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ToggleButton.h"
    )
endif()

