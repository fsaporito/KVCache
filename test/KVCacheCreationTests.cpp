#include "KVCache/KVCacheInterface/KVCacheAbstract.h"
#include <catch2/catch.hpp>

// This Macro Generates Data for RuntimeTests
#define generateData()                                                                                                             \
    auto memMaxSizeMB = GENERATE(KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,                                                 \
                                 KVCache::Interface::SizeConstraint::MAXSIZE_10_MB);                                               \
    auto memType = GENERATE(KVCache::Interface::MemoryCacheType::UNORDERED_MAP, KVCache::Interface::MemoryCacheType::ORDERED_MAP); \
    auto storageType = GENERATE(KVCache::Interface::StorageCacheType::NONE, KVCache::Interface::StorageCacheType::LINEAR_FILE);    \
    auto evictionStrategy = GENERATE(KVCache::Interface::CacheEvictionStrategyType::FIFO,                                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LIFO,                                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LRU,                                           \
                                     KVCache::Interface::CacheEvictionStrategyType::MRU);                                          \
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;                                                        \
    INFO("      -memMaxSizeMB=" << memMaxSizeMB << " "                                                                             \
                                << "memType=" << KVCache::Interface::MemoryCacheToStrMap().at(memType)                             \
                                << "storageType=" << KVCache::Interface::StorageCacheToStrMap().at(storageType)                    \
                                << "evictionStrategy=" << KVCache::Interface::CacheEvictionStrategyToStrMap().at(evictionStrategy) \
                                << "storagePath=" << storagePath);                                                                 \
    KVCache::Interface::KVOptionalParameters optionalParams{                                                                       \
        memMaxSizeMB,                                                                                                              \
        memType,                                                                                                                   \
        storageType,                                                                                                               \
        evictionStrategy,                                                                                                          \
        storagePath};                                                                                                              \
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));


TEST_CASE("Create KVCache with default parameters", "[creation],[KVCache]")
{
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache());
}

TEST_CASE("Create KVCache", "[creation],[KVCache]")
{
    // Generate Multiple Datasets and Inizialize KVCache
    generateData();
}