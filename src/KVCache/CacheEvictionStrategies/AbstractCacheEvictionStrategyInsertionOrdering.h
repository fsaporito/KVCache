#pragma once
#include "AbstractCacheEvictionStrategy.h"
#include <deque>


namespace KVCache
{
    namespace Internal
    {
        namespace CacheEvictionsStrategies
        {
            class AbstractCacheEvictionStrategyInsertionOrdering: public AbstractCacheEvictionStrategy
            {
              public:
                virtual ~AbstractCacheEvictionStrategyInsertionOrdering() = default;
                AbstractCacheEvictionStrategyInsertionOrdering(const AbstractCacheEvictionStrategyInsertionOrdering&) = delete;
                AbstractCacheEvictionStrategyInsertionOrdering& operator=(AbstractCacheEvictionStrategyInsertionOrdering const&) = delete;

                /*! Reaction to a put into the cache
                 *
                 * If the element is present, delete first the previous occurrence
                 * Then push the new (or updated) key to the front of the deque
                 *
                 */
                void put(const std::string& key) override;

                /*! Reaction to a remove into the cache
                 *
                 * If the element is present, delete it from the deque
                 *
                 */
                void remove(const std::string& key) override;

                /*! Reaction to a get into the cache
                 *
                 * Do nothing
                 *
                 */
                virtual void get(const std::string& key) override;

                /*! Returns the current number of elements in the deque */
                size_t size() const override;

              protected:
                AbstractCacheEvictionStrategyInsertionOrdering(const std::string& loggerName = "AbstractCacheEvictionStrategy");
                std::deque<std::string> m_deque;
            };
        }   // namespace CacheEvictionsStrategies
    }   // namespace Internal
}   // namespace KVCache