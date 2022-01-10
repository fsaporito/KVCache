#include "KVCache/MemoryCache/MemoryCacheMap.h"
#include "testHelpers.h"
#include <catch2/catch.hpp>


TEST_CASE("Put 1 KV Pair into MemoryCacheMap Single Thread", "[runtime],[Put],[Singlepair],[MemoryCacheMap][SingleThread]")
{

    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(memCache->put(key, value));
    REQUIRE(memCache->size() == 1);
}

TEST_CASE("Put 2 KV Pairs into MemoryCacheMap Single Thread", "[runtime],[Put],[Multipair],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);
    // Put KV Pair
    const std::string key1 = "TestKey1";
    const std::string value1 = "TestValue1";
    REQUIRE_NOTHROW(memCache->put(key1, value1));
    REQUIRE(memCache->size() == 1);

    // Put KV2 Pair
    const std::string key2 = "TestKey2";
    const std::string value2 = "TestValue2";
    REQUIRE_NOTHROW(memCache->put(key2, value2));
    REQUIRE(memCache->size() == 2);
}

TEST_CASE("Put + Get KV Pair into MemoryCacheMap Single Thread", "[runtime],[Put],[Get],[Singlepair],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(memCache->put(key, value));
    REQUIRE(memCache->size() == 1);

    // Get KV Pair
    REQUIRE_NOTHROW(memCache->get(key));
    auto optionalPair = memCache->get(key);
    REQUIRE(optionalPair.has_value());
    const auto& keyRead = optionalPair.value().first;
    const auto& valueRead = optionalPair.value().second;
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);
}

TEST_CASE("Put + Get + Update KV Pair into MemoryCacheMap Single Thread", "[runtime],[Put],[Get],[Singlepair],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);
    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(memCache->put(key, value));
    REQUIRE(memCache->size() == 1);

    // Get KV Pair
    REQUIRE_NOTHROW(memCache->get(key));
    auto optionalPair = memCache->get(key);
    REQUIRE(optionalPair.has_value());
    const auto& keyRead = optionalPair.value().first;
    const auto& valueRead = optionalPair.value().second;
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);

    // Update KV Pair
    const std::string newValue = "NewTestValue";
    REQUIRE_NOTHROW(memCache->put(key, newValue));
    REQUIRE(memCache->size() == 1);

    // Get updated KV Pair
    REQUIRE_NOTHROW(memCache->get(key));
    auto optionalPair2 = memCache->get(key);
    REQUIRE(optionalPair2.has_value());
    const auto& keyRead2 = optionalPair2.value().first;
    const auto& valueRead2 = optionalPair2.value().second;
    REQUIRE(keyRead2 == key);
    REQUIRE(valueRead2 == newValue);
}

TEST_CASE("Get Faillure on Empty MemoryCacheMap Single Thread", "[runtime],[Get],[Singlepair],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Get Faillure
    const std::string key = "TestKey";
    REQUIRE_NOTHROW(memCache->get(key));
    auto optionalPair = memCache->get(key);
    REQUIRE(!optionalPair.has_value());
}

TEST_CASE("Put + Remove KV Pair into MemoryCacheMap Single Thread", "[runtime],[Put],[Remove],[Singlepair],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(memCache->put(key, value));
    REQUIRE(memCache->size() == 1);

    // Remove KV Pair
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = memCache->remove(key));
    REQUIRE(removeFlag);
    REQUIRE(memCache->size() == 0);

    // Get KV Pair
    REQUIRE_NOTHROW(memCache->get(key));
    auto optionalPair = memCache->get(key);
    REQUIRE(!optionalPair.has_value());
}


TEST_CASE("Remove doesn't fail when key isn't present in Single Thread", "[runtime],[Remove],[Singlepair],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Remove KV Pair
    const std::string key = "TestKey";
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = memCache->remove(key));
    REQUIRE(!removeFlag);
    REQUIRE(memCache->size() == 0);
}

TEST_CASE("Put + Remove + Get Faillure KV Pair into MemoryCacheMap Single Thread", "[runtime],[Put],[Get],[Remove],[Singlepair],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(memCache->put(key, value));
    REQUIRE(memCache->size() == 1);

    // Remove KV Pair
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = memCache->remove(key));
    REQUIRE(removeFlag);
    REQUIRE(memCache->size() == 0);

    // Get Faillure
    REQUIRE_NOTHROW(memCache->get(key));
    auto optionalPair = memCache->get(key);
    REQUIRE(!optionalPair.has_value());
}


TEST_CASE("Put N + Get N KV Pair MemoryCacheMap Single Thread", "[runtime],[Put],[Get],[Multipair],[MemoryCacheMap],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize MemCache
        auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
        auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
        auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
        auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                               memType,
                                                                                               evictionStrategy);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(memCache->put(keys.at(i), values.at(i)));
            REQUIRE(memCache->size() == i + 1);
        }

        // Get KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(memCache->get(keys.at(i)));
            REQUIRE(memCache->size() == numSamples);
            auto optionalPair = memCache->get(keys.at(i));
            REQUIRE(optionalPair.has_value());
            const auto& keyRead = optionalPair.value().first;
            const auto& valueRead = optionalPair.value().second;
            REQUIRE(keyRead == keys.at(i));
            REQUIRE(valueRead == values.at(i));
        }
    }
}

TEST_CASE("Put N + Get N + Update N/2 KV Pair MemoryCacheMap Single Thread", "[runtime],[Put],[Get],[Multipair],[MemoryCacheMap],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize MemCache
        auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
        auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
        auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
        auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                               memType,
                                                                                               evictionStrategy);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(memCache->put(keys.at(i), values.at(i)));
            REQUIRE(memCache->size() == i + 1);
        }

        // Get KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(memCache->get(keys.at(i)));
            REQUIRE(memCache->size() == numSamples);
            auto optionalPair = memCache->get(keys.at(i));
            REQUIRE(optionalPair.has_value());
            const auto& keyRead = optionalPair.value().first;
            const auto& valueRead = optionalPair.value().second;
            REQUIRE(keyRead == keys.at(i));
            REQUIRE(valueRead == values.at(i));
        }

        // Update Odd KV Pairs with previous value
        for (size_t i = 0; i < numSamples; i++)
        {
            if (i % 2 != 0)   // Odd => Update
            {
                REQUIRE_NOTHROW(memCache->put(keys.at(i), values.at(i - 1)));
                REQUIRE(memCache->size() == numSamples);
            }
        }

        // Get KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(memCache->get(keys.at(i)));
            REQUIRE(memCache->size() == numSamples);
            auto optionalPair = memCache->get(keys.at(i));
            REQUIRE(optionalPair.has_value());
            const auto& keyRead = optionalPair.value().first;
            const auto& valueRead = optionalPair.value().second;
            REQUIRE(keyRead == keys.at(i));
            if (i % 2 != 0)   // Odd => was Updated with previous value
            {
                REQUIRE(valueRead == values.at(i - 1));
            }
            else
            {
                REQUIRE(valueRead == values.at(i));
            }
        }
    }
}

TEST_CASE("Put N + Remove N MemoryCacheMap Single Thread", "[runtime],[Put],[Remove],[Multipairs],[MemoryCacheMap],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize MemCache
        auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
        auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
        auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
        auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                               memType,
                                                                                               evictionStrategy);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(memCache->put(keys.at(i), values.at(i)));
            REQUIRE(memCache->size() == i + 1);
        }

        // Remove KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            bool removeFlag = false;
            REQUIRE_NOTHROW(removeFlag = memCache->remove(keys.at(i)));
            REQUIRE(removeFlag);
            REQUIRE(memCache->size() == numSamples - i - 1);
        }
    }
}

TEST_CASE("Put N + Get Odds + Remove Even MemoryCacheMap Single Thread", "[runtime],[Put],[Get],[Remove],[Multipair],[MemoryCacheMap],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize MemCache
        auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_10_MB;
        auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
        auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
        auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                               memType,
                                                                                               evictionStrategy);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(memCache->put(keys.at(i), values.at(i)));
            REQUIRE(memCache->size() == i + 1);
        }

        // Get Odd KV Pairs and Remove Even KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            const auto currentSize = memCache->size();
            if (i % 2 == 0)   // Even => Remove
            {
                bool removeFlag = false;
                REQUIRE_NOTHROW(removeFlag = memCache->remove(keys.at(i)));
                REQUIRE(removeFlag);
                REQUIRE(memCache->size() == currentSize - 1);
            }
            else   // Odd => Get
            {
                REQUIRE_NOTHROW(memCache->get(keys.at(i)));
                REQUIRE(memCache->size() == currentSize);
                auto optionalPair = memCache->get(keys.at(i));
                REQUIRE(optionalPair.has_value());
                const auto& keyRead = optionalPair.value().first;
                const auto& valueRead = optionalPair.value().second;
                REQUIRE(keyRead == keys.at(i));
                REQUIRE(valueRead == values.at(i));
            }
        }
    }
}