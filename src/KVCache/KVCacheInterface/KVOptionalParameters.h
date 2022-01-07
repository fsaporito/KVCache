#pragma once

#include "KVEnums.h"
#include <cstddef>

namespace KVCache
{
    namespace Interface
    {
        struct KVOptionalParameters
        {
            explicit KVOptionalParameters(const size_t memMaxSizeMB,
                                          const MemoryCacheType memType,
                                          const StorageCacheType storageType,
                                          const CacheEvictionStrategy evictionStrategy);

            size_t m_memMaxSizeMB;
            MemoryCacheType m_memType;
            StorageCacheType m_storageType;
            CacheEvictionStrategy m_evictionStrategy;
        };

    }   // namespace Interface

}   // namespace KVCache