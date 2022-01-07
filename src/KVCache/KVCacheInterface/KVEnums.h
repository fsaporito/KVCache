#pragma once
#include <cstddef>

namespace KVCache
{
    namespace Interface
    {

        namespace SizeConstraint
        {

            constexpr size_t MAXSIZE_1_MB = 1;
            constexpr size_t MAXSIZE_10_MB = 10;

        }   // namespace SizeConstraint

        enum class MemoryCacheType
        {
            ORDERED_MAP,
            UNORDERED_MAP
        };

        enum class StorageCacheType
        {
            NONE,
            LINEAR_FILE
        };

        enum class CacheEvictionStrategy
        {
            FIFO,
            LRU,
            FLU
        };

    }   // namespace Interface
}   // namespace KVCache