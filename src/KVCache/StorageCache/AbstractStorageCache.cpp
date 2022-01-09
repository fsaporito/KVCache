#include "AbstractStorageCache.h"
#include "spdlog/sinks/basic_file_sink.h"   // support for basic file logging
#include "StorageCacheLinearFile.h"
#include "StorageCacheNone.h"
#include "UnknownStorageCacheTypeException.h"
#include <memory>

using namespace KVCache::Internal::StorageCache;

AbstractStorageCache::AbstractStorageCache(const std::string& storagePath,
                                           const std::string& loggerOutputPath)
    : m_storagePath(storagePath)
{
    m_logger = spdlog::basic_logger_mt("StorageCache", loggerOutputPath);
    m_logger->info("AbstractStorageCache on path {}", m_storagePath);
}

std::unique_ptr<AbstractStorageCache> AbstractStorageCache::createStorageCache(const std::string& storagePath,
                                                                               KVCache::Interface::StorageCacheType storageType)
{
    auto m_logger = spdlog::basic_logger_mt("createStorageCache", "logs/createStorageCache.log");
    m_logger->info("create storage cache of Type {}", KVCache::Interface::StorageCacheTypeToString(storageType));
    switch (storageType)
    {
        using enum KVCache::Interface::StorageCacheType;
        case NONE:
            return std::make_unique<StorageCacheNone>(storagePath);
        case LINEAR_FILE:
            return std::make_unique<StorageCacheLinearFile>(storagePath);
        default:
            throw UnknownStorageCacheTypeException("Unknown StorageCacheType Type");
    }
}

std::string AbstractStorageCache::getStoragePath() const
{
    return m_storagePath;
}