Add_Executable(TestProject main.cpp)


Include_Directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)
#Target_Include_Directories(TestProject ${CMAKE_CURRENT_SOURCE_DIR}/..)
Target_Link_Libraries(TestProject Reflection)