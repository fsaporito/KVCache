set(factLibName "fact")
set(factLibName "fact" PARENT_SCOPE)

add_library(${factLibName} STATIC factorial.cpp factorial.h)
if(WIN32 OR MSVC OR MSYS OR MINGW) # Windows: lib extension										
	set_target_properties(${factLibName} PROPERTIES SUFFIX ".lib")
elseif(UNIX AND NOT(APPLE)) # Linux: so extension
	set_target_properties(${factLibName} PROPERTIES SUFFIX ".so")
endif()
message(STATUS " - Target ${factLibName} created successfully") 

target_link_libraries(
  ${factLibName}
  PUBLIC project_options
          project_warnings)