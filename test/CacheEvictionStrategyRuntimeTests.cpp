#include "KVCache/CacheEvictionStrategies/AbstractCacheEvictionStrategy.h"
#include "testHelpers.h"
#include <catch2/catch.hpp>

// This Macros Generates Data for RuntimeTests for All Eviction Strategies
#define generateData()                                                                                                                             \
    auto numSamples = static_cast<size_t>(GENERATE(1, 4, 10, 100, 1000));                                                                          \
    auto evictionStrategy = GENERATE(KVCache::Interface::CacheEvictionStrategyType::FIFO,                                                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LIFO,                                                          \
                                     KVCache::Interface::CacheEvictionStrategyType::LRU,                                                           \
                                     KVCache::Interface::CacheEvictionStrategyType::MRU);                                                          \
    INFO("      -numSamples=" << numSamples << " "                                                                                                 \
                                               "evictionStrategy="                                                                                 \
                              << KVCache::Interface::CacheEvictionStrategyToStrMap().at(evictionStrategy));                                        \
    auto cacheEvictor = KVCache::Internal::CacheEvictionsStrategies::AbstractCacheEvictionStrategy::createCacheEvictionStrategy(evictionStrategy); \
    auto [keys, values] = TestHelper::generateKVPairs(numSamples);


TEST_CASE("Put N Keys into CacheEvictor", "[runtime],[Put],[CacheEvictor]")
{

    // Generate Multiple Datasets and Inizialize cacheEvictor
    generateData();

    // Put KV Pairs
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cacheEvictor->put(keys.at(i)));
        REQUIRE(cacheEvictor->size() == i + 1);
    }
}

TEST_CASE("Put N + Remove N Keys into CacheEvictor", "[runtime],[Put],[CacheEvictor]")
{

    // Generate Multiple Datasets and Inizialize cacheEvictor
    generateData();

    // Put Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cacheEvictor->put(keys.at(i)));
        REQUIRE(cacheEvictor->size() == i + 1);
    }

    // Remove Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        cacheEvictor->remove(keys.at(i));
        REQUIRE(cacheEvictor->size() == numSamples - i - 1);
    }
}

TEST_CASE("Put N + Evict N Keys into CacheEvictor", "[runtime],[Put],[CacheEvictor]")
{

    // Generate Multiple Datasets and Inizialize cacheEvictor
    generateData();

    // Put Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cacheEvictor->put(keys.at(i)));
        REQUIRE(cacheEvictor->size() == i + 1);
    }

    // Evict Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        const auto evictedKey = cacheEvictor->evict();
        REQUIRE(evictedKey);
        const auto readKey = evictedKey.value();
        switch (evictionStrategy)
        {
            using enum KVCache::Interface::CacheEvictionStrategyType;
            case FIFO:
                REQUIRE(readKey == keys.at(i));
                break;
            case LIFO:
                REQUIRE(readKey == keys.at(numSamples - i - 1));
                break;
            case LRU:
                REQUIRE(readKey == keys.at(i));
                break;
            case MRU:
                REQUIRE(readKey == keys.at(numSamples - i - 1));
                break;
            default:
                FAIL();
                break;
        }
    }
}

TEST_CASE("Put N + Get N + Evict N Keys into CacheEvictor", "[runtime],[Put],[CacheEvictor]")
{

    // Generate Multiple Datasets and Inizialize cacheEvictor
    generateData();

    // Put Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cacheEvictor->put(keys.at(i)));
        REQUIRE(cacheEvictor->size() == i + 1);
    }

    // Get Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cacheEvictor->get(keys.at(i)));
        REQUIRE(cacheEvictor->size() == numSamples);
    }

    // Evict Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        const auto evictedKey = cacheEvictor->evict();
        REQUIRE(evictedKey);
        const auto readKey = evictedKey.value();
        switch (evictionStrategy)
        {
            using enum KVCache::Interface::CacheEvictionStrategyType;
            case FIFO:
                REQUIRE(readKey == keys.at(i));
                break;
            case LIFO:
                REQUIRE(readKey == keys.at(numSamples - i - 1));
                break;
            case LRU:
                REQUIRE(readKey == keys.at(i));
                break;
            case MRU:
                REQUIRE(readKey == keys.at(numSamples - i - 1));
                break;
            default:
                FAIL();
                break;
        }
    }
}

TEST_CASE("Put N + Get pos N/2 + Evict N Keys into CacheEvictor", "[runtime],[Put],[CacheEvictor]")
{

    // Generate Multiple Datasets and Inizialize cacheEvictor
    generateData();

    // Put Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cacheEvictor->put(keys.at(i)));
        REQUIRE(cacheEvictor->size() == i + 1);
    }

    // Get Key at n/2
    const auto numSamplesHalfPos = static_cast<size_t>(numSamples / 2);
    REQUIRE_NOTHROW(cacheEvictor->get(keys.at(numSamplesHalfPos)));
    REQUIRE(cacheEvictor->size() == numSamples);


    // Evict Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        const auto evictedKey = cacheEvictor->evict();
        REQUIRE(evictedKey);
        const auto readKey = evictedKey.value();
        switch (evictionStrategy)
        {
            using enum KVCache::Interface::CacheEvictionStrategyType;
            case FIFO:
                REQUIRE(readKey == keys.at(i));
                break;
            case LIFO:
                REQUIRE(readKey == keys.at(numSamples - i - 1));
                break;
            case LRU:
                if (i == numSamples - 1)
                {
                    REQUIRE(readKey == keys.at(numSamplesHalfPos));
                }
                else if (i == numSamplesHalfPos)
                {
                    continue;
                }
                else if (i < numSamplesHalfPos)
                {
                    REQUIRE(readKey == keys.at(i));
                }
                else   // if (i > numSamplesHalfPos)
                {
                    REQUIRE(readKey == keys.at(i + 1));
                }
                break;
            case MRU:
                if (i == 0)
                {
                    REQUIRE(readKey == keys.at(numSamplesHalfPos));
                }
                else if (i == numSamplesHalfPos)
                {
                    continue;
                }
                else if (i < numSamplesHalfPos)
                {
                    REQUIRE(readKey == keys.at(numSamples - i));
                }
                else   // if (i > numSamplesHalfPos)
                {
                    REQUIRE(readKey == keys.at(numSamples - i - 1));
                }
                break;
            default:
                FAIL();
                break;
        }
    }
}


TEST_CASE("Put N + Get All except pos N/2 + Evict N Keys into CacheEvictor", "[runtime],[Put],[CacheEvictor]")
{

    // Generate Multiple Datasets and Inizialize cacheEvictor
    generateData();

    // Put Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        REQUIRE_NOTHROW(cacheEvictor->put(keys.at(i)));
        REQUIRE(cacheEvictor->size() == i + 1);
    }

    // Get All Keys except  n/2
    const auto numSamplesHalfPos = static_cast<size_t>(numSamples / 2);
    for (size_t i = 0; i < numSamples; i++)
    {
        if (i == numSamplesHalfPos)
        {
            continue;
        }
        REQUIRE_NOTHROW(cacheEvictor->get(keys.at(i)));
        REQUIRE(cacheEvictor->size() == numSamples);
    }


    // Evict Keys
    for (size_t i = 0; i < numSamples; i++)
    {
        const auto evictedKey = cacheEvictor->evict();
        REQUIRE(evictedKey);
        const auto readKey = evictedKey.value();
        switch (evictionStrategy)
        {
            using enum KVCache::Interface::CacheEvictionStrategyType;
            case FIFO:
                REQUIRE(readKey == keys.at(i));
                break;
            case LIFO:
                REQUIRE(readKey == keys.at(numSamples - i - 1));
                break;
            case LRU:
                if (i == 0)
                {
                    REQUIRE(readKey == keys.at(numSamplesHalfPos));
                }
                else if (i == numSamplesHalfPos)
                {
                    continue;
                }
                else if (i < numSamplesHalfPos)
                {
                    REQUIRE(readKey == keys.at(i - 1));
                }
                else   // if (i > numSamplesHalfPos)
                {
                    REQUIRE(readKey == keys.at(i));
                }
                break;
            case MRU:
                if (i == numSamples - 1)
                {
                    REQUIRE(readKey == keys.at(numSamplesHalfPos));
                }
                else if (i == numSamples - numSamplesHalfPos)
                {
                    continue;
                }
                else if (i >= numSamples - numSamplesHalfPos - 1)
                {
                    REQUIRE(readKey == keys.at(numSamples - i - 2));
                }
                else   // if (i < numSamples - numSamplesHalfPos)
                {
                    REQUIRE(readKey == keys.at(numSamples - i - 1));
                }
                break;
            default:
                FAIL();
                break;
        }
    }
}