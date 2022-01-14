#include "AbstractCacheEvictionStrategyInsertionOrdering.h"

using namespace KVCache::Internal::CacheEvictionsStrategies;

AbstractCacheEvictionStrategyInsertionOrdering::AbstractCacheEvictionStrategyInsertionOrdering(const std::string& loggerName)
    : AbstractCacheEvictionStrategy(loggerName){};

void AbstractCacheEvictionStrategyInsertionOrdering::put(const std::string& key)
{
    // Find the key position in the deque
    auto elPosition = std::find(m_deque.begin(), m_deque.end(), key);

    // If the key is present, delete it
    if (elPosition != m_deque.end())
    {
        m_deque.erase(elPosition);
    }

    // Add the key to the front of the deque
    m_deque.push_front(key);

    return;
}

void AbstractCacheEvictionStrategyInsertionOrdering::remove(const std::string& key)
{
    // Find the key position in the deque
    auto elPosition = std::find(m_deque.begin(), m_deque.end(), key);

    // If the key is present, delete it
    if (elPosition != m_deque.end())
    {
        m_deque.erase(elPosition);
    }

    return;
}

void AbstractCacheEvictionStrategyInsertionOrdering::get(const std::string& key)
{
    // Do nothing
    return;
}

size_t AbstractCacheEvictionStrategyInsertionOrdering::size() const
{
    return m_deque.size();
}