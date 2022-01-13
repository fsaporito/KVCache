#pragma once
#include "AbstractMemoryCache.h"
#include <concepts>
#include <map>
#include <mutex>
#include <unordered_map>

namespace KVCache
{
    namespace Internal
    {
        namespace MemoryCache
        {
            template<typename T>
            concept isMap = std::same_as<T, std::map<std::string, std::string>> || std::same_as<T, std::unordered_map<std::string, std::string>>;

            template<typename T>
                requires isMap<T>
            /*!
             *  This class implements a thread-safe KeyValue-Cache using a map (ordered or unordered)
             */
            class MemoryCacheMap: public AbstractMemoryCache
            {
              public:
                MemoryCacheMap(const size_t maxByteSize,
                               const Interface::CacheEvictionStrategyType cacheEvictionStrategy);

                ~MemoryCacheMap() = default;
                MemoryCacheMap(const MemoryCacheMap&) = delete;
                MemoryCacheMap& operator=(MemoryCacheMap const&) = delete;

                /*!
                 * Puts KV pair into cache.
                 * If the key is already present, it will update the value with the new one.
                 * This method will automatically update the bytesize of the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 * If the KV cache is full, will return a vector containing the evicted pairs.
                 * Eviction Strategy is given at object creation.
                 */
                std::vector<std::pair<std::string, std::string>> put(const std::string& key, const std::string& value) override;

                /*!
                 * Removes KV pair from the cache.
                 * If the pair is present in the cache, it will be removed and the method will return true.
                 * If the pair isn't present in the cache, this method won't do anything and return false.
                 * This method will automatically update the bytesize of the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                bool remove(const std::string& key) override;

                /*!
                 * Get a KV pair from the cache.
                 * If the pair isn't present in the cache, this method return an empty optional.
                 * This method won't change the underlying data.
                 * This method is thread-safe regarding access to the underline data.
                 */
                std::optional<std::pair<std::string, std::string>> get(const std::string& key) const override;

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
                mutable std::mutex m_mapMutex{};
                size_t m_currentByteSize{0};
                T m_map;
            };
        }   // namespace MemoryCache
    }   // namespace Internal
}   // namespace KVCache
