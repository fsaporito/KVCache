#pragma once
#include <cstddef>
#include <string>

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
        inline std::string MemoryCacheTypeToString(MemoryCacheType memCacheType)
        {
            switch(memCacheType)
            {
                using enum MemoryCacheType;
                case ORDERED_MAP:
                    return "Ordered Map";
                case UNORDERED_MAP:
                    return "Unordered Map";
                default:
                    return "Unknown";
            }
        }

        enum class StorageCacheType
        {
            NONE,
            LINEAR_FILE
        };
        inline std::string StorageCacheTypeToString(StorageCacheType storageCacheType)
        {
            switch(storageCacheType)
            {
                using enum StorageCacheType;
                case NONE:
                    return "None";
                case LINEAR_FILE:
                    return "Linear File";
                default:
                    return "Unknown";
            }
        }

        enum class CacheEvictionStrategy
        {
            FIFO,
            LRU,
            FLU
        };
        inline std::string CacheEvictionStrategyToString(CacheEvictionStrategy cacheEvictionStrategy)
        {
            switch(cacheEvictionStrategy)
            {
                using enum CacheEvictionStrategy;
                case FIFO:
                    return "None";
                case LRU:
                    return "LRU";
                case FLU:
                    return "FLU";
                default:
                    return "Unknown";
            }
        }

        namespace StoragePath
        {
            const std::string defaultDirectory = ".";
            const std::string defaultPathName = ".KVCache.txt";
            const std::string defaultStoragePath = defaultDirectory + "/" + defaultPathName;
        }

    }   // namespace Interface
}   // namespace KVCache