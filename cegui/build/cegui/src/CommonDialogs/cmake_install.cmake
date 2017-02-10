# Install script for directory: /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/CommonDialogs

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
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCEGUICommonDialogs-0.so.1.5.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCEGUICommonDialogs-0.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCEGUICommonDialogs-0.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib/libCEGUICommonDialogs-0.so.1.5.1"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib/libCEGUICommonDialogs-0.so.1"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib/libCEGUICommonDialogs-0.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCEGUICommonDialogs-0.so.1.5.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCEGUICommonDialogs-0.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCEGUICommonDialogs-0.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/CommonDialogs" TYPE FILE FILES "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/CommonDialogs/../../include/CEGUI/CommonDialogs/Module.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/CommonDialogs/ColourPicker" TYPE FILE FILES
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/CommonDialogs/../../include/CEGUI/CommonDialogs/ColourPicker/Types.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/CommonDialogs/../../include/CEGUI/CommonDialogs/ColourPicker/Controls.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/CommonDialogs/../../include/CEGUI/CommonDialogs/ColourPicker/ColourPicker.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/CommonDialogs/../../include/CEGUI/CommonDialogs/ColourPicker/Conversions.h"
    )
endif()

