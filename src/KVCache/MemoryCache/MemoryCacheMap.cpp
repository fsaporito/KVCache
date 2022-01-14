#include "MemoryCacheMap.h"

#include <spdlog/spdlog.h>
#include <stdexcept>

using namespace KVCache::Internal::MemoryCache;

template<typename T>
    requires isMap<T>
        MemoryCacheMap<T>::MemoryCacheMap(const size_t maxByteSize,
                                          const Interface::CacheEvictionStrategyType cacheEvictionStrategy)
        : AbstractMemoryCache(maxByteSize, cacheEvictionStrategy, "MemoryCacheMap")
    {
        m_evictionStrategy = CacheEvictionsStrategies::AbstractCacheEvictionStrategy::createCacheEvictionStrategy(cacheEvictionStrategy);
        m_logger->info("MemoryCacheMap Object Created");
    };


    template<typename T>
        requires isMap<T>
            std::vector<std::pair<std::string, std::string>> MemoryCacheMap<T>::put(const std::string& key, const std::string& value)
        {
            std::vector<std::pair<std::string, std::string>> removedElements{};

            std::lock_guard<std::mutex> guard(m_mapMutex);

            // Check if element can fit in the cache
            size_t keyByteSize = key.size();
            const size_t newValueByteSize = value.size();
            if (newValueByteSize + keyByteSize >= m_maxByteSize)   // Element can't fit, return it
            {
                m_logger->warn("MemoryCacheMap::put() Received element for key={} is to big for cache, won't be added", key);
                removedElements.push_back(std::make_pair(key, value));
                return removedElements;
            }
            else   // Element can fit
            {
                if (m_map.contains(key))
                {
                    m_logger->info("MemoryCacheMap::put() key={} is present, value will be updated", key);

                    const auto oldValue = m_map.at(key);
                    const size_t oldValueByteSize = oldValue.size();
                    m_currentByteSize -= oldValueByteSize;

                    m_map[key] = value;
                    m_currentByteSize += newValueByteSize;
                }
                else
                {
                    m_logger->info("MemoryCacheMap::put() key={} isn't present, value will be added", key);
                    const auto kvPair = std::make_pair(key, value);
                    m_map.insert(kvPair);
                    m_currentByteSize += keyByteSize + newValueByteSize;
                }

                // Evict Cache Elements Until Size is OK
                while (m_currentByteSize >= m_maxByteSize)
                {
                    const auto evictedKeyOptional = m_evictionStrategy->evict();
                    if (!evictedKeyOptional.has_value())
                    {
                        throw std::runtime_error("Cache Evicted tried to evict an element but was empty");
                    }
                    const auto evictedKey = evictedKeyOptional.value();
                    const auto evictedValue = m_map.at(evictedKey);
                    const auto evictedKeyByteSize = evictedKey.size();
                    const auto evictedValueByteSize = evictedValue.size();
                    m_currentByteSize -= evictedKeyByteSize + evictedValueByteSize;
                    removedElements.push_back(std::make_pair(evictedKey, evictedValue));
                    m_map.erase(evictedKey);
                    m_logger->info("MemoryCacheMap::put() evicted key={}, new bytesize=", evictedKey, m_currentByteSize);
                }

                // Update Eviction Data After Get Operation
                m_evictionStrategy->put(key);

                m_logger->info("MemoryCacheMap::put() completed for key={}, new bytesize=", key, m_currentByteSize);

                return removedElements;
            }
        }

    template<typename T>
        requires isMap<T>
    bool MemoryCacheMap<T>::remove(const std::string& key)
    {
        std::lock_guard<std::mutex> guard(m_mapMutex);

        // Element isn't present, return
        if (!m_map.contains(key))
        {
            return false;
        }

        m_logger->info("MemoryCacheMap::remove() remove key={}", key);

        // Remove Element and Adjust Size
        const size_t oldValueByteSize = m_map.at(key).size();
        m_map.erase(key);
        m_currentByteSize -= oldValueByteSize;

        // Update Eviction Data After Remove Operation
        m_evictionStrategy->remove(key);

        m_logger->info("MemoryCacheMap::remove() removed key={}, new bytesize=", key, m_currentByteSize);

        return true;
    }

    template<typename T>
        requires isMap<T>
            std::optional<std::pair<std::string, std::string>> MemoryCacheMap<T>::get(const std::string& key)
    const
    {
        std::lock_guard<std::mutex> guard(m_mapMutex);

        // Element isn't present, return empty optional
        if (!m_map.contains(key))
        {
            m_logger->info("MemoryCacheMap::get() failed for key={}", key);
            return {};
        }

        m_logger->info("MemoryCacheMap::get() key={}", key);

        // Update Eviction Data After Get Operation
        m_evictionStrategy->get(key);

        return std::make_pair(key, m_map.at(key));
    }

    template<typename T>
        requires isMap<T>
            size_t MemoryCacheMap<T>::getByteSize()
    const
    {
        std::lock_guard<std::mutex> guard(m_mapMutex);
        m_logger->info("MemoryCacheMap::getByteSize() = {}", m_currentByteSize);
        return m_currentByteSize;
    }

    template<typename T>
        requires isMap<T>
            size_t MemoryCacheMap<T>::size()
    const
    {
        std::lock_guard<std::mutex> guard(m_mapMutex);
        m_logger->info("MemoryCacheMap::getByteSize() = {}", m_map.size());
        return m_map.size();
    }

    template<typename T>
        requires isMap<T>
            std::vector<std::string> MemoryCacheMap<T>::getKeys()
    const
    {
        std::vector<std::string> keys;
        keys.reserve(m_map.size());
        for (const auto& kv: m_map)
        {
            keys.push_back(kv.first);
        }
        return keys;
    }


    template class KVCache::Internal::MemoryCache::MemoryCacheMap<std::map<std::string, std::string>>;
    template class KVCache::Internal::MemoryCache::MemoryCacheMap<std::unordered_map<std::string, std::string>>;
