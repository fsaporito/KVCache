#include "KVCache/MemoryCache/MemoryCacheMap.h"
#include <catch2/catch.hpp>

// This Macro Generates Data for RuntimeTests
#define generateData()                                                                                                                \
    auto memMaxSizeMB = GENERATE(KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,                                                    \
                                 KVCache::Interface::SizeConstraint::MAXSIZE_10_MB);                                                  \
    auto memType = GENERATE(KVCache::Interface::MemoryCacheType::UNORDERED_MAP, KVCache::Interface::MemoryCacheType::ORDERED_MAP);    \
    auto evictionStrategy = GENERATE(KVCache::Interface::CacheEvictionStrategyType::FIFO,                                             \
                                     KVCache::Interface::CacheEvictionStrategyType::LIFO,                                             \
                                     KVCache::Interface::CacheEvictionStrategyType::LRU,                                              \
                                     KVCache::Interface::CacheEvictionStrategyType::MRU);                                             \
    INFO("      - memMaxSizeMB=" << memMaxSizeMB << " "                                                                               \
                                 << "memType=" << KVCache::Interface::MemoryCacheToStrMap().at(memType)                               \
                                 << "evictionStrategy=" << KVCache::Interface::CacheEvictionStrategyToStrMap().at(evictionStrategy)); \
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,                              \
                                                                                           memType,                                   \
                                                                                           evictionStrategy));


TEST_CASE("Create MemoryCacheMap", "[creation],[MemoryCacheMap]")
{
    // Generate Multiple Datasets and Inizialize Memcache
    generateData();
}

TEST_CASE("Create MemoryCacheMap with Zero Max Size", "[creation],[MemoryCacheMap]")
{
    auto memMaxSizeMB = static_cast<size_t>(0);
    auto memType = KVCache::Interface::MemoryCacheType::ORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    REQUIRE_THROWS(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                          memType,
                                                                                          evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap with Unknown MemoryCache Type", "[creation],[MemoryCacheMap]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = static_cast<KVCache::Interface::MemoryCacheType>(100);
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    REQUIRE_THROWS(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                          memType,
                                                                                          evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap with Unknown CacheEvictionStrategy Type", "[creation],[MemoryCacheMap]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::ORDERED_MAP;
    auto evictionStrategy = static_cast<KVCache::Interface::CacheEvictionStrategyType>(100);
    REQUIRE_THROWS(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                          memType,
                                                                                          evictionStrategy));
}