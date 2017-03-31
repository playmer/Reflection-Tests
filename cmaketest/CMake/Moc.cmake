################################################################################
# Project: YTE Engine
# Legal  : All content ? 2013-2014 DigiPen (USA) Corporation, all rights reserved.
# Author : Joshua T. Fisher (2014)
# About  : A script for getting the subdirectory of a folder. (From Stack Overflow.)
################################################################################
Macro(MocHeadersResult result currentDirectory)
  File( GLOB_RECURSE sourceFiles *.hpp *.h )

  Set(resultList "")

  ForEach(sourceFile ${sourceFiles})    
    Get_Filename_Component(fileName ${sourceFile} NAME_WE)
    
    List(APPEND resultList ${currentDirectory}/moc_${fileName}.cpp)
    
    File(WRITE  ${currentDirectory}/moc_${fileName}.cpp "//File intentionally left blank.")
  EndForEach()
  
  Set(${result} ${resultList})
EndMacro()

Macro(MocHeaders currentDirectory outDirectory target)
  Set(MocExe ${Source_Root}/Dependencies/Qt/binary/moc.exe)

  File( GLOB_RECURSE sourceFiles *.hpp *.h )

  ForEach(sourceFile ${sourceFiles})
    Get_Filename_Component(fileName ${sourceFile} NAME_WE)
    
    Add_Custom_Command(TARGET ${target}
                       PRE_BUILD
                       COMMAND ${MocExe} 
                       ARGS ${sourceFile}
                            -o ${outDirectory}/moc_${fileName}.cpp)
  EndForEach()
EndMacro()

Macro(MocImplementationResult result currentDirectory)
  File( GLOB_RECURSE sourceFiles *.cpp *.c )
  
  Set(resultList "")

  ForEach( sourceFile ${sourceFiles} )
    Get_Filename_Component(fileName ${sourceFile} NAME_WE)  
    
    List(APPEND resultList ${currentDirectory}/${fileName}.moc)
    
    File(WRITE  ${currentDirectory}/${fileName}.moc "//File intentionally left blank.")
  EndForEach()
  
  Set(${result} ${resultList})
EndMacro()

Macro(MocImplementation currentDirectory outDirectory target)
  Set( MocExe ${Source_Root}/Dependencies/Qt/binary/moc.exe )

  File( GLOB_RECURSE sourceFiles *.cpp *.c )
  
  ForEach( sourceFile ${sourceFiles} )
    Get_Filename_Component(fileName ${sourceFile} NAME_WE)
    
    Add_Custom_Command(TARGET ${target}
                       PRE_BUILD
                       COMMAND ${MocExe} 
                       ARGS ${sourceFile}
                            -o ${outDirectory}/${fileName}.moc)
  EndForEach()
EndMacro()

Macro(Moc currentDirectory outDirectory target)
  MocImplementation(${currentDirectory} ${outDirectory} ${target})
  MocHeaders(${currentDirectory} ${outDirectory} ${target})
EndMacro()