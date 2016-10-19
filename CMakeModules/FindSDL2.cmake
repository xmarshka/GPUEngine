# Locate SDL2 library
# This module defines
# SDL2_FOUND, if false, do not try to link to SDL2
# SDL2_INCLUDE_DIR, where to find SDL.h
# SDL2_LIBRARY, the name of the library to link against
# SDL2_CORE_LIBRARY, path to the SDL2 library
# SDL2_MAIN_LIBRARY, path to the SDL2main library
#
# This module responds to the the flag:
# SDL2_BUILDING_LIBRARY
# If this is defined, then no SDL2main will be linked in because
# only applications need main().
# Otherwise, it is assumed you are building an application and this
# module will attempt to locate and set the the proper link flags
# as part of the returned SDL2_LIBRARY variable.
#
# Don't forget to include SDLmain.h and SDLmain.m your project for the
# OS X framework based version. (Other versions link to -lSDL2main which
# this module will try to find on your behalf.) Also for OS X, this
# module will automatically add the -framework Cocoa on your behalf.
#
#
# Additional Note: If you see an empty SDL2_CORE_LIBRARY in your configuration
# and no SDL2_LIBRARY, it means CMake did not find your SDL2 library
# (SDL2.lib, libsdl2.so, SDL2.framework, etc).
# Set SDL2_CORE_LIBRARY to point to your SDL2 library, and configure again.
# Similarly, if you see an empty SDL2_MAIN_LIBRARY, you should set this value
# as appropriate. These values are used to generate the final SDL2_LIBRARY
# variable, but when these values are unset, SDL2_LIBRARY does not get created.
#
#
# $SDL2DIR is an environment variable that would
# correspond to the ./configure --prefix=$SDL2DIR
# used in building SDL2.
# l.e.galup  9-20-02
#
# Modified by Eric Wing.
# Added code to assist with automated building by using environmental variables
# and providing a more controlled/consistent search behavior.
# Added new modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).
# Also corrected the header search path to follow "proper" SDL guidelines.
# Added a search for SDL2main which is needed by some platforms.
# Added a search for threads which is needed by some platforms.
# Added needed compile switches for MinGW.
#
# Modified by PCJohn (Jan Peciva):
# Look for config file first. Create SDL2 target. Print GPUEngine style message.
# Updated code formatting to match the one used in GPUEngine.
#
# On OSX, this will prefer the Framework version (if found) over others.
# People will have to manually change the cache values of
# SDL2_LIBRARY to override this selection or set the CMake environment
# CMAKE_INCLUDE_PATH to modify the search paths.
#
# Note that the header path has changed from SDL2/SDL.h to just SDL.h
# This needed to change because "proper" SDL convention
# is #include "SDL.h", not <SDL2/SDL.h>. This is done for portability
# reasons because not all systems place things in SDL2/ (see FreeBSD).

#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)


# try config-based find first
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)

# SDL2 (seen on version 2.0.4) does not create target but provides paths.
# We will adjust the path names and create target.
# (No SDL version information is present in sdl2-config.cmake, at least on version 2.0.4).
if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND AND NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})

      # variables
      set(SDL2_INCLUDE_DIR "${SDL2_INCLUDE_DIRS}")
      unset(SDL2_INCLUDE_DIRS)
      set(SDL2_LIBRARY ${SDL2_LIBDIR}/libSDL2.so)
      unset(SDL2_LIBRARIES)

      # target
      add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
      set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
         INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
         INTERFACE_LINK_LIBRARIES "${SDL2_LIBRARY}"
      )
   endif()
endif()


# use regular old-style approach
if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   set(SDL2_SEARCH_PATHS
      ~/Library/Frameworks
      /Library/Frameworks
      /usr/local
      /usr
      /sw # Fink
      /opt/local # DarwinPorts
      /opt/csw # Blastwave
      /opt
   )

   find_path(SDL2_INCLUDE_DIR SDL.h
      HINTS
      $ENV{SDL2DIR}
      PATH_SUFFIXES include/SDL2 include
      PATHS ${SDL2_SEARCH_PATHS}
   )

   find_library(SDL2_CORE_LIBRARY
      NAMES SDL2
      HINTS
      $ENV{SDL2DIR}
      PATH_SUFFIXES lib64 lib
      PATHS ${SDL2_SEARCH_PATHS}
   )

   # Non-OS X framework versions expect you to also dynamically link to
   # SDL2main. This is mainly for Windows and OS X. Other (Unix) platforms
   # seem to provide SDL2main for compatibility even though they don't
   # necessarily need it.
   set(NEED_MAIN_LIB NOT SDL2_BUILDING_LIBRARY AND NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework")
   if(NEED_MAIN_LIB)

      find_library(SDL2_MAIN_LIBRARY
         NAMES SDL2main
         HINTS
         $ENV{SDL2DIR}
         PATH_SUFFIXES lib64 lib
         PATHS ${SDL2_SEARCH_PATHS}
      )

   endif()

   # SDL2 may require threads on your system.
   # The Apple build may not need an explicit flag because one of the
   # frameworks may already provide it.
   # But for non-OSX systems, I will use the CMake Threads package.
   if(NOT APPLE)
      find_package(Threads)
   endif()

   if(SDL2_CORE_LIBRARY AND
      (NOT NEED_MAIN_LIB OR SDL2_MAIN_LIBRARY))

      # make a copy of the variable before we start to modify it
      set(SDL2_LIBRARY_TEMP ${SDL2_CORE_LIBRARY})

      # For SDL2main
      if(NEED_MAIN_LIB)
         set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${SDL2_MAIN_LIBRARY})
      endif()

      # MinGW needs mingw32
      if(MINGW)
         set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} mingw32)
      endif()

      # For OS X, SDL2 uses Cocoa as a backend so it must link to Cocoa.
      # CMake doesn't display the -framework Cocoa string in the UI even
      # though it actually is there if I modify a pre-used variable.
      # I think it has something to do with the CACHE STRING.
      # So I use a temporary variable until the end so I can set the
      # "real" variable in one-shot.
      if(APPLE)
         set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} "-framework Cocoa")
      endif()

      # For threads, as mentioned Apple doesn't need this.
      # In fact, there seems to be a problem if I used the Threads package
      # and try using this line, so I'm just skipping it entirely for OS X.
      if(NOT APPLE)
         set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
      endif()

      # Set the final string here so the GUI reflects the final state.
      set(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP} CACHE STRING "SDL2 Libraries to be linked against" FORCE)

   else()

      # if SDL2_CORE_LIBRARY and SDL2_MAIN_LIBRARY are not properly set, remove SDL2_LIBRARY variable
      unset(SDL2_LIBRARY CACHE)

   endif()

   # set *_FOUND flag
   if(SDL2_INCLUDE_DIR AND SDL2_LIBRARY)
      set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
   endif()

   # target for cmake 3.0.0 and newer
   if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)
      if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
         if(NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
            add_library(${CMAKE_FIND_PACKAGE_NAME} INTERFACE IMPORTED)
            set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
               INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
               INTERFACE_LINK_LIBRARIES "${SDL2_LIBRARY}"
            )
         endif()
      endif()
   endif()

endif()

# message
include(GEMacros)
ge_report_find_status("${SDL2_LIBRARY}")
