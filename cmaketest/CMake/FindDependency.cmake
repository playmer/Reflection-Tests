################################################################################
# Project: YTE Engine
# File   : CMakeLists.txt
# Legal  : All content � 2013-2014 DigiPen (USA) Corporation, all rights reserved.
# Author : Joshua T. Fisher (2014)
# About  : A script for getting the subdirectory of a folder. (From Stack Overflow.)
# Usage  : cmake -E PrintVersion.cmake
################################################################################
include(${Source_Root}/cmake/ListChildren.cmake)

Macro(FindDependency DependencyName StaticLibraries SharedLibraries SharedLibrariesRelative IncludeDirectory)
  Set(IndividualDependencyPath ${DependencyPath}/${DependencyName})
 
 
  Message(STATUS ${DependencyName})
  File( GLOB_RECURSE 
        StaticLibraryFiles 
        ${IndividualDependencyPath}/library/${DependencyPlatform}
        ${IndividualDependencyPath}/library/${DependencyPlatform}/*.lib)
        
  File( GLOB_RECURSE 
        SharedLibraryFiles 
        ${IndividualDependencyPath}/library/${DependencyPlatform}
        ${IndividualDependencyPath}/library/${DependencyPlatform}/*.dll)
        
  File( GLOB_RECURSE 
        SharedLibraryFilesRelative 
        RELATIVE
        ${IndividualDependencyPath}/library/${DependencyPlatform}
        ${IndividualDependencyPath}/library/${DependencyPlatform}/*.dll)
  
  Set(${StaticLibraries} ${StaticLibraryFiles})
  Set(${SharedLibraries} ${SharedLibraryFiles})
  Set(${SharedLibrariesRelative} ${SharedLibraryFilesRelative})
  Set(${IncludeDirectory} ${IndividualDependencyPath}/include)
EndMacro()


Macro(FindDependencyStatic DependencyName StaticLibrariesRelease StaticLibrariesDebug 
                           SharedLibraries SharedLibrariesRelative IncludeDirectory)
  Set(IndividualDependencyPath ${DependencyPath}/${DependencyName})
 
 
  Message(STATUS ${DependencyName})
  File( GLOB_RECURSE 
        StaticLibraryReleaseFiles 
        ${IndividualDependencyPath}/library/${DependencyPlatform}/Release
        ${IndividualDependencyPath}/library/${DependencyPlatform}/Release/*.lib)
        
  File( GLOB_RECURSE 
        StaticLibraryDebugFiles 
        ${IndividualDependencyPath}/library/${DependencyPlatform}/Debug
        ${IndividualDependencyPath}/library/${DependencyPlatform}/Debug/*.lib)
        
  File( GLOB_RECURSE 
        SharedLibraryFiles 
        ${IndividualDependencyPath}/library/${DependencyPlatform}
        ${IndividualDependencyPath}/library/${DependencyPlatform}/*.dll)
        
  File( GLOB_RECURSE 
        SharedLibraryFilesRelative 
        RELATIVE
        ${IndividualDependencyPath}/library/${DependencyPlatform}
        ${IndividualDependencyPath}/library/${DependencyPlatform}/*.dll)
  
  Set(${StaticLibrariesRelease} ${StaticLibraryReleaseFiles})
  Set(${StaticLibrariesDebug} ${StaticLibraryDebugFiles})
  Set(${SharedLibraries} ${SharedLibraryFiles})
  Set(${SharedLibrariesRelative} ${SharedLibraryFilesRelative})
  Set(${IncludeDirectory} ${IndividualDependencyPath}/include)
EndMacro()
