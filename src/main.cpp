#include <docopt/docopt.h>
#include <fstream>
#include <spdlog/spdlog.h>


#include "KVCache/KVCacheInterface/KVCacheAbstract.h"

static constexpr auto USAGE =
    R"(KVCache Client App.
 Usage:
    KVCacheClient [--option=value]
 Options:
          --memCacheMaxSizeMB       Max size of the Memory Cache in MB. Default 1 MB. Must be an Integer Value.
          --memoryCacheType         Type of MemoryCache: UNORDERED_MAP | ORDERED_MAP. Default is UNORDERED_MAP
          --storageCacheType        Type of StorageCache: NONE | LINEAR_FILE. Default is NONE.
          --cacheEvictionStrategy   Algorithm for Cache Eviction when the MemoryCache is full: FIFO. Default is FIFO
          --storagePath             Path of the StorageCache. Default is current directory.
          --fileLoad                Path of a file to load into the cache. The file will need to have the KV Pairs on consecutive lines 
                                        Line 1: Key1
                                        Line 2: Value1
                                        Line3: Key2
                                        Line4: Value2
                                    ...
                                    Empty lines will be ignored.
          -h --help                 Show this screen.
          --version                 Show version.
)";

int main(int argc, const char** argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
                                                               {std::next(argv), std::next(argv, argc)},
                                                               true,   // show help if requested
                                                               "KVCacheClient 1.0");   // version string

    spdlog::info("Starting Up KV Cache Client");

    const std::string memCacheMaxSizeMBString = "memCacheMaxSizeMB";
    auto memCacheMaxSizeMBValue = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;

    const std::string memoryCacheTypeString = "memoryCacheType";
    auto memoryCacheType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;

    const std::string storageCacheTypeString = "storageCacheType";
    auto storageCacheType = KVCache::Interface::StorageCacheType::NONE;

    const std::string cacheEvictionStrategyString = "cacheEvictionStrategy";
    auto cacheEvictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;

    const std::string storagePathString = "storagePath";
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;

    const std::string fileLoadString = "fileLoad";
    bool fileLoadFlag = false;
    std::string fileLoad = "";

    // Log Args
    std::string logArgsMes = "Received Args: \n";
    for (auto const& arg: args)
    {
        logArgsMes += arg.first + " = " + arg.second.asString() + "\n";
    }

    try
    {

        // Analyze Args
        for (auto const& arg: args)
        {
            if (arg.first == memCacheMaxSizeMBString)
            {
                const auto value = arg.second.asLong();
                if (value <= 0)
                {
                    throw std::runtime_error(arg.first + " value should be positive");
                }
                memCacheMaxSizeMBValue = static_cast<size_t>(value);
            }
            else if (arg.first == memoryCacheTypeString)
            {
                const auto str = arg.second.asString();
                memoryCacheType = KVCache::Interface::StrToMemoryCacheTypeMap.at(str);
            }
            else if (arg.first == storageCacheTypeString)
            {
                const auto str = arg.second.asString();
                storageCacheType = KVCache::Interface::StrToStorageCacheTypeMap.at(str);
            }
            else if (arg.first == cacheEvictionStrategyString)
            {
                const auto str = arg.second.asString();
                cacheEvictionStrategy = KVCache::Interface::StrToCacheEvictionStrategyTypeMap.at(str);
            }
            else if (arg.first == storagePathString)
            {
                const auto str = arg.second.asString();
                if (str.empty())
                {
                    throw std::runtime_error("Storage Path value is empty");
                }
                storagePath = str;
            }
            else if (arg.first == fileLoadString)
            {
                const auto str = arg.second.asString();
                if (str.empty())
                {
                    throw std::runtime_error("FileLoad value is empty");
                }
                fileLoad = str;
                fileLoadFlag = true;
            }
            else
            {
                throw std::runtime_error("Unkwnown Argument Option: " + arg.first);
            }
        }

        // Create Optional Params Struct
        KVCache::Interface::KVOptionalParameters optionalParams{memCacheMaxSizeMBValue,
                                                                memoryCacheType,
                                                                storageCacheType,
                                                                cacheEvictionStrategy,
                                                                storagePath};
        spdlog::info("KVCache Parameters:\n{}", optionalParams.toString());

        // Create KV Cache Object
        spdlog::info("Creating KVCache Object");
        auto kvCache = KVCache::Interface::KVCacheAbstract::createKVCache();
        spdlog::info("KVCache Object Created Succesfully");

        // Populate with Given File
        if (fileLoadFlag)
        {
            std::ifstream fileLoadStream{fileLoad};
            for (std::string readKey; std::getline(fileLoadStream, readKey);)
            {

                // Ignore Empty Lines
                if (readKey.empty() || readKey == "\n")
                {
                    continue;
                }

                // Read the value
                std::string readValue;
                std::getline(fileLoadStream, readValue);

                // Write KVPair into kvCache
                kvCache->put(readKey, readValue);
            }
        }
    }
    catch (const std::exception& e)
    {
        spdlog::error("KV Cache Client Error: " + std::string(e.what()));
    }
    catch (...)
    {
        spdlog::error("KV Cache Client Error: Unknown Error");
    }


    // Closing Up
    spdlog::info("Closing Up KV Cache Client");

    return 0;
}
