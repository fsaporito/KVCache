#include "KVCacheImpl.h"
#include "../MemoryCache/AbstractMemoryCache.h"
#include <spdlog/spdlog.h>

KVCache::Internal::KVCacheImpl::KVCacheImpl()
    : KVCacheAbstract()
{
    spdlog::trace("KVCacheImpl Constructor Starting Up");
    spdlog::trace("KVCacheImpl Constructor is using default KV Optional Parameters");
    Interface::KVOptionalParameters defaultOptionalParams{Interface::SizeConstraint::MAXSIZE_1_MB,
                                                          Interface::MemoryCacheType::UNORDERED_MAP,
                                                          Interface::StorageCacheType::NONE,
                                                          Interface::CacheEvictionStrategy::FIFO};
    setupKVCache(defaultOptionalParams);
    spdlog::trace("KVCacheImpl Constructor Completed");
}
KVCache::Internal::KVCacheImpl::KVCacheImpl(const Interface::KVOptionalParameters& optionalParams)
    : KVCacheAbstract()
{
    spdlog::trace("KVCacheImpl Constructor Starting Up");
    setupKVCache(optionalParams);
    spdlog::trace("KVCacheImpl Constructor Completed");
}

void KVCache::Internal::KVCacheImpl::put(const std::string& key, const std::string& value)
{
    spdlog::trace("KVCache put({})", key);
    m_memoryCache->put(key, value);
}

void KVCache::Internal::KVCacheImpl::remove(const std::string& key)
{
    spdlog::trace("KVCache remove({})", key);
    m_memoryCache->remove(key);
}

std::pair<std::string, std::string> KVCache::Internal::KVCacheImpl::get(const std::string& key) const
{
    spdlog::trace("KVCache get({})", key);
    return m_memoryCache->get(key);
}

void KVCache::Internal::KVCacheImpl::setupKVCache(const Interface::KVOptionalParameters& optionalParams)
{
    spdlog::trace("setupKVCache - KVOptionalParameters:\n{}", optionalParams.toString());
    m_memoryCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(optionalParams.m_memMaxSizeMB,
                                                                                           optionalParams.m_memType,
                                                                                           optionalParams.m_evictionStrategy);
}
