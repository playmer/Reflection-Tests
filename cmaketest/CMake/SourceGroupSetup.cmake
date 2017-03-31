################################################################################
# Project: YTE Engine
# Legal  : All content � 2013-2014 DigiPen (USA) Corporation, all rights reserved.
# Author : Joshua T. Fisher (2014)
# About  : A script for getting the subdirectories of a folder. 
#          (From Stack Overflow.)
################################################################################
Function(SourceGroupSetup currentDirectory currentSourceGroup recursed)
  ListDirectories( subDirectories ${currentDirectory} )
  ListFiles( subFiles ${currentDirectory} )

  ForEach(subDirectory ${subDirectories}) 
    If (currentSourceGroup STREQUAL " ")
      SourceGroupSetup("${currentDirectory}/${subDirectory}" "${subDirectory}" TRUE)
    Else()
      SourceGroupSetup("${currentDirectory}/${subDirectory}" "${currentSourceGroup}\\${subDirectory}" TRUE)
    EndIf()
  EndForEach()

  If (recursed)
    Source_Group(${currentSourceGroup} FILES ${subFiles})
  Else() 
    Source_Group(" " FILES ${subFiles})
  EndIf()
EndFunction()
