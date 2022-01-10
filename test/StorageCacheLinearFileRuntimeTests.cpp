#include "KVCache/StorageCache/StorageCacheLinearFile.h"
#include "testHelpers.h"
#include <catch2/catch.hpp>
#include <vector>


TEST_CASE("Put 1 KV Pair StorageCacheLinearFile", "[runtime],[Put],[Singlepair],[StorageCacheLinearFile][SingleThread]")
{

    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 1);
}

TEST_CASE("Put 2 KV Pairs StorageCacheLinearFile", "[runtime],[Put],[Multipair],[StorageCacheLinearFiles][SingleThread]")
{

    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key1 = "TestKey";
    const std::string value1 = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key1, value1));
    REQUIRE(storageCache->size() == 1);

    // Put Second KV Pair
    const std::string key2 = "TestKey2";
    const std::string value2 = "TestValue2";
    REQUIRE_NOTHROW(storageCache->put(key2, value2));
    REQUIRE(storageCache->size() == 2);
}

TEST_CASE("Put + Get KV Pair StorageCacheLinearFile Single Thread", "[runtime],[Put],[Get],[Singlepair],[StorageCacheLinearFile][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 1);

    // Get KV Pair
    REQUIRE_NOTHROW(storageCache->get(key));
    auto optionalPair = storageCache->get(key);
    REQUIRE(optionalPair.has_value());
    const auto& keyRead = optionalPair.value().first;
    const auto& valueRead = optionalPair.value().second;
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);
}

TEST_CASE("Put + Get + Update KV Pair StorageCacheLinearFile Single Thread", "[runtime],[Put],[Get],[Singlepair],[StorageCacheLinearFile][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 1);

    // Get KV Pair
    REQUIRE_NOTHROW(storageCache->get(key));
    auto optionalPair = storageCache->get(key);
    REQUIRE(optionalPair.has_value());
    const auto& keyRead = optionalPair.value().first;
    const auto& valueRead = optionalPair.value().second;
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);

    // Update KV Pair
    const std::string newValue = "NewTestValue";
    REQUIRE_NOTHROW(storageCache->put(key, newValue));
    REQUIRE(storageCache->size() == 1);

    // Get updated KV Pair
    REQUIRE_NOTHROW(storageCache->get(key));
    auto optionalPair2 = storageCache->get(key);
    REQUIRE(optionalPair2.has_value());
    const auto& keyRead2 = optionalPair2.value().first;
    const auto& valueRead2 = optionalPair2.value().second;
    REQUIRE(keyRead2 == key);
    REQUIRE(valueRead2 == newValue);
}

TEST_CASE("Get returns empty optional on Empty StorageCacheLinearFile Single Thread", "[runtime],[Get],[Singlepair],[StorageCacheLinearFile][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Get Faillure
    const std::string key = "TestKey";
    REQUIRE_NOTHROW(storageCache->get(key));
    auto optionalPair = storageCache->get(key);
    REQUIRE(!optionalPair.has_value());
}

TEST_CASE("Put + Remove KV Pair StorageCacheLinearFile Single Thread", "[runtime],[Put],[Remove],[Singlepair],[StorageCacheLinearFile][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 1);

    // Remove KV Pair
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = storageCache->remove(key));
    REQUIRE(removeFlag);
    REQUIRE(storageCache->size() == 0);

    // Get KV Pair
    REQUIRE_NOTHROW(storageCache->get(key));
    auto optionalPair = storageCache->get(key);
    REQUIRE(!optionalPair.has_value());
}


TEST_CASE("Remove doesn't fail when key isn't present in StorageCacheLinearFile in Single Thread", "[runtime],[Remove],[Singlepair],[StorageCacheLinearFile][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Remove KV Pair
    const std::string key = "TestKey";
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = storageCache->remove(key));
    REQUIRE(!removeFlag);
    REQUIRE(storageCache->size() == 0);
}

TEST_CASE("Put + Remove + Get Faillure KV Pair StorageCacheLinearFile Single Thread", "[runtime],[Put],[Get],[Remove],[Singlepair],[StorageCacheLinearFile]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 1);

    // Remove KV Pair
    bool removeFlag = false;
    REQUIRE_NOTHROW(removeFlag = storageCache->remove(key));
    REQUIRE(removeFlag);
    REQUIRE(storageCache->size() == 0);

    // Get Faillure
    REQUIRE_NOTHROW(storageCache->get(key));
    auto optionalPair = storageCache->get(key);
    REQUIRE(!optionalPair.has_value());
}


TEST_CASE("Put N + Get N KV Pair StorageCacheLinearFile Single Thread", "[runtime],[Put],[Get],[Multipair],[StorageCacheLinearFile],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize StorageCache
        auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
        auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
        auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                      storageType);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(storageCache->put(keys.at(i), values.at(i)));
            REQUIRE(storageCache->size() == i + 1);
        }

        // Get KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(storageCache->get(keys.at(i)));
            REQUIRE(storageCache->size() == numSamples);
            auto optionalPair = storageCache->get(keys.at(i));
            REQUIRE(optionalPair.has_value());
            const auto& keyRead = optionalPair.value().first;
            const auto& valueRead = optionalPair.value().second;
            REQUIRE(keyRead == keys.at(i));
            REQUIRE(valueRead == values.at(i));
        }
    }
}

TEST_CASE("Put N + Get N + Update N/2 KV Pair StorageCacheLinearFile Single Thread", "[runtime],[Put],[Get],[Multipair],[StorageCacheLinearFile],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize StorageCache
        auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
        auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
        auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                      storageType);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(storageCache->put(keys.at(i), values.at(i)));
            REQUIRE(storageCache->size() == i + 1);
        }

        // Get KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(storageCache->get(keys.at(i)));
            REQUIRE(storageCache->size() == numSamples);
            auto optionalPair = storageCache->get(keys.at(i));
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
                REQUIRE_NOTHROW(storageCache->put(keys.at(i), values.at(i - 1)));
                REQUIRE(storageCache->size() == numSamples);
            }
        }

        // Get KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(storageCache->get(keys.at(i)));
            REQUIRE(storageCache->size() == numSamples);
            auto optionalPair = storageCache->get(keys.at(i));
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

TEST_CASE("Put N + Remove N StorageCacheLinearFile Single Thread", "[runtime],[Put],[Remove],[Multipairs],[StorageCacheLinearFile],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize StorageCache
        auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
        auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
        auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                      storageType);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(storageCache->put(keys.at(i), values.at(i)));
            REQUIRE(storageCache->size() == i + 1);
        }

        // Remove KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            bool removeFlag = false;
            REQUIRE_NOTHROW(removeFlag = storageCache->remove(keys.at(i)));
            REQUIRE(removeFlag);
            REQUIRE(storageCache->size() == numSamples - i - 1);
        }
    }
}

TEST_CASE("Put N + Get Odds + Remove Even StorageCacheLinearFile Single Thread", "[runtime],[Put],[Get],[Remove],[Multipair],[StorageCacheLinearFile],[SingleThread]")
{

    std::vector<size_t> numSamplesVector = {4, 10, 100, 1000};
    for (const auto numSamples: numSamplesVector)
    {

        // Initialize StorageCache
        auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
        auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
        auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                      storageType);

        // Generate keys and values
        auto [keys, values] = TestHelper::generateKVPairs(numSamples);

        // Put KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            REQUIRE_NOTHROW(storageCache->put(keys.at(i), values.at(i)));
            REQUIRE(storageCache->size() == i + 1);
        }

        // Get Odd KV Pairs and Remove Even KV Pairs
        for (size_t i = 0; i < numSamples; i++)
        {
            const auto currentSize = storageCache->size();
            if (i % 2 == 0)   // Even => Remove
            {
                bool removeFlag = false;
                REQUIRE_NOTHROW(removeFlag = storageCache->remove(keys.at(i)));
                REQUIRE(removeFlag);
                REQUIRE(storageCache->size() == currentSize - 1);
            }
            else   // Odd => Get
            {
                REQUIRE_NOTHROW(storageCache->get(keys.at(i)));
                REQUIRE(storageCache->size() == currentSize);
                auto optionalPair = storageCache->get(keys.at(i));
                REQUIRE(optionalPair.has_value());
                const auto& keyRead = optionalPair.value().first;
                const auto& valueRead = optionalPair.value().second;
                REQUIRE(keyRead == keys.at(i));
                REQUIRE(valueRead == values.at(i));
            }
        }
    }
}
