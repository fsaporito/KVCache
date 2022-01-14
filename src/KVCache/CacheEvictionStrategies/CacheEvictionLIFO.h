#pragma once
#include "AbstractCacheEvictionStrategyInsertionOrdering.h"


namespace KVCache
{
    namespace Internal
    {
        namespace CacheEvictionsStrategies
        {
            class CacheEvictionLIFO: public AbstractCacheEvictionStrategyInsertionOrdering
            {
              public:
                CacheEvictionLIFO(const std::string& loggerName = "CacheEvictionLIFO");
                virtual ~CacheEvictionLIFO() = default;
                CacheEvictionLIFO(const CacheEvictionLIFO&) = delete;
                CacheEvictionLIFO& operator=(CacheEvictionLIFO const&) = delete;

                /*! Method for eviction from the cache
                 *
                 * This strategy is a LIFO, so it will remove the first element in the deque since new elements are placed at the beginning of the deque
                 */
                std::optional<std::string> evict() override;
            };
        }   // namespace CacheEvictionsStrategies
    }   // namespace Internal
}   // namespace KVCache