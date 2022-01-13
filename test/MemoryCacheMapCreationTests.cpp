#include "KVCache/MemoryCache/MemoryCacheMap.h"
#include <catch2/catch.hpp>


TEST_CASE("Create MemoryCacheMap of Type Ordered", "[creation],[MemoryCacheMap][OrderedMap]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::ORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap of Type Unordered", "[creation],[MemoryCacheMap][UnorderedMap]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap of Size 10Mb", "[creation],[MemoryCacheMap][UnorderedMap]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap with Eviction Strategy FIFO", "[creation],[MemoryCacheMap][UnorderedMap][FIFO]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap with Eviction Strategy LIFO", "[creation],[MemoryCacheMap][UnorderedMap][LIFO]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::LIFO;
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap with Eviction Strategy LRU", "[creation],[MemoryCacheMap][UnorderedMap][LRU]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::LRU;
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy));
}

TEST_CASE("Create MemoryCacheMap with Eviction Strategy MRU", "[creation],[MemoryCacheMap][UnorderedMap][FLU]")
{
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::MRU;
    REQUIRE_NOTHROW(KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
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