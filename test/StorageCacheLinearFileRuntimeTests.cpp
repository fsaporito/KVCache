#include "KVCache/StorageCache/StorageCacheLinearFile.h"
#include "testHelpers.h"
#include <catch2/catch.hpp>
#include <vector>


#define generateData()                                                                                                \
    auto numSamples = static_cast<size_t>(GENERATE(1, 4, 10, 100, 1000));                                             \
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;                                             \
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;                                           \
    INFO("      -storageType=" << KVCache::Interface::StorageCacheToStrMap().at(storageType)                          \
                               << "storagePath=" << storagePath);                                                     \
    auto cache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath, storageType); \
    auto [keys, values] = TestHelper::generateKVPairs(numSamples);


TEST_CASE("Get returns empty optional on Empty StorageCacheLinearFile", "[runtime],[Get],[StorageCacheLinearFile]")
{
    // Initialize cache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto cache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                           storageType);

    // Get Faillure
    const std::string key = "TestKey";
    REQUIRE_NOTHROW(cache->get(key));
    auto optionalPair = cache->get(key);
    REQUIRE(!optionalPair.has_value());
}

TEST_CASE("Remove doesn't fail when key isn't present in StorageCacheLinearFile", "[runtime],[Remove],[StorageCacheLinearFile]")
{
    // Initialize cache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto cache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                           storageType);

    // Remove KV Pair
    const std::string key = "TestKey";
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = cache->remove(key));
    REQUIRE(!removeFlag);
    REQUIRE(cache->size() == 0);
}

TEST_CASE("Put + Remove + Get Faillure KV Pair StorageCacheLinearFile", "[runtime],[Put],[Get],[Remove],[StorageCacheLinearFile]")
{
    // Initialize cache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto cache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                           storageType);

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


TEST_CASE("Put N + Get N KV Pair StorageCacheLinearFile", "[runtime],[Put],[Get],[StorageCacheLinearFile]")
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

TEST_CASE("Put N + Get N + Update N KV Pair StorageCacheLinearFile", "[runtime],[Put],[Get]")
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

    // Update Odd KV Pairs with previous value
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

TEST_CASE("Put N + Remove N StorageCacheLinearFile", "[runtime],[Put],[Remove],[StorageCacheLinearFile]")
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

TEST_CASE("Put N + Get Odds + Remove Even StorageCacheLinearFile", "[runtime],[Put],[Get],[Remove],[StorageCacheLinearFile]")
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
