#include "KVCache/KVCacheInterface/KVCacheAbstract.h"
#include <catch2/catch.hpp>


TEST_CASE("Create KVCache with default parameters", "[creation],[KVCache]")
{
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache());
}

TEST_CASE("Create KVCache Size 1MB", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::FIFO,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}

TEST_CASE("Create KVCache Size 10MB", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_10_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::FIFO,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}

TEST_CASE("Create KVCache Mem Cache UNORDERED MAP", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::FIFO,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}


TEST_CASE("Create KVCache Mem Cache ORDERED MAP", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::FIFO,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}

TEST_CASE("Create KVCache Storage Cache None", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::ORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::FIFO,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}

TEST_CASE("Create KVCache Storage Cache LINEAR FILE", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::LINEAR_FILE,
                                                            KVCache::Interface::CacheEvictionStrategy::FIFO,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}

TEST_CASE("Create KVCache Cache Eviction Strategy FIFO", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::FIFO,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}

TEST_CASE("Create KVCache Cache Eviction Strategy LRU", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::LRU,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}

TEST_CASE("Create KVCache Cache Eviction Strategy FLU", "[creation],[KVCache]")
{
    KVCache::Interface::KVOptionalParameters optionalParams{KVCache::Interface::SizeConstraint::MAXSIZE_1_MB,
                                                            KVCache::Interface::MemoryCacheType::UNORDERED_MAP,
                                                            KVCache::Interface::StorageCacheType::NONE,
                                                            KVCache::Interface::CacheEvictionStrategy::FLU,
                                                            KVCache::Interface::StoragePath::defaultStoragePath};
    REQUIRE_NOTHROW(KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams));
}
