#include "MemoryCacheMap.h"

#include <spdlog/spdlog.h>
#include <stdexcept>

using namespace KVCache::Internal::MemoryCache;

template<typename T>
    requires isMap<T>
        MemoryCacheMap<T>::MemoryCacheMap(const size_t maxByteSize,
                                          const Interface::CacheEvictionStrategy cacheEvictionStrategy)
        : AbstractMemoryCache(maxByteSize, cacheEvictionStrategy, "logs/MemoryCacheMap.log")
    {
        m_logger->info("MemoryCacheMap Object Created");
    };


    template<typename T>
        requires isMap<T>
            std::vector<std::pair<std::string, std::string>> MemoryCacheMap<T>::put(const std::string& key, const std::string& value)
        {
            std::vector<std::pair<std::string, std::string>> removedElements{};

            std::lock_guard<std::mutex> guard(m_mapMutex);

            if (m_map.contains(key))
            {
                m_logger->info("MemoryCacheMap::put() key={} is present, value will be updated", key);
                const size_t oldValueByteSize = m_map.at(key).size();
                m_currentByteSize -= oldValueByteSize;
                m_map[key] = value;
                const size_t newValueByteSize = value.size();
                m_currentByteSize += newValueByteSize;
            }
            else
            {
                m_logger->info("MemoryCacheMap::put() key={} isn't present, value will be added", key);
                const auto kvPair = std::make_pair(key, value);
                m_map.insert(kvPair);
                const size_t newKeyByteSize = key.size();
                const size_t newValueByteSize = value.size();
                m_currentByteSize += newKeyByteSize + newValueByteSize;
            }

            m_logger->info("MemoryCacheMap::put() completed for key={}, new bytesize=", key, m_currentByteSize);

            return removedElements;
        }

    template<typename T>
        requires isMap<T>
    void MemoryCacheMap<T>::remove(const std::string& key)
    {
        std::lock_guard<std::mutex> guard(m_mapMutex);
        if (m_map.contains(key))
        {
            m_logger->info("MemoryCacheMap::remove() remove key={}", key);
            const size_t oldValueByteSize = m_map.at(key).size();
            m_map.erase(key);
            m_currentByteSize -= oldValueByteSize;
            m_logger->info("MemoryCacheMap::remove() removed key={}, new bytesize=", key, m_currentByteSize);
        }
    }

    template<typename T>
        requires isMap<T>
            std::pair<std::string, std::string> MemoryCacheMap<T>::get(const std::string& key)
    const
    {
        std::lock_guard<std::mutex> guard(m_mapMutex);
        if (m_map.contains(key))
        {
            m_logger->info("MemoryCacheMap::get() key={}", key);
            return std::make_pair(key, m_map.at(key));
        }
        else
        {
            m_logger->info("MemoryCacheMap::get() failed for key={}", key);
            throw std::runtime_error("Didn't find element with key: " + key);
        }
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

    template class KVCache::Internal::MemoryCache::MemoryCacheMap<std::map<std::string, std::string>>;
    template class KVCache::Internal::MemoryCache::MemoryCacheMap<std::unordered_map<std::string, std::string>>;
