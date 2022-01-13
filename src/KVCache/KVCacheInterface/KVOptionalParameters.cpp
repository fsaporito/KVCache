#include "KVOptionalParameters.h"


KVCache::Interface::KVOptionalParameters::KVOptionalParameters(const size_t memMaxSizeMB,
                                                               const MemoryCacheType memType,
                                                               const StorageCacheType storageType,
                                                               const CacheEvictionStrategyType evictionStrategy,
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
    paramSt += "memType: " + MemoryCacheToStrMap().at(m_memType) + "\n";
    paramSt += "storageType: " + StorageCacheToStrMap().at(m_storageType) + "\n";
    paramSt += "evictionStrategy: " + CacheEvictionStrategyToStrMap().at(m_evictionStrategy) + "\n";
    paramSt += "storagePath: " + m_storagePath + "\n";

    return paramSt;
}