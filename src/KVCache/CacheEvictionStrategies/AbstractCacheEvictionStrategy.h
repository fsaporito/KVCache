#pragma once
#include "../KVCacheInterface/KVEnums.h"
#include <memory>
#include <optional>
#include <spdlog/logger.h>
#include <string>


namespace KVCache
{
    namespace Internal
    {
        namespace CacheEvictionsStrategies
        {
            class AbstractCacheEvictionStrategy
            {
              public:
                static std::unique_ptr<AbstractCacheEvictionStrategy> createCacheEvictionStrategy(KVCache::Interface::CacheEvictionStrategyType cacheEvictionStrategyType);

                virtual ~AbstractCacheEvictionStrategy() = default;
                AbstractCacheEvictionStrategy(const AbstractCacheEvictionStrategy&) = delete;
                AbstractCacheEvictionStrategy& operator=(AbstractCacheEvictionStrategy const&) = delete;

                virtual void put(const std::string& key) = 0;
                virtual void remove(const std::string& key) = 0;
                virtual void get(const std::string& key) = 0;
                virtual std::optional<std::string> evict() = 0;

                virtual size_t size() const = 0;

              protected:
                AbstractCacheEvictionStrategy(const std::string& loggerName = "AbstractCacheEvictionStrategy");
                std::shared_ptr<spdlog::logger> m_logger;
            };
        }   // namespace CacheEvictionsStrategies
    }   // namespace Internal
}   // namespace KVCache