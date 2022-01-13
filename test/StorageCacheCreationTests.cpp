#include "KVCache/StorageCache/StorageCacheLinearFile.h"
#include "KVCache/StorageCache/StorageCacheNone.h"
#include <catch2/catch.hpp>

// This Macro Generates Data for RuntimeTests
#define generateData()                                                                                                          \
    auto storageType = GENERATE(KVCache::Interface::StorageCacheType::NONE, KVCache::Interface::StorageCacheType::LINEAR_FILE); \
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;                                                     \
    INFO("      -storageType=" << KVCache::Interface::StorageCacheToStrMap().at(storageType)                                    \
                               << "storagePath=" << storagePath);                                                               \
    REQUIRE_NOTHROW(KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath, storageType));


TEST_CASE("Create StorageCache", "[creation],[StorageCache]")
{
    generateData();
}

TEST_CASE("Create StorageCache with Unknown Type", "[creation],[StorageCache]")
{
    auto storageType = static_cast<KVCache::Interface::StorageCacheType>(100);
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    REQUIRE_THROWS(KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                             storageType));
}