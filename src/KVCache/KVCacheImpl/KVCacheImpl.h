#pragma once
#include "../KVCacheInterface/KVCacheAbstract.h"
#include "../MemoryCache/AbstractMemoryCache.h"
#include "../StorageCache/AbstractStorageCache.h"
#include <memory>
#include <spdlog/logger.h>


namespace KVCache
{
    namespace Internal
    {

        namespace MemoryCache
        {
            class AbstractMemoryCache;
        }

        /*!
         *  This class gives a concrete implementation of the KVCache Virtual Class.
         */
        class KVCacheImpl: public Interface::KVCacheAbstract
        {
          public:
            explicit KVCacheImpl();
            explicit KVCacheImpl(const Interface::KVOptionalParameters& optionalParams);
            virtual ~KVCacheImpl() = default;
            KVCacheImpl(const KVCacheImpl&) = delete;
            KVCacheImpl& operator=(KVCacheImpl const&) = delete;

            void put(const std::string& key, const std::string& value) override;
            void remove(const std::string& key) override;
            std::pair<std::string, std::string> get(const std::string& key) const override;

          protected:
            void setupKVCache(const Interface::KVOptionalParameters& optionalParams);
            std::unique_ptr<MemoryCache::AbstractMemoryCache> m_memoryCache;
            std::unique_ptr<StorageCache::AbstractStorageCache> m_storageCache;
            std::shared_ptr<spdlog::logger> m_logger;
        };
    }   // namespace Internal
}   // namespace KVCache