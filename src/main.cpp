#include <docopt/docopt.h>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>


#include "KVCache/KVCacheInterface/KVCacheAbstract.h"

static constexpr auto USAGE =
    R"(KVCache Client

 Usage:
    KVCacheClient [--memCacheMaxSizeMB=<mb>] [--memoryCacheType=<memType>] [--storageCacheType=<storageType>] [--cacheEvictionStrategy=<cacheEviction>] [--storagePath=<path>] [--fileLoad=<filePath>] 
    KVCacheClient (-h | --help)
    KVCacheClient --version
 
 Options:
          --memCacheMaxSizeMB=<mb>                  Max size as Integer of the Memory Cache in MB. [Default 1 MB].
          --memoryCacheType=<memType>               Type of MemoryCache: (UNORDERED_MAP | ORDERED_MAP). [Default is UNORDERED_MAP].
          --storageCacheType=<storageType>          Type of StorageCache: (NONE | LINEAR_FILE). [Default is NONE].
          --cacheEvictionStrategy=<cacheEviction>   Algorithm for Cache Eviction when the MemoryCache is full: (FIFO | LIFO | LRU | MRU). [Default is FIFO].
          --storagePath=<path>                      Path of the StorageCache. Default is current directory.
          --fileLoad=<filePath>                     Path of a file to load into the cache. The file will need to have the KV Pairs on consecutive lines
          -h --help                                 Show this screen.
          --version                                 Show version.
)";

int main(int argc, const char** argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
                                                               {argv + 1, argv + argc},
                                                               true,   // show help if requested
                                                               "KVCacheClient 1.0");   // version string

    spdlog::info("Starting Up KV Cache Client");

    const std::string memCacheMaxSizeMBString = "--memCacheMaxSizeMB";
    auto memCacheMaxSizeMBValue = KVCache::Interface::SizeConstraint::MAXSIZE_1_MB;

    const std::string memoryCacheTypeString = "--memoryCacheType";
    auto memoryCacheType = KVCache::Interface::MemoryCacheType::UNORDERED_MAP;

    const std::string storageCacheTypeString = "--storageCacheType";
    auto storageCacheType = KVCache::Interface::StorageCacheType::NONE;

    const std::string cacheEvictionStrategyString = "--cacheEvictionStrategy";
    auto cacheEvictionStrategy = KVCache::Interface::CacheEvictionStrategyType::FIFO;

    const std::string storagePathString = "--storagePath";
    auto storagePath = KVCache::Interface::StoragePath::defaultStoragePath;

    const std::string fileLoadString = "--fileLoad";
    bool fileLoadFlag = false;
    std::string fileLoad = "";

    try
    {

        /**
        // Log Args
        std::stringstream ss;
        std::string logArgsMes = "Received Args: \n";
        for (auto const& arg: args)
        {
            ss << arg.first << " = " << arg.second << "\n";
        }
        spdlog::info("KVCacheClient Arguments:\n{}", ss.str());
        */

        // Analyze Args
        spdlog::info("KVCacheClient - Analyzing Arguments ...");
        for (auto const& arg: args)
        {
            if (arg.first == memCacheMaxSizeMBString)
            {
                if (!arg.second)   // Argument is Empty
                {
                    continue;
                }
                const auto value = arg.second.asLong();
                if (value <= 0)
                {
                    throw std::runtime_error(arg.first + " value should be positive");
                }
                memCacheMaxSizeMBValue = static_cast<size_t>(value);
            }
            else if (arg.first == memoryCacheTypeString)
            {
                if (!arg.second)   // Argument is Empty
                {
                    continue;
                }
                const auto str = arg.second.asString();
                memoryCacheType = KVCache::Interface::StrToMemoryCacheTypeMap.at(str);
            }
            else if (arg.first == storageCacheTypeString)
            {
                if (!arg.second)   // Argument is Empty
                {
                    continue;
                }
                const auto str = arg.second.asString();
                storageCacheType = KVCache::Interface::StrToStorageCacheTypeMap.at(str);
            }
            else if (arg.first == cacheEvictionStrategyString)
            {
                if (!arg.second)   // Argument is Empty
                {
                    continue;
                }
                const auto str = arg.second.asString();
                cacheEvictionStrategy = KVCache::Interface::StrToCacheEvictionStrategyTypeMap.at(str);
            }
            else if (arg.first == storagePathString)
            {
                if (!arg.second)   // Argument is Empty
                {
                    continue;
                }
                const auto str = arg.second.asString();
                if (str.empty())
                {
                    throw std::runtime_error("Storage Path value is empty (@line " + std::to_string(__LINE__) + ")");
                }
                storagePath = str;
            }
            else if (arg.first == fileLoadString)
            {
                if (!arg.second)   // Argument is Empty
                {
                    continue;
                }
                const auto str = arg.second.asString();
                if (str.empty())
                {
                    throw std::runtime_error("FileLoad value is empty (@line " + std::to_string(__LINE__) + ")");
                }
                fileLoad = str;
                fileLoadFlag = true;
            }
            else   // Ignore unknown arguments
            {
                continue;
            }
        }

        // Create Optional Params Struct
        KVCache::Interface::KVOptionalParameters optionalParams{memCacheMaxSizeMBValue,
                                                                memoryCacheType,
                                                                storageCacheType,
                                                                cacheEvictionStrategy,
                                                                storagePath};
        spdlog::info("KVCache Parameters:\n{}loadedFile: {}", optionalParams.toString(), fileLoad);

        // Create KV Cache Object
        spdlog::info("Creating KVCache Object");
        auto kvCache = KVCache::Interface::KVCacheAbstract::createKVCache(optionalParams);
        spdlog::info("KVCache Object Created Succesfully");

        // Populate with Given File
        if (fileLoadFlag)
        {
            spdlog::info("Loading File Into KVCache: {}", fileLoad);
            std::ifstream fileLoadStream{fileLoad};
            std::vector<std::pair<std::string, std::string>> readKVPairs;
            size_t readKVPairsNum = 0;
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
                readKVPairsNum++;

                // Write KVPair into kvCache and into a temp vector
                kvCache->put(readKey, readValue);
            }
            spdlog::info("Read {} lines from", fileLoad);

            // Test that the kv Pairs are effectively in the cache
            if (kvCache->size() != readKVPairsNum)
            {
                throw std::runtime_error("KVCache has size of "
                                         + std::to_string(kvCache->size())
                                         + " but the file had "
                                         + std::to_string(readKVPairsNum)
                                         + " kvPairs");
            }
            spdlog::info("KVCache has now a size of {} kvPairs", kvCache->size());
            for (const auto& kvPair: readKVPairs)
            {
                const auto& [originalKey, originalValue] = kvPair;
                const auto optionalKVPair = kvCache->get(originalKey);
                if (!optionalKVPair.has_value())
                {
                    throw std::runtime_error("KVCache has no key " + originalKey);
                }
                const auto& [cacheKey, cacheValue] = optionalKVPair.value();
                if (originalKey != cacheKey)
                {
                    throw std::runtime_error("KVCache got a different key from the original one from the loaded file (@line " + std::to_string(__LINE__) + ")");
                    ;
                }
                if (originalValue != cacheValue)
                {
                    throw std::runtime_error("KVCache got different value from the original one from the loaded file (@line " + std::to_string(__LINE__) + ")");
                }
            }
            spdlog::info("KVCache is equal to the original file content :)");
        }
    }
    catch (const std::exception& e)
    {
        spdlog::error("KV Cache Client Error: " + std::string(e.what()));
    }
    catch (...)
    {
        spdlog::error("KV Cache Client Error: Unknown Error (@line " + std::to_string(__LINE__) + ")");
    }


    // Closing Up
    spdlog::info("Closing Up KV Cache Client");

    return 0;
}
