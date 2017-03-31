FIND_PATH(FMOD_INCLUDE_DIR fmod_studio.h
  HINTS
  $ENV{FMOD_INC}
  PATH_SUFFIXES include/FMOD include FMOD
  i686-w64-mingw32/include/FMOD
  x86_64-w64-mingw32/include/FMOD
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/FMOD
  /usr/include/FMOD
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(FMOD_STUDIO_LIBRARY_TEMP
  NAMES
  fmodstudioL64.so fmodstudioL64.dll
  HINTS
  $ENV{FMOD}
  PATH_SUFFIXES lib64 lib
  lib/x64
  x86_64-w64-mingw32/lib
  PATHS
  /usr/local/lib/FMOD
  /sw
  /opt/local
  /opt/csw
  /opt
)



FIND_LIBRARY(FMOD_LIBRARY_TEMP
  NAMES
  fmodL64.so fmodL64.dll
  HINTS
  $ENV{FMOD}
  PATH_SUFFIXES lib64 lib
  lib/x64
  x86_64-w64-mingw32/lib
  PATHS
  /usr/local/lib/FMOD
  /sw
  /opt/local
  /opt/csw
  /opt
)

if (${CMAKE_GENERATOR} STREQUAL "Visual Studio 12 2013 Win64" OR
	${CMAKE_GENERATOR} STREQUAL "Visual Studio 14 Win64")
  set(FMOD_STUDIO_LIBRARY_TEMP "${SOURCE_ROOT}/dep/lib/x64/fmodstudioL64_vc.lib")
  set(FMOD_LIBRARY_TEMP "${SOURCE_ROOT}/dep/lib/x64/fmodL64_vc.lib")
elseif (${CMAKE_GENERATOR} STREQUAL "Visual Studio 12 2013" OR
	${CMAKE_GENERATOR} STREQUAL "Visual Studio 14")
  set(FMOD_STUDIO_LIBRARY_TEMP "${SOURCE_ROOT}/dep/lib/x86/fmodstudioL_vc.lib")
  set(FMOD_LIBRARY_TEMP "${SOURCE_ROOT}/dep/lib/x86/fmodL_vc.lib")
endif()

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lSDL2main -lSDL2 -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
  SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)

SET(FMOD_FOUND "NO")

IF(FMOD_LIBRARY_TEMP AND FMOD_STUDIO_LIBRARY_TEMP)
    # For OS X, SDL2 uses Cocoa as a backend so it must link to Cocoa.
    # CMake doesn't display the -framework Cocoa string in the UI even
    # though it actually is there if I modify a pre-used variable.
    # I think it has something to do with the CACHE STRING.
    # So I use a temporary variable until the end so I can set the
    # "real" variable in one-shot.
    IF(APPLE)
      SET(FMOD_LIBRARY_TEMP ${FMOD_LIBRARY_TEMP} "-framework Cocoa")
    ENDIF(APPLE)

    # For MinGW library
    IF(MINGW)
      SET(FMOD_LIBRARY_TEMP ${MINGW32_LIBRARY} ${FMOD_LIBRARY_TEMP})
    ENDIF(MINGW)

    # Set the final string here so the GUI reflects the final state.
    SET(FMOD_LIBRARY ${FMOD_LIBRARY_TEMP} CACHE STRING "Where the FMOD Library can be found")
    SET(FMOD_STUDIO_LIBRARY ${FMOD_STUDIO_LIBRARY_TEMP} CACHE STRING "Where the FMOD Library can be found")
    # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
    SET(FMOD_LIBRARY_TEMP "${FMOD_LIBRARY_TEMP}" CACHE INTERNAL "")

    SET(FMOD_FOUND "YES")
ENDIF(FMOD_LIBRARY_TEMP AND FMOD_STUDIO_LIBRARY_TEMP)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(FMOD REQUIRED_VARS FMOD_LIBRARY FMOD_INCLUDE_DIR)
