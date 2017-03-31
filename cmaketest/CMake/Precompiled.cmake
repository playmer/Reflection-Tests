################################################################################
# Project: RG3D Engine
# File   : CMakeLists.txt
# Legal  : All content © 2013-2014 DigiPen (USA) Corporation, all rights reserved.
# Author : Trent Reed (2013)
# About  : A script for printing the current source number.
# Usage  : cmake -E PrintVersion.cmake
################################################################################
Macro(SetPrecompiledHeader precompiledHeader precompiledSource sourceFiles)
  if(MSVC AND ${Analysis})
    Get_Filename_Component(pchheaderBasename ${precompiledHeader} NAME_WE)
    Set(precompiledBinary "$(IntDir)${pchheaderBasename}.pch")
    Set(source ${${sourceFiles}})

    Set_Source_Files_Properties(${precompiledSource}
                                PROPERTIES 
                                  COMPILE_FLAGS 
                                    "/Yc\"\"${precompiledHeader}\"\" /Fp\"${precompiledBinary}\""
                                  OBJECT_OUTPUTS 
                                    "${precompiledBinary}")
    Set_Source_Files_Properties(${source}
                                PROPERTIES 
                                  COMPILE_FLAGS 
                                    "/Yu\"${precompiledHeader}\" /FI\"${precompiledHeader}\" /Fp\"${precompiledBinary}\""
                                  OBJECT_DEPENDS 
                                    "${precompiledBinary}")  
    # Add precompiled header to SourcesVar
    list(APPEND ${sourceFiles} ${precompiledSource})
  endif()
EndMacro()