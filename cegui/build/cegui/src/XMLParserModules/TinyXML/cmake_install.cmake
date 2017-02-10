# Install script for directory: /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/XMLParserModules/TinyXML

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUITinyXMLParser.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUITinyXMLParser.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUITinyXMLParser.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999" TYPE SHARED_LIBRARY FILES "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib/libCEGUITinyXMLParser.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUITinyXMLParser.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUITinyXMLParser.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUITinyXMLParser.so"
         OLD_RPATH "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cegui-0.9999/libCEGUITinyXMLParser.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/XMLParserModules/TinyXML" TYPE FILE FILES
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/XMLParserModules/TinyXML/../../../include/CEGUI/XMLParserModules/TinyXML/XMLParserModule.h"
    "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/cegui/src/XMLParserModules/TinyXML/../../../include/CEGUI/XMLParserModules/TinyXML/XMLParser.h"
    )
endif()

