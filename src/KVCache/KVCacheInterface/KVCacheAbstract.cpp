#include "KVCacheAbstract.h"
#include "../KVCacheImpl/KVCacheImpl.h"

std::unique_ptr<KVCache::Interface::KVCacheAbstract> KVCache::Interface::KVCacheAbstract::createKVCache()
{
    return std::make_unique<KVCache::Internal::KVCacheImpl>();
}

std::unique_ptr<KVCache::Interface::KVCacheAbstract> KVCache::Interface::KVCacheAbstract::createKVCache(const Interface::KVOptionalParameters& optionalParams)
{
    return std::make_unique<KVCache::Internal::KVCacheImpl>(optionalParams);
}