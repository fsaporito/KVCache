#pragma once
#include "AbstractStorageCache.h"

namespace KVCache
{
    namespace Internal
    {
        namespace StorageCache
        {
            /*!
             *  This class implements a Null KeyValue-Cache
             */
            class StorageCacheNone: public AbstractStorageCache
            {
              public:
                explicit StorageCacheNone(const std::string& storagePath);

                ~StorageCacheNone() = default;
                StorageCacheNone(const StorageCacheNone&) = delete;
                StorageCacheNone& operator=(StorageCacheNone const&) = delete;

                /*!
                 * Puts KV pair into the null cache.
                 */
                void put(const std::string& key, const std::string& value) override;

                /*!
                 * Do nothing since the cache is null. It will ALWAYS return false
                 */
                bool remove(const std::string& key) override;

                /*!
                 * Always returns empty optional since the KV Pair can never be found in the null cache
                 */
                std::optional<std::pair<std::string, std::string>> get(const std::string& key) const override;

                /*!
                 * Returns the bytesize of the KVCache, which is always 0 for the null cache.
                 */
                size_t getByteSize() const override;

                /*!
                 * Returns the number of KVPairs in the KVCache, which is always 0 for the null cache.
                 */
                size_t size() const override;

              protected:
                mutable std::mutex m_mapMutex{};
                const size_t m_currentByteSize{0};
                const size_t m_currentSize{0};
            };
        }   // namespace StorageCache
    }   // namespace Internal
}   // namespace KVCache
