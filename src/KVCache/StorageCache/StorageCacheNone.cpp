#include "StorageCacheNone.h"
#include <spdlog/spdlog.h>
#include <stdexcept>

using namespace KVCache::Internal::StorageCache;


StorageCacheNone::StorageCacheNone(const std::string& storagePath)
    : AbstractStorageCache(storagePath, "logs/StorageCacheNone.log")
{
    spdlog::trace("StorageCacheNone Object Created");
};


void StorageCacheNone::put(const std::string& key, const std::string& value)
{
    spdlog::trace("StorageCacheNone::put() completed for key={}, new bytesize={}, value has size of {}", key, m_currentByteSize, value.size());
}


bool StorageCacheNone::remove(const std::string& key)
{
    spdlog::trace("StorageCacheNone::remove() remove key={}", key);
    return false;
}


std::optional<std::pair<std::string, std::string>> StorageCacheNone::get(const std::string& key) const
{
    spdlog::trace("StorageCacheNone::get() failed for key={}", key);
    return {};
}


size_t StorageCacheNone::getByteSize() const
{
    spdlog::trace("StorageCacheNone::getByteSize() = {}", m_currentByteSize);
    return m_currentByteSize;
}

size_t StorageCacheNone::size() const
{
    spdlog::trace("StorageCacheNone::getSize() = {}", m_currentSize);
    return m_currentSize;
}