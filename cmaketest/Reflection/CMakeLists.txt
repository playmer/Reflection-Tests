Set(Reflection_Source)

Get_Filename_Component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
Add_Subdirectory(Meta)
Add_Subdirectory(StandardLibrary)
Include_Directories(${ParentDirectory})

Add_Library(Reflection ${Reflection_Source})