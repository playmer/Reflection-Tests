# Make source groups
#SourceGroupSetup(${CMAKE_CURRENT_SOURCE_DIR} " " FALSE)

#File( GLOB precompiledFile pch.c*)
#List( REMOVE_ITEM sourceFiles ${precompiledFile})

#SetPrecompiledHeader(pch.h ${precompiledFile} sourceFiles)
Set(Reflection_Source)

Get_Filename_Component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

Add_Subdirectory(Meta)
Add_Subdirectory(StandardLibrary)

MESSAGE(STATUS ${Reflection_Source})

Include_Directories(${ParentDirectory})
Add_Library( Reflection ${Reflection_Source})


#target_include_directories(Reflection ${CMAKE_CURRENT_SOURCE_DIR})


#If (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
#Target_Compile_Options(${engineSystem} PUBLIC "/MT$<$<CONFIG:Debug>:d>")
#EndIf()

# External Dependencies
#Target_Link_Libraries(${engineSystem} ${LIBCMT_LIBRARIES} ${StaticLibraries})

set_property( TARGET ${engineSystem} PROPERTY FOLDER "Reflection")