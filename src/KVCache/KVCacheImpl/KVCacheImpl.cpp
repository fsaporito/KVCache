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
    auto removedData = m_memoryCache->put(key, value);
    if (!removedData.empty())
    {
        for (const auto& kvPair: removedData)
        {
            const auto& removedKey = kvPair.first;
            const auto& removedValue = kvPair.second;
            m_storageCache->put(removedKey, removedValue);
        }
    }
}

bool KVCache::Internal::KVCacheImpl::remove(const std::string& key)
{
    m_logger->info("KVCache remove({})", key);
    const bool wasPairRemoved = m_memoryCache->remove(key);
    if (wasPairRemoved)
    {
        return wasPairRemoved;
    }
    else
    {
        return m_storageCache->remove(key);
    }
}

std::optional<std::pair<std::string, std::string>> KVCache::Internal::KVCacheImpl::get(const std::string& key) const
{
    m_logger->info("KVCache get({})", key);
    auto kvPair = m_memoryCache->get(key);
    if (kvPair)
    {
        return kvPair;
    }
    else
    {
        return m_storageCache->get(key);
    }
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
