#pragma once

#include "KVEnums.h"
#include <cstddef>
#include <string>

namespace KVCache
{
    namespace Interface
    {
        /*!
         *  This struct contains the optional parameters for the Key Value Cache.
         */
        struct KVOptionalParameters
        {
            explicit KVOptionalParameters(const size_t memMaxSizeMB,
                                          const MemoryCacheType memType,
                                          const StorageCacheType storageType,
                                          const CacheEvictionStrategy evictionStrategy);

            std::string toString() const;

            size_t m_memMaxSizeMB;
            MemoryCacheType m_memType;
            StorageCacheType m_storageType;
            CacheEvictionStrategy m_evictionStrategy;
        };

    }   // namespace Interface

}   // namespace KVCache