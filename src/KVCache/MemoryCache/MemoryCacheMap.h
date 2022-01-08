#pragma once
#include "AbstractMemoryCache.h"
#include <concepts>
#include <map>
#include <mutex>
#include <spdlog/spdlog.h>
#include <stdexcept>
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
                               const Interface::CacheEvictionStrategy cacheEvictionStrategy)
                    : AbstractMemoryCache(maxByteSize, cacheEvictionStrategy)
                {
                    spdlog::trace("MemoryCacheMap Object Created");
                };

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
                std::vector<std::pair<std::string, std::string>> put(const std::string& key, const std::string& value) override
                {
                    std::vector<std::pair<std::string, std::string>> removedElements{};

                    std::lock_guard<std::mutex> guard(m_mapMutex);

                    if (m_map.contains(key))
                    {
                        spdlog::trace("MemoryCacheMap::put() key={} is present, value will be updated", key);
                        const size_t oldValueByteSize = m_map.at(key).size();
                        m_currentByteSize -= oldValueByteSize;
                        m_map[key] = value;
                        const size_t newValueByteSize = value.size();
                        m_currentByteSize += newValueByteSize;
                    }
                    else
                    {
                        spdlog::trace("MemoryCacheMap::put() key={} isn't present, value will be added", key);
                        const auto kvPair = std::make_pair(key, value);
                        m_map.insert(kvPair);
                        const size_t newKeyByteSize = key.size();
                        const size_t newValueByteSize = value.size();
                        m_currentByteSize += newKeyByteSize + newValueByteSize;
                    }

                    spdlog::trace("MemoryCacheMap::put() completed for key={}, new bytesize=", key, m_currentByteSize);

                    return removedElements;
                }

                /*!
                 * Removes KV pair from the cache.
                 * If the pair isn't present in the cache, this method wont' do anything.
                 * This method will automatically update the bytesize of the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                void remove(const std::string& key) override
                {
                    std::lock_guard<std::mutex> guard(m_mapMutex);
                    if (m_map.contains(key))
                    {
                        spdlog::trace("MemoryCacheMap::remove() remove key={}", key);
                        const size_t oldValueByteSize = m_map.at(key).size();
                        m_map.erase(key);
                        m_currentByteSize -= oldValueByteSize;
                        spdlog::trace("MemoryCacheMap::remove() removed key={}, new bytesize=", key, m_currentByteSize);
                    }
                }

                /*!
                 * Get a KV pair from the cache.
                 * If the pair isn't present in the cache, this method will throw an exception.
                 * This method won't change the underlying data.
                 * This method is thread-safe regarding access to the underline data.
                 */
                std::pair<std::string, std::string> get(const std::string& key) const override
                {
                    std::lock_guard<std::mutex> guard(m_mapMutex);
                    if (m_map.contains(key))
                    {
                        spdlog::trace("MemoryCacheMap::get() key={}", key);
                        return std::make_pair(key, m_map.at(key));
                    }
                    else
                    {
                        spdlog::trace("MemoryCacheMap::get() failed for key={}", key);
                        throw std::runtime_error("Didn't find element with key: " + key);
                    }
                }

                /*!
                 * Returns the bytesize of the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                size_t getByteSize() const override
                {
                    std::lock_guard<std::mutex> guard(m_mapMutex);
                    spdlog::trace("MemoryCacheMap::getByteSize() = {}", m_currentByteSize);
                    return m_currentByteSize;
                }

                /*!
                 * Returns the number of KVPairs in the KVCache.
                 * This method is thread-safe regarding access to the underline data.
                 */
                size_t size() const override
                {
                    std::lock_guard<std::mutex> guard(m_mapMutex);
                    spdlog::trace("MemoryCacheMap::getByteSize() = {}", m_map.size());
                    return m_map.size();
                }

              protected:
                mutable std::mutex m_mapMutex{};
                size_t m_currentByteSize{0};
                T m_map;
            };
        }   // namespace MemoryCache
    }   // namespace Internal
}   // namespace KVCache
