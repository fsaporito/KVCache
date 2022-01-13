#include "KVCacheImpl.h"
#include "../MemoryCache/AbstractMemoryCache.h"
#include "KVExceptionsHelper.h"
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
    const std::string loggerName = "KVCacheImpl";
    m_logger = spdlog::get(loggerName);
    if (!m_logger)
    {
        m_logger = spdlog::basic_logger_mt(loggerName, "logs/KVCacheImpl.log");
    }

    m_logger->info("KVCacheImpl Constructor Starting Up");
    setupKVCache(optionalParams);
    m_logger->info("KVCacheImpl Constructor Completed");
}

void KVCache::Internal::KVCacheImpl::put(const std::string& key, const std::string& value)
{
    m_logger->info("KVCache put({})", key);
    try
    {
        // Put data into memory cache
        auto removedData = m_memoryCache->put(key, value);

        // Move removed data from memory cache to storage cache
        if (!removedData.empty())
        {
            for (const auto& kvPair: removedData)
            {
                const auto& removedKey = kvPair.first;
                const auto& removedValue = kvPair.second;
                m_storageCache->put(removedKey, removedValue);
            }
        }

        // Eventually remove the key from the storage cache if it exists
        m_storageCache->remove(key);
    }
    catch (...)
    {
        Exceptions::kvCacheExceptionHandler(m_logger, __FILE__, __LINE__);
    }
}

bool KVCache::Internal::KVCacheImpl::remove(const std::string& key)
{
    m_logger->info("KVCache remove({})", key);
    bool wasPairRemoved = false;
    try
    {
        wasPairRemoved = m_memoryCache->remove(key);
        if (!wasPairRemoved)   // Check the storage for removal
        {
            wasPairRemoved = m_storageCache->remove(key);
        }
    }
    catch (...)
    {
        Exceptions::kvCacheExceptionHandler(m_logger, __FILE__, __LINE__);
    }
    return wasPairRemoved;
}

std::optional<std::pair<std::string, std::string>> KVCache::Internal::KVCacheImpl::get(const std::string& key) const
{
    m_logger->info("KVCache get({})", key);
    try
    {
        const auto kvPair = m_memoryCache->get(key);
        if (kvPair)
        {
            return kvPair;
        }
        else
        {
            return m_storageCache->get(key);
        }
    }
    catch (...)
    {
        Exceptions::kvCacheExceptionHandler(m_logger, __FILE__, __LINE__);
    }
    return {};
}

void KVCache::Internal::KVCacheImpl::setupKVCache(const Interface::KVOptionalParameters& optionalParams)
{
    try
    {
        m_logger->info("setupKVCache - KVOptionalParameters:\n{}", optionalParams.toString());
        m_memoryCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(optionalParams.m_memMaxSizeMB,
                                                                                               optionalParams.m_memType,
                                                                                               optionalParams.m_evictionStrategy);
        m_storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(optionalParams.m_storagePath,
                                                                                                   optionalParams.m_storageType);
    }
    catch (...)
    {
        Exceptions::kvCacheExceptionHandler(m_logger, __FILE__, __LINE__);
    }
}
