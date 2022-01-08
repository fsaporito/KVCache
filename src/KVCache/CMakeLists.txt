set(KVCacheLibName "KVCache")
set(KVCacheLibName "KVCache" PARENT_SCOPE)

add_library(${KVCacheLibName} STATIC 
  KVCacheInterface/KVCacheAbstract.cpp 
  KVCacheInterface/KVCacheAbstract.h
  KVCacheInterface/KVEnums.h
  KVCacheInterface/KVOptionalParameters.cpp
  KVCacheInterface/KVOptionalParameters.h
  KVCacheImpl/KVCacheImpl.cpp 
  KVCacheImpl/KVCacheImpl.h
  MemoryCache/AbstractMemoryCache.cpp
  MemoryCache/AbstractMemoryCache.h
  MemoryCache/MemoryCacheMap.h)
if(WIN32 OR MSVC OR MSYS OR MINGW) # Windows: lib extension										
	set_target_properties(${KVCacheLibName} PROPERTIES SUFFIX ".lib")
elseif(UNIX AND NOT(APPLE)) # Linux: so extension
	set_target_properties(${KVCacheLibName} PROPERTIES SUFFIX ".so")
endif()
message(STATUS " - Target ${KVCacheLibName} created successfully")

find_package(spdlog)

target_link_libraries(
  ${KVCacheLibName}
  PUBLIC project_options
          project_warnings
          spdlog::spdlog)