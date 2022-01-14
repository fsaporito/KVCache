#pragma once
#include "AbstractCacheEvictionStrategyInsertionOrdering.h"


namespace KVCache
{
    namespace Internal
    {
        namespace CacheEvictionsStrategies
        {
            class CacheEvictionFIFO: public AbstractCacheEvictionStrategyInsertionOrdering
            {
              public:
                CacheEvictionFIFO(const std::string& loggerName = "CacheEvictionFIFO");

                virtual ~CacheEvictionFIFO() = default;
                CacheEvictionFIFO(const CacheEvictionFIFO&) = delete;
                CacheEvictionFIFO& operator=(CacheEvictionFIFO const&) = delete;

                /*! Method for eviction from the cache
                 *
                 * This strategy is a FIFO, so it will remove the last element in the deque since new elements are placed at the beginning of the dequeue
                 */
                std::optional<std::string> evict() override;
            };
        }   // namespace CacheEvictionsStrategies
    }   // namespace Internal
}   // namespace KVCache