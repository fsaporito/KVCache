set(KVCacheLibName "KVCache")
set(KVCacheLibName "KVCache" PARENT_SCOPE)

add_library(${KVCacheLibName} STATIC 
  KVCacheInterface/KVCacheAbstract.cpp 
  KVCacheInterface/KVCacheAbstract.h
  KVCacheInterface/KVCacheException.h
  KVCacheInterface/KVEnums.h
  KVCacheInterface/KVOptionalParameters.cpp
  KVCacheInterface/KVOptionalParameters.h
  KVCacheImpl/KVCacheImpl.cpp 
  KVCacheImpl/KVCacheImpl.h
  KVCacheImpl/KVExceptionsHelper.h
  MemoryCache/AbstractMemoryCache.cpp
  MemoryCache/AbstractMemoryCache.h
  MemoryCache/MemoryCacheMap.cpp
  MemoryCache/MemoryCacheMap.h
  StorageCache/AbstractStorageCache.cpp  
  StorageCache/AbstractStorageCache.h
  StorageCache/StorageCacheLinearFile.cpp  
  StorageCache/StorageCacheLinearFile.h
  StorageCache/StorageCacheNone.cpp  
  StorageCache/StorageCacheNone.h  
  StorageCache/UnknownStorageCacheTypeException.h
  CacheEvictionStrategies/AbstractCacheEvictionStrategy.cpp
  CacheEvictionStrategies/AbstractCacheEvictionStrategy.h
  CacheEvictionStrategies/AbstractCacheEvictionStrategyInsertionOrdering.cpp
  CacheEvictionStrategies/AbstractCacheEvictionStrategyInsertionOrdering.h
  CacheEvictionStrategies/CacheEvictionFIFO.cpp
  CacheEvictionStrategies/CacheEvictionFIFO.h
  CacheEvictionStrategies/CacheEvictionLIFO.cpp
  CacheEvictionStrategies/CacheEvictionLIFO.h
  CacheEvictionStrategies/CacheEvictionLRU.cpp
  CacheEvictionStrategies/CacheEvictionLRU.h
  CacheEvictionStrategies/CacheEvictionMRU.cpp
  CacheEvictionStrategies/CacheEvictionMRU.h
  CacheEvictionStrategies/UnknownCacheEvictionStrategyException.h
)
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
