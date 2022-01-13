#pragma once
#include "../KVCacheInterface/KVEnums.h"
#include <cstddef>
#include <memory>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <utility>

namespace KVCache
{
    namespace Internal
    {
        namespace StorageCache
        {
            class AbstractStorageCache
            {
              public:
                static std::unique_ptr<AbstractStorageCache> createStorageCache(const std::string& storagePath,
                                                                                KVCache::Interface::StorageCacheType storageType);

                virtual ~AbstractStorageCache() = default;
                AbstractStorageCache(const AbstractStorageCache&) = delete;
                AbstractStorageCache& operator=(AbstractStorageCache const&) = delete;

                virtual void put(const std::string& key, const std::string& value) = 0;
                virtual bool remove(const std::string& key) = 0;
                virtual std::optional<std::pair<std::string, std::string>> get(const std::string& key) const = 0;
                virtual size_t getByteSize() const = 0;
                virtual size_t size() const = 0;

                std::string getStoragePath() const;

              protected:
                AbstractStorageCache(const std::string& storagePath, const std::string& loggerName = "AbstractStorageCache");
                std::string m_storagePath;
                std::shared_ptr<spdlog::logger> m_logger;
            };
        }   // namespace StorageCache
    }   // namespace Internal
}   // namespace KVCache