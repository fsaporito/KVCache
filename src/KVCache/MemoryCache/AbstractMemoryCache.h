#pragma once
#include "../KVCacheInterface/KVEnums.h"
#include <cstddef>
#include <memory>
#include <spdlog/logger.h>
#include <string>
#include <vector>

namespace KVCache
{
    namespace Internal
    {
        namespace MemoryCache
        {
            class AbstractMemoryCache
            {
              public:
                static std::unique_ptr<AbstractMemoryCache> createMemoryCache(size_t maxByteSize,
                                                                              KVCache::Interface::MemoryCacheType memType,
                                                                              KVCache::Interface::CacheEvictionStrategy cacheEvictionStrategy);

                virtual ~AbstractMemoryCache() = default;
                AbstractMemoryCache(const AbstractMemoryCache&) = delete;
                AbstractMemoryCache& operator=(AbstractMemoryCache const&) = delete;

                virtual std::vector<std::pair<std::string, std::string>> put(const std::string& key, const std::string& value) = 0;
                virtual void remove(const std::string& key) = 0;
                virtual std::pair<std::string, std::string> get(const std::string& key) const = 0;
                virtual size_t getByteSize() const = 0;
                virtual size_t size() const = 0;

                size_t getMaxByteSize() const;
                Interface::CacheEvictionStrategy getCacheEvictionStrategy() const;

              protected:
                AbstractMemoryCache(const size_t maxByteSize,
                                    const Interface::CacheEvictionStrategy cacheEvictionStrategy,
                                    const std::string& loggerOutputPath = "logs/AbstractMemoryCache.log");
                size_t m_maxByteSize;
                Interface::CacheEvictionStrategy m_cacheEvictionStrategy;
                std::shared_ptr<spdlog::logger> m_logger;
            };
        }   // namespace MemoryCache
    }   // namespace Internal
}   // namespace KVCache