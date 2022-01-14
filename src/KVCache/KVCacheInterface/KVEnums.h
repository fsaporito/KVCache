#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>

namespace KVCache
{
    namespace Interface
    {

        // Size Constraints
        namespace SizeConstraint
        {

            constexpr size_t MAXSIZE_1_MB = 1024 * 1024;
            constexpr size_t MAXSIZE_10_MB = 10 * MAXSIZE_1_MB;

        }   // namespace SizeConstraint

        // Memory Cache Type
        enum class MemoryCacheType
        {
            ORDERED_MAP,
            UNORDERED_MAP
        };
        const std::unordered_map<std::string, MemoryCacheType> StrToMemoryCacheTypeMap = {
            {  "ORDERED_MAP",   MemoryCacheType::ORDERED_MAP},
            {"UNORDERED_MAP", MemoryCacheType::UNORDERED_MAP}
        };
        inline std::unordered_map<MemoryCacheType, std::string> MemoryCacheToStrMap()
        {
            std::unordered_map<MemoryCacheType, std::string> map;
            for (const auto& [str, enumType]: StrToMemoryCacheTypeMap)
            {
                map.insert({enumType, str});
            }
            return map;
        };

        // Storage Cache Type
        enum class StorageCacheType
        {
            NONE,
            LINEAR_FILE
        };
        const std::unordered_map<std::string, StorageCacheType> StrToStorageCacheTypeMap = {
            {       "NONE",        StorageCacheType::NONE},
            {"LINEAR_FILE", StorageCacheType::LINEAR_FILE}
        };
        inline std::unordered_map<StorageCacheType, std::string> StorageCacheToStrMap()
        {
            std::unordered_map<StorageCacheType, std::string> map;
            for (const auto& [str, enumType]: StrToStorageCacheTypeMap)
            {
                map.insert({enumType, str});
            }
            return map;
        };

        // Cache Eviction Strategy
        enum class CacheEvictionStrategyType
        {
            FIFO,
            LIFO,
            LRU,
            MRU
        };
        const std::unordered_map<std::string, CacheEvictionStrategyType> StrToCacheEvictionStrategyTypeMap = {
            {"FIFO", CacheEvictionStrategyType::FIFO},
            {"LIFO", CacheEvictionStrategyType::LIFO},
            { "LRU",  CacheEvictionStrategyType::LRU},
            { "MRU",  CacheEvictionStrategyType::MRU}
        };
        inline std::unordered_map<CacheEvictionStrategyType, std::string> CacheEvictionStrategyToStrMap()
        {
            std::unordered_map<CacheEvictionStrategyType, std::string> map;
            for (const auto& [str, enumType]: StrToCacheEvictionStrategyTypeMap)
            {
                map.insert({enumType, str});
            }
            return map;
        };

        // Storage Path
        namespace StoragePath
        {
            const std::string defaultDirectory = ".";
            const std::string defaultPathName = ".KVCache.txt";
            const std::string defaultStoragePath = defaultDirectory + "/" + defaultPathName;
        }   // namespace StoragePath

    }   // namespace Interface
}   // namespace KVCache