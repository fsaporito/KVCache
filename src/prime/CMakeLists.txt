set(primeLibName "prime")
set(primeLibName "prime" PARENT_SCOPE)

add_library(${primeLibName} STATIC prime.cpp prime.h)
if(WIN32 OR MSVC OR MSYS OR MINGW) # Windows: lib extension										
	set_target_properties(${primeLibName} PROPERTIES SUFFIX ".lib")
elseif(UNIX AND NOT(APPLE)) # Linux: so extension
	set_target_properties(${primeLibName} PROPERTIES SUFFIX ".so")
endif()
message(STATUS " - Target ${primeLibName} created successfully") 


target_link_libraries(
  ${primeLibName}
  PUBLIC project_options
          project_warnings)
