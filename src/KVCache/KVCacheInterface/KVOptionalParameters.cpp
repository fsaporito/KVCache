#include "KVOptionalParameters.h"

constexpr size_t NUMBER_OF_BYTES_PER_MEGABYTE = 1024 * 1024;

KVCache::Interface::KVOptionalParameters::KVOptionalParameters(const size_t memMaxSizeByte,
                                                               const MemoryCacheType memType,
                                                               const StorageCacheType storageType,
                                                               const CacheEvictionStrategyType evictionStrategy,
                                                               const std::string& storagePath)
    : m_memMaxSizeByte(memMaxSizeByte),
      m_memType(memType),
      m_storageType(storageType),
      m_evictionStrategy(evictionStrategy),
      m_storagePath(storagePath)
{
}

std::string KVCache::Interface::KVOptionalParameters::toString() const
{

    std::string paramSt;

    paramSt += "memMaxSize (MB): " + std::to_string(static_cast<double>(m_memMaxSizeByte) / static_cast<double>(NUMBER_OF_BYTES_PER_MEGABYTE)) + "\n";
    paramSt += "memType: " + MemoryCacheToStrMap().at(m_memType) + "\n";
    paramSt += "storageType: " + StorageCacheToStrMap().at(m_storageType) + "\n";
    paramSt += "evictionStrategy: " + CacheEvictionStrategyToStrMap().at(m_evictionStrategy) + "\n";
    paramSt += "storagePath: " + m_storagePath + "\n";

    return paramSt;
}