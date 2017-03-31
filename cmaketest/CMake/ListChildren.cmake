################################################################################
# Project: YTE Engine
# File   : CMakeLists.txt
# Legal  : All content © 2013-2014 DigiPen (USA) Corporation, all rights reserved.
# Author : Joshua T. Fisher (2014)
# About  : A script for getting the subdirectory of a folder. (From Stack Overflow.)
################################################################################
MACRO(ListDirectories result currentDirectory)
  File(GLOB children RELATIVE ${currentDirectory} ${currentDirectory}/*)
  Set(dirlist "")
  
  ForEach(child ${children})
    If(IS_DIRECTORY ${currentDirectory}/${child})
      List(APPEND dirlist ${child})
    EndIf()
  EndForEach()
  
  Set(${result} ${dirlist})
ENDMACRO()

MACRO(ListFiles result currentDirectory)
  File(GLOB children ${currentDirectory} 
          ${currentDirectory}/*.cpp ${currentDirectory}/*.c
          ${currentDirectory}/*.hpp ${currentDirectory}/*.h)
  Set(dirlist "")
  
  ForEach(child ${children})
    If(NOT IS_DIRECTORY ${currentDirectory}/${child})
      List(APPEND dirlist ${child})
    EndIf()
  EndForEach()
  
  Set(${result} ${dirlist})
ENDMACRO()