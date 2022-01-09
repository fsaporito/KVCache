#include "KVCache/StorageCache/StorageCacheLinearFile.h"
#include <catch2/catch.hpp>


TEST_CASE("Put 1 KV Pair into StorageCacheLinearFile", "[runtime],[StorageCacheLinearFile][SingleThread]")
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

TEST_CASE("Put 2 KV Pairs into StorageCacheLinearFile", "[runtime],[StorageCacheLinearFiles][SingleThread]")
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

TEST_CASE("Put + Get KV Pair into StorageCacheLinearFile by Single Thread", "[runtime],[StorageCacheLinearFile][SingleThread]")
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
    auto [keyRead, valueRead] = storageCache->get(key);
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);
}

TEST_CASE("Put + Get + Update KV Pair into StorageCacheLinearFile by Single Thread", "[runtime],[StorageCacheLinearFile][SingleThread]")
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
    const auto [keyRead, valueRead] = storageCache->get(key);
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);

    // Update KV Pair
    const std::string newValue = "NewTestValue";
    REQUIRE_NOTHROW(storageCache->put(key, newValue));
    REQUIRE(storageCache->size() == 1);

    // Get updated KV Pair
    REQUIRE_NOTHROW(storageCache->get(key));
    const auto [keyRead2, valueRead2] = storageCache->get(key);
    REQUIRE(keyRead2 == key);
    REQUIRE(valueRead2 == newValue);
}

TEST_CASE("Get Faillure on Empty StorageCacheLinearFile by Single Thread", "[runtime],[StorageCacheLinearFile][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Get Faillure
    const std::string key = "TestKey";
    REQUIRE_THROWS(storageCache->get(key));
}

TEST_CASE("Put + Remove KV Pair into StorageCacheLinearFile by Single Thread", "[runtime],[StorageCacheLinearFile][SingleThread]")
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
    REQUIRE_NOTHROW(storageCache->remove(key));
    REQUIRE(storageCache->size() == 0);

    // Get KV Pair
    REQUIRE_THROWS(storageCache->get(key));
}


TEST_CASE("Remove doesn't fail when key isn't present in StorageCacheLinearFile in Single Thread", "[runtime],[StorageCacheLinearFile][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Remove KV Pair
    const std::string key = "TestKey";
    REQUIRE_NOTHROW(storageCache->remove(key));
    REQUIRE(storageCache->size() == 0);
}

TEST_CASE("Put + Remove + Get Faillure KV Pair into StorageCacheLinearFile by Single Thread", "[runtime],[MemoryCacheMap][StorageCacheLinearFile]")
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
    REQUIRE_NOTHROW(storageCache->remove(key));
    REQUIRE(storageCache->size() == 0);

    // Get Faillure
    REQUIRE_THROWS(storageCache->get(key));
}