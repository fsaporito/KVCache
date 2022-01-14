#include "KVCache/KVCacheInterface/KVCacheAbstract.h"
#include "testHelpers.h"
#include <catch2/catch.hpp>

// This Macro Generates Data for RuntimeTests
#define generateData()                                                                                                             \
    auto numSamples = static_cast<size_t>(GENERATE(1, 4, 10, 20));                                                                 \
    auto valuesSize = static_cast<size_t>(GENERATE(10, 100, 1024, 4096, 1024 * 1024 / 10));                                        \
    auto memMaxSizeMB = GENERATE(KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,                                                 \
                                 KVCache::Interface::SizeConstraint::MAXSIZE_10_MB);                                               \
    auto memType = GENERATE(KVCache::Interface::MemoryCacheType::UNORDERED_MAP, KVCache::Interface::MemoryCacheType::ORDERED_MAP); \
    auto storageType = GENERATE(KVCache::Interface::StorageCacheType::LINEAR_FILE);                                                \
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
    auto kvCache = KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams);                                             \
    auto [keys, values] = TestHelper::generateKVPairs(numSamples, "Key", TestHelper::generateLongValueOfGivenSize(valuesSize));

TEST_CASE("Get returns empty on Empty kvCache", "[runtime],[Get],[kvCache]")
{
    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Get Faillure
    const std::string key = "TestKey";
    REQUIRE_NOTHROW(kvCache->get(key));
    auto optionalPair = kvCache->get(key);
    REQUIRE(!optionalPair.has_value());
}

TEST_CASE("Remove doesn't fail when key isn't present in kvCache", "[runtime],[Remove],[kvCache]")
{
    /// Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Remove KV Pair
    const std::string key = "TestKey";
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = kvCache->remove(key));
    REQUIRE(!removeFlag);
    REQUIRE(kvCache->size() == 0);
}

TEST_CASE("Put + Remove + Get Faillure KV Pair into kvCache", "[runtime],[Put],[Get],[Remove],[kvCache]")
{
    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(kvCache->put(key, value));
    REQUIRE(kvCache->size() == 1);

    // Remove KV Pair
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = kvCache->remove(key));
    REQUIRE(removeFlag);
    REQUIRE(kvCache->size() == 0);

    // Get Faillure
    REQUIRE_NOTHROW(kvCache->get(key));
    auto optionalPair = kvCache->get(key);
    REQUIRE(!optionalPair.has_value());
}


TEST_CASE("Put N + Get N KV Pair kvCache", "[runtime],[Put],[Get],[kvCache]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->put(keys.at(i), values.at(i)));
        REQUIRE(kvCache->size() == i + 1);
    }

    // Get KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->get(keys.at(i)));
        REQUIRE(kvCache->size() == numSamples);
        auto optionalPair = kvCache->get(keys.at(i));
        REQUIRE(optionalPair.has_value());
        const auto& keyRead = optionalPair.value().first;
        const auto& valueRead = optionalPair.value().second;
        REQUIRE(keyRead == keys.at(i));
        REQUIRE(valueRead == values.at(i));
    }
}

TEST_CASE("Put N + Get N + Update N KV Pair kvCache", "[runtime],[Put],[Get],[kvCache]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->put(keys.at(i), values.at(i)));
        REQUIRE(kvCache->size() == i + 1);
    }

    // Get KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->get(keys.at(i)));
        REQUIRE(kvCache->size() == numSamples);
        auto optionalPair = kvCache->get(keys.at(i));
        REQUIRE(optionalPair.has_value());
        const auto& keyRead = optionalPair.value().first;
        const auto& valueRead = optionalPair.value().second;
        REQUIRE(keyRead == keys.at(i));
        REQUIRE(valueRead == values.at(i));
    }

    // Update KV Pairs with repeated value
    for (size_t i = 1; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->put(keys.at(i), values.at(i - 1) + values.at(i - 1)));
        REQUIRE(kvCache->size() == numSamples);
    }

    // Get KV Pairs
    for (size_t i = 1; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->get(keys.at(i)));
        REQUIRE(kvCache->size() == numSamples);
        auto optionalPair = kvCache->get(keys.at(i));
        REQUIRE(optionalPair.has_value());
        const auto& keyRead = optionalPair.value().first;
        const auto& valueRead = optionalPair.value().second;
        REQUIRE(keyRead == keys.at(i));
        REQUIRE(valueRead == values.at(i - 1) + values.at(i - 1));
    }
}

TEST_CASE("Put N + Remove N kvCache", "[runtime],[Put],[Remove],[kvCache]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->put(keys.at(i), values.at(i)));
        REQUIRE(kvCache->size() == i + 1);
    }

    // Remove KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        bool removeFlag = false;
        REQUIRE_NOTHROW(removeFlag = kvCache->remove(keys.at(i)));
        REQUIRE(removeFlag);
        REQUIRE(kvCache->size() == numSamples - i - 1);
    }
}

TEST_CASE("Put N + Get Odds + Remove Even kvCache", "[runtime],[Put],[Get],[Remove],[kvCache]")
{

    // Generate Multiple Datasets and Inizialize Memcache
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(kvCache->put(keys.at(i), values.at(i)));
        REQUIRE(kvCache->size() == i + 1);
    }

    // Get Odd KV Pairs and Remove Even KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        const auto currentSize = kvCache->size();
        if (i % 2 == 0)   // Even => Remove
        {
            bool removeFlag = false;
            REQUIRE_NOTHROW(removeFlag = kvCache->remove(keys.at(i)));
            REQUIRE(removeFlag);
            REQUIRE(kvCache->size() == currentSize - 1);
        }
        else   // Odd => Get
        {
            REQUIRE_NOTHROW(kvCache->get(keys.at(i)));
            REQUIRE(kvCache->size() == currentSize);
            auto optionalPair = kvCache->get(keys.at(i));
            REQUIRE(optionalPair.has_value());
            const auto& keyRead = optionalPair.value().first;
            const auto& valueRead = optionalPair.value().second;
            REQUIRE(keyRead == keys.at(i));
            REQUIRE(valueRead == values.at(i));
        }
    }
}
