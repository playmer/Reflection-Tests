CMake_Minimum_Required(VERSION 3.6 FATAL_ERROR)

Project(YTE_Reflection_Test CXX C)

Set(Source_Root ${CMAKE_CURRENT_SOURCE_DIR})

Set_Property(GLOBAL PROPERTY USE_FOLDERS ON)
Set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Source_Root}/cmake/modules/")

Include(CMake/AddFile.cmake)
Include(CMake/SourceGroupSetup.cmake)

Include_Directories(${CMAKE_CURRENT_SOURCE_DIR})

Add_Subdirectory(Reflection)
Add_Subdirectory(Main)