#include "CacheEvictionMRU.h"

using namespace KVCache::Internal::CacheEvictionsStrategies;

CacheEvictionMRU::CacheEvictionMRU(const std::string& loggerName)
    : AbstractCacheEvictionStrategyInsertionOrdering(loggerName){};

std::optional<std::string> CacheEvictionMRU::evict()
{
    if (m_deque.empty())
    {
        return {};
    }
    else
    {
        const std::string evictedElement = m_deque.front();
        m_deque.pop_front();
        return evictedElement;
    }
}

void CacheEvictionMRU::get(const std::string& key)
{

    // Find the key position in the deque
    auto elPosition = std::find(m_deque.begin(), m_deque.end(), key);

    // If the key is present, delete it and then add it to the front of the queue
    if (elPosition != m_deque.end())
    {
        m_deque.erase(elPosition);
        m_deque.push_front(key);
    }

    return;
}