#include "AbstractMemoryCache.h"
#include "MemoryCacheMap.h"
#include "spdlog/sinks/basic_file_sink.h"   // support for basic file logging
#include "UnknownMemCacheTypeException.h"
#include <memory>
#include <spdlog/logger.h>

using namespace KVCache::Internal::MemoryCache;

AbstractMemoryCache::AbstractMemoryCache(const size_t maxByteSize,
                                         const KVCache::Interface::CacheEvictionStrategy cacheEvictionStrategy,
                                         const std::string& loggerOutputPath)
    : m_maxByteSize(maxByteSize),
      m_cacheEvictionStrategy(cacheEvictionStrategy)
{
    m_logger = spdlog::basic_logger_mt("MemoryCache", loggerOutputPath);
};

std::unique_ptr<AbstractMemoryCache> AbstractMemoryCache::createMemoryCache(size_t maxByteSize,
                                                                            KVCache::Interface::MemoryCacheType memType,
                                                                            KVCache::Interface::CacheEvictionStrategy cacheEvictionStrategy)
{
    auto m_logger = spdlog::basic_logger_mt("createMemoryCache", "logs/createMemoryCache.log");
    m_logger->info("create memory cache of Type {}", KVCache::Interface::MemoryCacheTypeToString(memType));
    switch (memType)
    {
        using enum KVCache::Interface::MemoryCacheType;
        case ORDERED_MAP:
            return std::make_unique<MemoryCacheMap<std::map<std::string, std::string>>>(maxByteSize, cacheEvictionStrategy);
        case UNORDERED_MAP:
            return std::make_unique<MemoryCacheMap<std::unordered_map<std::string, std::string>>>(maxByteSize, cacheEvictionStrategy);
        default:
            throw UnknownMemCacheTypeException("Unknown MemoryCache Type");
    }
}

size_t AbstractMemoryCache::getMaxByteSize() const
{
    return m_maxByteSize;
}

KVCache::Interface::CacheEvictionStrategy AbstractMemoryCache::getCacheEvictionStrategy() const
{
    return m_cacheEvictionStrategy;
}