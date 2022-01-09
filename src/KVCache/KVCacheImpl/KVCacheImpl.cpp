#include "KVCacheImpl.h"
#include "../MemoryCache/AbstractMemoryCache.h"
#include "spdlog/sinks/basic_file_sink.h"   // support for basic file logging
#include "spdlog/spdlog.h"

KVCache::Internal::KVCacheImpl::KVCacheImpl()
{
    const std::string loggerName = "KVCacheImpl";
    m_logger = spdlog::get(loggerName);
    if (!m_logger)
    {
        m_logger = spdlog::basic_logger_mt(loggerName, "logs/KVCacheImpl.log");
    }

    m_logger->info("KVCacheImpl Constructor Starting Up");
    m_logger->info("KVCacheImpl Constructor is using default KV Optional Parameters");
    Interface::KVOptionalParameters defaultOptionalParams{Interface::SizeConstraint::MAXSIZE_1_MB,
                                                          Interface::MemoryCacheType::UNORDERED_MAP,
                                                          Interface::StorageCacheType::NONE,
                                                          Interface::CacheEvictionStrategy::FIFO,
                                                          Interface::StoragePath::defaultStoragePath};
    setupKVCache(defaultOptionalParams);
    m_logger->info("KVCacheImpl Constructor Completed");
}
KVCache::Internal::KVCacheImpl::KVCacheImpl(const Interface::KVOptionalParameters& optionalParams)
{
    m_logger = spdlog::basic_logger_mt("KVCacheImpl", "logs/KVCacheImpl.log");
    m_logger->info("KVCacheImpl Constructor Starting Up");
    setupKVCache(optionalParams);
    m_logger->info("KVCacheImpl Constructor Completed");
}

void KVCache::Internal::KVCacheImpl::put(const std::string& key, const std::string& value)
{
    m_logger->info("KVCache put({})", key);
    m_memoryCache->put(key, value);
}

void KVCache::Internal::KVCacheImpl::remove(const std::string& key)
{
    m_logger->info("KVCache remove({})", key);
    m_memoryCache->remove(key);
}

std::pair<std::string, std::string> KVCache::Internal::KVCacheImpl::get(const std::string& key) const
{
    m_logger->info("KVCache get({})", key);
    return m_memoryCache->get(key);
}

void KVCache::Internal::KVCacheImpl::setupKVCache(const Interface::KVOptionalParameters& optionalParams)
{
    m_logger->info("setupKVCache - KVOptionalParameters:\n{}", optionalParams.toString());
    m_memoryCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(optionalParams.m_memMaxSizeMB,
                                                                                           optionalParams.m_memType,
                                                                                           optionalParams.m_evictionStrategy);
    m_storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(optionalParams.m_storagePath,
                                                                                               optionalParams.m_storageType);
}
