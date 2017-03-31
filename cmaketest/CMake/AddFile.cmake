################################################################################
# Project: YTE Engine
# Legal  : All content � 2013-2014 DigiPen (USA) Corporation, all rights reserved.
# Author : Joshua T. Fisher (2014)
# About  : A script for getting the subdirectory of a folder. (From Stack Overflow.)
# Usage  : cmake -E PrintVersion.cmake
################################################################################
Include(${Source_Root}/cmake/Precompiled.cmake)

Macro(EngineSystemSetup engineSystem)
  File( GLOB_RECURSE EngineSystemSource *.cpp *.c)
  File( GLOB_RECURSE EngineSystemHeaders *.hpp *.h)
  
  EngineSystemSetupDirectory(${engineSystem} ${CMAKE_CURRENT_SOURCE_DIR}
                             "${EngineSystemSource}" "${EngineSystemHeaders}")
EndMacro()

Function(EngineSystemSetupDirectory engineSystem currentDirectory sourceFiles headerFiles)
  Include_Directories(${currentDirectory} ${Engine_System_Root})
  
  # Make source groups
  SourceGroupSetup(${currentDirectory} " " FALSE)
  
  File( GLOB precompiledFile pch.c*)
  List( REMOVE_ITEM sourceFiles ${precompiledFile})

  SetPrecompiledHeader(pch.h ${precompiledFile} sourceFiles)
  Add_Library( ${engineSystem} ${sourceFiles} ${headerFiles})
  

  If (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    Target_Compile_Options(${engineSystem} PUBLIC "/MT$<$<CONFIG:Debug>:d>")
  EndIf()

    # External Dependencies
  Target_Link_Libraries(${engineSystem} ${LIBCMT_LIBRARIES} ${StaticLibraries})

  set_property( TARGET ${engineSystem} PROPERTY FOLDER "YTE")
EndFunction()


Macro(AddFile aSource aPreviousSource aFileName)
  Get_Filename_Component(DirectoryName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
  
  Set(${aPreviousSource} ${${aPreviousSource}} ${DirectoryName}/${aFileName})
EndMacro()
