#include "KVCacheImpl.h"

KVCache::Internal::KVCacheImpl::KVCacheImpl()
    : KVCacheAbstract()
{
    Interface::KVOptionalParameters defaultOptionalParams{Interface::SizeConstraint::MAXSIZE_1_MB,
                                                          Interface::MemoryCacheType::UNORDERED_MAP,
                                                          Interface::StorageCacheType::NONE,
                                                          Interface::CacheEvictionStrategy::FIFO};
    setupKVCache(defaultOptionalParams);
}

KVCache::Internal::KVCacheImpl::KVCacheImpl(const Interface::KVOptionalParameters& optionalParams)
    : KVCacheAbstract()
{
    setupKVCache(optionalParams);
}

void KVCache::Internal::KVCacheImpl::put(const std::string& key, const std::string& value)
{
    key;
    value;
}

void KVCache::Internal::KVCacheImpl::remove(const std::string& key)
{
    key;
}

std::pair<std::string, std::string> KVCache::Internal::KVCacheImpl::get(const std::string& key) const
{
    const std::string value {"test value"};
    return std::make_pair(key, value);    
}

void KVCache::Internal::KVCacheImpl::setupKVCache(const Interface::KVOptionalParameters& optionalParams)
{}
