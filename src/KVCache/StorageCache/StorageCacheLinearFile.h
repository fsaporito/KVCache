#pragma once
#include "AbstractStorageCache.h"
#include <fstream>
#include <mutex>
#include <unordered_map>

namespace KVCache
{
    namespace Internal
    {

        constexpr size_t NUMBER_OF_CHARACTERS_IN_NEW_LINE = 2;

        namespace StorageCache
        {
            /*!
             *  This class implements a thread-safe KeyValue-Cache based on a file that will be linearly searched
             * The file will be written in the following format:
             * Line N: Key
             * Line N+1: Value
             * Line N+2: Empty Line
             */
            class StorageCacheLinearFile: public AbstractStorageCache
            {
              public:
                explicit StorageCacheLinearFile(const std::string& storagePath);

                ~StorageCacheLinearFile() = default;
                StorageCacheLinearFile(const StorageCacheLinearFile&) = delete;
                StorageCacheLinearFile& operator=(StorageCacheLinearFile const&) = delete;

                /*!
                 * Puts KV pair into cache.
                 * If the key is already present, it will update the value with the new one.
                 * This method will automatically update the bytesize of the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                void put(const std::string& key, const std::string& value) override;

                /*!
                 * Removes KV pair from the cache.
                 * If the pair isn't present in the cache, this method wont' do anything.
                 * This method will automatically update the bytesize of the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                void remove(const std::string& key) override;

                /*!
                 * Get a KV pair from the cache.
                 * If the pair isn't present in the cache, this method will throw an exception.
                 * This method won't change the underlying data.
                 * This method is thread-safe regarding access to the underline data.
                 */
                std::pair<std::string, std::string> get(const std::string& key) const override;

                /*!
                 * Returns the bytesize of the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                size_t getByteSize() const override;

                /*!
                 * Returns the number of KVPairs in the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                size_t size() const override;

              protected:
                mutable std::mutex m_fileMutex{};
                size_t m_currentByteSize{0};
                size_t m_currentSize{0};
            };
        }   // namespace StorageCache
    }   // namespace Internal
}   // namespace KVCache
