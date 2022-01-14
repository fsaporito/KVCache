#include "AbstractCacheEvictionStrategy.h"
#include "CacheEvictionFIFO.h"
#include "CacheEvictionLIFO.h"
#include "CacheEvictionLRU.h"
#include "CacheEvictionMRU.h"
#include "spdlog/sinks/basic_file_sink.h"   // support for basic file logging
#include "spdlog/spdlog.h"
#include "UnknownCacheEvictionStrategyException.h"
#include <memory>

using namespace KVCache::Internal::CacheEvictionsStrategies;

AbstractCacheEvictionStrategy::AbstractCacheEvictionStrategy(const std::string& loggerName)
{
    m_logger = spdlog::get(loggerName);
    if (!m_logger)
    {
        m_logger = spdlog::basic_logger_mt(loggerName, "logs/" + loggerName + ".log");
    }
};

std::unique_ptr<AbstractCacheEvictionStrategy> AbstractCacheEvictionStrategy::createCacheEvictionStrategy(KVCache::Interface::CacheEvictionStrategyType cacheEvictionStrategyType)
{
    const std::string loggerName = "createCacheEvictionStrategy";
    auto m_logger = spdlog::get(loggerName);
    if (!m_logger)
    {
        m_logger = spdlog::basic_logger_mt(loggerName, "logs/" + loggerName + ".log");
    }
    m_logger->info("create cache eviction strategy of Type {}", KVCache::Interface::CacheEvictionStrategyToStrMap().at(cacheEvictionStrategyType));
    switch (cacheEvictionStrategyType)
    {
        using enum KVCache::Interface::CacheEvictionStrategyType;
        case FIFO:
            return std::make_unique<CacheEvictionFIFO>();
        case LIFO:
            return std::make_unique<CacheEvictionLIFO>();
        case LRU:
            return std::make_unique<CacheEvictionLRU>();
        case MRU:
            return std::make_unique<CacheEvictionMRU>();
        default:
            throw UnknownCacheEvictionStrategyException("Unknown CacheEvictionStrategy Type");
    }
}