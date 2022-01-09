#include "KVCache/StorageCache/StorageCacheLinearFile.h"
#include "KVCache/StorageCache/StorageCacheNone.h"
#include <catch2/catch.hpp>


TEST_CASE("Create StorageCache of Type None", "[creation],[StorageCache][StorageCacheNone]")
{
    auto storageType = KVCache::Interface::StorageCacheType::NONE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    REQUIRE_NOTHROW(KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                              storageType));
}

TEST_CASE("Create StorageCache of Type Linear File", "[creation],[StorageCache][StorageCacheLinearFile]")
{
    auto storageType = KVCache::Interface::StorageCacheType::LINEAR_FILE;
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    REQUIRE_NOTHROW(KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                              storageType));
}

TEST_CASE("Create StorageCache with Unknown Type", "[creation],[StorageCache]")
{
    auto storageType = static_cast<KVCache::Interface::StorageCacheType>(100);
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;
    REQUIRE_THROWS(KVCache::Internal::StorageCache::AbstractStorageCache::createStorageCache(storagePath,
                                                                                             storageType));
}