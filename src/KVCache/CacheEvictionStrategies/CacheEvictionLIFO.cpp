#include "CacheEvictionLIFO.h"

using namespace KVCache::Internal::CacheEvictionsStrategies;

CacheEvictionLIFO::CacheEvictionLIFO(const std::string& loggerName)
    : AbstractCacheEvictionStrategyInsertionOrdering(loggerName){};

std::optional<std::string> CacheEvictionLIFO::evict()
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