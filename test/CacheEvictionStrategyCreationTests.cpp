#include "KVCache/CacheEvictionStrategies/AbstractCacheEvictionStrategy.h"
#include <catch2/catch.hpp>

// This Macro Generates Data for RuntimeTests
#define generateData()                                                                                             \
    auto evictionStrategy = GENERATE(KVCache::Interface::CacheEvictionStrategyType::FIFO,                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LIFO,                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LRU,                           \
                                     KVCache::Interface::CacheEvictionStrategyType::MRU);                          \
    INFO("      - evictionStrategy=" << KVCache::Interface::CacheEvictionStrategyToStrMap().at(evictionStrategy)); \
    REQUIRE_NOTHROW(KVCache::Internal::CacheEvictionsStrategies::AbstractCacheEvictionStrategy::createCacheEvictionStrategy(evictionStrategy));


TEST_CASE("Create CacheEvictionStrategy", "[creation],[CacheEvictionStrategy]")
{
    // Generate Multiple Datasets and Inizialize Memcache
    generateData();
}

TEST_CASE("Create CacheEvictionStrategy with Unknown CacheEvictionStrategy Type", "[creation],[CacheEvictionStrategy]")
{
    auto evictionStrategy = static_cast<KVCache::Interface::CacheEvictionStrategyType>(100);
    REQUIRE_THROWS(KVCache::Internal::CacheEvictionsStrategies::AbstractCacheEvictionStrategy::createCacheEvictionStrategy(evictionStrategy));
}