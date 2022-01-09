#include "KVCache/StorageCache/StorageCacheNone.h"
#include <catch2/catch.hpp>


TEST_CASE("Put 1 KV Pair into StorageCacheNone", "[runtime],[Put],[Singlepair],[StorageCacheNone][SingleThread]")
{

    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::NONE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 0);
}

TEST_CASE("Put 2 KV Pairs into StorageCacheNone", "[runtime],[Put],[Multipair],[StorageCacheNone][SingleThread]")
{

    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::NONE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key1 = "TestKey";
    const std::string value1 = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key1, value1));
    REQUIRE(storageCache->size() == 0);

    // Put Second KV Pair
    const std::string key2 = "TestKey2";
    const std::string value2 = "TestValue2";
    REQUIRE_NOTHROW(storageCache->put(key2, value2));
    REQUIRE(storageCache->size() == 0);
}

TEST_CASE("Get Always throws with StorageCacheNone", "[runtime],[Put],[Get],[Singlepair],[StorageCacheNone][SingleThread]")
{

    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::NONE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 0);
    REQUIRE(storageCache->getByteSize() == 0);

    // Get KV Pair
    REQUIRE_THROWS(storageCache->get(key));
}

TEST_CASE("Remove Doesn't Throw with StorageCacheNone Single Thread", "[runtime],[Put],[Remove],[Singlepair],[MemoryCacheMap][SingleThread]")
{
    // Initialize StorageCache
    auto storageType = KVCache::Interface::StorageCacheType::NONE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    auto storageCache = KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                                  storageType);

    // Put KV Pair
    const std::string key = "TestKey";
    const std::string value = "TestValue";
    REQUIRE_NOTHROW(storageCache->put(key, value));
    REQUIRE(storageCache->size() == 0);
    REQUIRE(storageCache->getByteSize() == 0);

    // Remove KV Pair
    REQUIRE_NOTHROW(storageCache->remove(key));
    REQUIRE(storageCache->size() == 0);
}