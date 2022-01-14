#pragma once
#include "AbstractCacheEvictionStrategyInsertionOrdering.h"


namespace KVCache
{
    namespace Internal
    {
        namespace CacheEvictionsStrategies
        {
            class CacheEvictionMRU: public AbstractCacheEvictionStrategyInsertionOrdering
            {
              public:
                CacheEvictionMRU(const std::string& loggerName = "CacheEvictionMRU");

                virtual ~CacheEvictionMRU() = default;
                CacheEvictionMRU(const CacheEvictionMRU&) = delete;
                CacheEvictionMRU& operator=(CacheEvictionMRU const&) = delete;

                /*! Reaction to a get from the cache
                 *
                 * If the element is not present, do nothing
                 * If the element is present, delete first the previous occurrence
                 * Then push the new (or updated) key to the front of the deque
                 *
                 */
                void get(const std::string& key) override;

                /*! Method for eviction from the cache
                 *
                 * This strategy is a MRU, so it will remove the first element in the deque since most recent element is placed at the beginning of the dequeue
                 */
                std::optional<std::string> evict() override;
            };
        }   // namespace CacheEvictionsStrategies
    }   // namespace Internal
}   // namespace KVCache