#include "CacheEvictionFIFO.h"

using namespace KVCache::Internal::CacheEvictionsStrategies;

CacheEvictionFIFO::CacheEvictionFIFO(const std::string& loggerName)
    : AbstractCacheEvictionStrategyInsertionOrdering(loggerName){};

std::optional<std::string> CacheEvictionFIFO::evict()
{
    if (m_deque.empty())
    {
        return {};
    }
    else
    {
        const std::string evictedElement = m_deque.back();
        m_deque.pop_back();
        return evictedElement;
    }
}