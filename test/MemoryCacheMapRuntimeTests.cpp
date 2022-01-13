#include "KVCache/MemoryCache/MemoryCacheMap.h"
#include "testHelpers.h"
#include <catch2/catch.hpp>

// This Macro Generates Data for RuntimeTests
#define generateData()                                                                                                             \
    auto numSamples = static_cast<size_t>(GENERATE(1, 4, 10, 100, 1000));                                                          \
    auto memMaxSizeMB = GENERATE(KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,                                                 \
                                 KVCache::Interface::SizeConstraint::MAXSIZE_10_MB);                                               \
    auto memType = GENERATE(KVCache::Interface::MemoryCacheType::UNORDERED_MAP, KVCache::Interface::MemoryCacheType::ORDERED_MAP); \
    auto evictionStrategy = GENERATE(KVCache::Interface::CacheEvictionStrategyType::FIFO,                                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LIFO,                                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LRU,                                           \
                                     KVCache::Interface::CacheEvictionStrategyType::MRU);                                          \
    INFO("      -numSamples=" << numSamples << " "                                                                                 \
                              << "memMaxSizeMB=" << memMaxSizeMB << " "                                                            \
                              << "memType=" << KVCache::Interface::MemoryCacheToStrMap().at(memType)                               \
                              << "evictionStrategy=" << KVCache::Interface::CacheEvictionStrategyToStrMap().at(evictionStrategy)); \
    auto cache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,                              \
                                                                                        memType,                                   \
                                                                                        evictionStrategy);                         \
    auto [keys, values] = TestHelper::generateKVPairs(numSamples);


TEST_CASE("Get returns empty  on Empty MemoryCacheMap", "[runtime],[Get],[MemoryCacheMap]")
{
    // Initialize cache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    auto cache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                        memType,
                                                                                        evictionStrategy);

    // Get Faillure
    const std::string key = "TestKey";
    REQUIRE_NOTHROW(cache->get(key));
    auto optionalPair = cache->get(key);
    REQUIRE(!optionalPair.has_value());
}

TEST_CASE("Remove doesn't fail when key isn't present", "[runtime],[Remove],[MemoryCacheMap]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    auto cache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                        memType,
                                                                                        evictionStrategy);

    // Remove KV Pair
    const std::string key = "TestKey";
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = cache->remove(key));
    REQUIRE(!removeFlag);
    REQUIRE(cache->size() == 0);
}

TEST_CASE("Put + Remove + Get Faillure KV Pair into MemoryCacheMap", "[runtime],[Put],[Get],[Remove],[MemoryCacheMap]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;
    auto cache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                        memType,
                                                                                        evictionStrategy);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(cache->put(key, value));
    REQUIRE(cache->size() == 1);

    // Remove KV Pair
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = cache->remove(key));
    REQUIRE(removeFlag);
    REQUIRE(cache->size() == 0);

    // Get Faillure
    REQUIRE_NOTHROW(cache->get(key));
    auto optionalPair = cache->get(key);
    REQUIRE(!optionalPair.has_value());
}


TEST_CASE("Put N + Get N KV Pair MemoryCacheMap", "[runtime],[Put],[Get],[MemoryCacheMap]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->put(keys.at(i), values.at(i)));
        REQUIRE(cache->size() == i + 1);
    }

    // Get KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->get(keys.at(i)));
        REQUIRE(cache->size() == numSamples);
        auto optionalPair = cache->get(keys.at(i));
        REQUIRE(optionalPair.has_value());
        const auto& keyRead = optionalPair.value().first;
        const auto& valueRead = optionalPair.value().second;
        REQUIRE(keyRead == keys.at(i));
        REQUIRE(valueRead == values.at(i));
    }
}

TEST_CASE("Put N + Get N + Update N KV Pair MemoryCacheMap", "[runtime],[Put],[Get],[MemoryCacheMap]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->put(keys.at(i), values.at(i)));
        REQUIRE(cache->size() == i + 1);
    }

    // Get KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->get(keys.at(i)));
        REQUIRE(cache->size() == numSamples);
        auto optionalPair = cache->get(keys.at(i));
        REQUIRE(optionalPair.has_value());
        const auto& keyRead = optionalPair.value().first;
        const auto& valueRead = optionalPair.value().second;
        REQUIRE(keyRead == keys.at(i));
        REQUIRE(valueRead == values.at(i));
    }

    // Update KV Pairs with repeated value
    for (size_t i = 1; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->put(keys.at(i), values.at(i - 1) + values.at(i - 1)));
        REQUIRE(cache->size() == numSamples);
    }

    // Get KV Pairs
    for (size_t i = 1; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->get(keys.at(i)));
        REQUIRE(cache->size() == numSamples);
        auto optionalPair = cache->get(keys.at(i));
        REQUIRE(optionalPair.has_value());
        const auto& keyRead = optionalPair.value().first;
        const auto& valueRead = optionalPair.value().second;
        REQUIRE(keyRead == keys.at(i));
        REQUIRE(valueRead == values.at(i - 1) + values.at(i - 1));
    }
}

TEST_CASE("Put N + Remove N MemoryCacheMap", "[runtime],[Put],[Remove],[MemoryCacheMap]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->put(keys.at(i), values.at(i)));
        REQUIRE(cache->size() == i + 1);
    }

    // Remove KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        bool removeFlag = false;
        REQUIRE_NOTHROW(removeFlag = cache->remove(keys.at(i)));
        REQUIRE(removeFlag);
        REQUIRE(cache->size() == numSamples - i - 1);
    }
}

TEST_CASE("Put N + Get Odds + Remove Even MemoryCacheMap", "[runtime],[Put],[Get],[Remove],[MemoryCacheMap]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cache->put(keys.at(i), values.at(i)));
        REQUIRE(cache->size() == i + 1);
    }

    // Get Odd KV Pairs and Remove Even KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        const auto currentSize = cache->size();
        if (i % 2 == 0)   // Even => Remove
        {
            bool removeFlag = false;
            REQUIRE_NOTHROW(removeFlag = cache->remove(keys.at(i)));
            REQUIRE(removeFlag);
            REQUIRE(cache->size() == currentSize - 1);
        }
        else   // Odd => Get
        {
            REQUIRE_NOTHROW(cache->get(keys.at(i)));
            REQUIRE(cache->size() == currentSize);
            auto optionalPair = cache->get(keys.at(i));
            REQUIRE(optionalPair.has_value());
            const auto& keyRead = optionalPair.value().first;
            const auto& valueRead = optionalPair.value().second;
            REQUIRE(keyRead == keys.at(i));
            REQUIRE(valueRead == values.at(i));
        }
    }
}