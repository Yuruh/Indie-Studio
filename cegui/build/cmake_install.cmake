# Install script for directory: /home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/CEGUI-0.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/CEGUI-0-OPENGL.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/CEGUI-0-OPENGL3.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/src/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/src/RendererModules/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/src/XMLParserModules/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/src/ImageCodecModules/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/src/WindowRendererSets/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/src/ScriptModules/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/cegui/src/CommonDialogs/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/application_templates/cmake_install.cmake")
  include("/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/datafiles/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/zanard_a/rendu/Projets_TEK2/cpp_indie_studio/cegui/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
