#include "KVOptionalParameters.h"


KVCache::Interface::KVOptionalParameters::KVOptionalParameters(const size_t memMaxSizeMB,
                                                               const MemoryCacheType memType,
                                                               const StorageCacheType storageType,
                                                               const CacheEvictionStrategy evictionStrategy)
    : m_memMaxSizeMB(memMaxSizeMB),
      m_memType(memType),
      m_storageType(storageType),
      m_evictionStrategy(evictionStrategy)
{
}