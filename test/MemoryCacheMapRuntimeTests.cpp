#include "KVCache/MemoryCache/MemoryCacheMap.h"
#include <catch2/catch.hpp>


TEST_CASE("Put 1 KV Pair into MemoryCacheMap by Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{

    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
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

TEST_CASE("Put 2 KV Pairs into MemoryCacheMap by Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
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

TEST_CASE("Put + Get KV Pair into MemoryCacheMap by Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
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
    auto [keyRead, valueRead] = memCache->get(key);
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);
}

TEST_CASE("Put + Get + Update KV Pair into MemoryCacheMap by Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
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
    const auto [keyRead, valueRead] = memCache->get(key);
    REQUIRE(keyRead == key);
    REQUIRE(valueRead == value);

    // Update KV Pair
    const std::string newValue = "NewTestValue";
    REQUIRE_NOTHROW(memCache->put(key, newValue));
    REQUIRE(memCache->size() == 1);

    // Get updated KV Pair
    REQUIRE_NOTHROW(memCache->get(key));
    const auto [keyRead2, valueRead2] = memCache->get(key);
    REQUIRE(keyRead2 == key);
    REQUIRE(valueRead2 == newValue);
}

TEST_CASE("Get Remove Faillure on Empty MemoryCacheMap by Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Get Faillure
    const std::string key = "TestKey";
    REQUIRE_THROWS(memCache->get(key));
}

TEST_CASE("Put + Remove KV Pair into MemoryCacheMap by Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
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
    REQUIRE_NOTHROW(memCache->remove(key));
    REQUIRE(memCache->size() == 0);

    // Get KV Pair
    REQUIRE_THROWS(memCache->get(key));
}


TEST_CASE("Remove doesn't fail when key isn't present in Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
    auto memType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;
    auto evictionStrategy = KVCache::Interface::CacheEvictionStrategy::FIFO;
    auto memCache = KVCache::Internal::MemoryCache::AbstractMemoryCache::createMemoryCache(memMaxSizeMB,
                                                                                           memType,
                                                                                           evictionStrategy);

    // Remove KV Pair
    const std::string key = "TestKey";
    REQUIRE_NOTHROW(memCache->remove(key));
    REQUIRE(memCache->size() == 0);
}

TEST_CASE("Put + Remove + Get Faillure KV Pair into MemoryCacheMap by Single Thread", "[runtime],[MemoryCacheMap][SingleThread]")
{
    // Initialize MemCache
    auto memMaxSizeMB = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;
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
    REQUIRE_NOTHROW(memCache->remove(key));
    REQUIRE(memCache->size() == 0);

    // Get Faillure
    REQUIRE_THROWS(memCache->get(key));
}