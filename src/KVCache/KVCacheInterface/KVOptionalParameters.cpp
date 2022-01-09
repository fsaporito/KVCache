#include "KVOptionalParameters.h"


KVCache::Interface::KVOptionalParameters::KVOptionalParameters(const size_t memMaxSizeMB,
                                                               const MemoryCacheType memType,
                                                               const StorageCacheType storageType,
                                                               const CacheEvictionStrategy evictionStrategy,
                                                               const std::string& storagePath)
    : m_memMaxSizeMB(memMaxSizeMB),
      m_memType(memType),
      m_storageType(storageType),
      m_evictionStrategy(evictionStrategy),
      m_storagePath(storagePath)
{
}

std::string KVCache::Interface::KVOptionalParameters::toString() const
{
    std::string paramSt;

    paramSt += "memMaxSizeMB: " + std::to_string(m_memMaxSizeMB) + "\n";
    paramSt += "memType: " + KVCache::Interface::MemoryCacheTypeToString(m_memType) + "\n";
    paramSt += "storageType: " + KVCache::Interface::StorageCacheTypeToString(m_storageType) + "\n";
    paramSt += "evictionStrategy: " + KVCache::Interface::CacheEvictionStrategyToString(m_evictionStrategy) + "\n";
    paramSt += "evictionStrategy: " + m_storagePath + "\n";

    return paramSt;
}