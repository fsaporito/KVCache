#include "StorageCacheLinearFile.h"

#include <filesystem>
#include <stdexcept>


using namespace KVCache::Internal::StorageCache;


StorageCacheLinearFile::StorageCacheLinearFile(const std::string& storagePath)
    : AbstractStorageCache(storagePath, "StorageCacheLinearFile")
{
    std::filesystem::remove(m_storagePath);
    m_logger->info("StorageCacheNone Object Created");
};


void StorageCacheLinearFile::put(const std::string& key, const std::string& value)
{

    std::lock_guard<std::mutex> guard(m_fileMutex);
    m_logger->info("StorageCacheLinearFile::put() of key={}", key);

    std::ifstream pathStream{m_storagePath};

    const std::string pathBkp = m_storagePath + "__bkp.temp";
    std::ofstream ostreamBkp{pathBkp};

    bool valueWasAlreadyUpdated = false;

    for (std::string readKey; std::getline(pathStream, readKey);)
    {

        // Ignore Empty Lines
        if (readKey.empty() || readKey == "\n")
        {
            continue;
        }

        // Read the value
        std::string readValue;
        std::getline(pathStream, readValue);

        // Value was already found and updated, just copy over the read data
        if (valueWasAlreadyUpdated)
        {
            ostreamBkp << readKey << "\n"
                       << readValue << "\n";
            continue;
        }

        // Copy the key
        ostreamBkp << readKey << "\n";

        // If Key was found, update the value, otherwise just copy the old one
        if (key == readKey)
        {
            m_logger->info("StorageCacheLinearFile::put() key={} is present, value will be updated", key);
            ostreamBkp << value << "\n";
            valueWasAlreadyUpdated = true;
            m_currentByteSize -= readValue.size();
            m_currentByteSize += (value.size()) * sizeof(char);
        }
        else
        {
            ostreamBkp << readValue + "\n";
        }
    }

    // Add value if it wasn't found
    if (!valueWasAlreadyUpdated)
    {
        m_logger->info("StorageCacheLinearFile::put() key={} isn't present, value will be added", key);
        if (m_currentSize == 0)   // Add Directly the KV Pair without a new line
        {
            ostreamBkp << key << "\n"
                       << value << "\n";
        }
        else   // Add a new line before the KV Pair
        {
            ostreamBkp << "\n"
                       << key << "\n"
                       << value;
        }
        constexpr size_t NUMBER_OF_INTRODUCED_NEW_LINES = 1;
        m_currentByteSize += (key.size() + value.size() + NUMBER_OF_INTRODUCED_NEW_LINES * NUMBER_OF_CHARACTERS_IN_NEW_LINE) * sizeof(char);
        m_currentSize += 1;
    }

    // Switch the original file with the new one
    std::filesystem::remove(m_storagePath);
    std::filesystem::rename(pathBkp, m_storagePath);


    m_logger->info("StorageCacheLinearFile::put() completed for key={}, new bytesize={}", key, m_currentByteSize);
}

bool StorageCacheLinearFile::remove(const std::string& key)
{

    std::lock_guard<std::mutex> guard(m_fileMutex);

    m_logger->info("StorageCacheLinearFile::remove() remove key={}", key);

    std::ifstream pathStream{m_storagePath};

    const std::string pathBkp = m_storagePath + "__bkp.temp";
    std::ofstream ostreamBkp{pathBkp};

    bool valueWasAlreadyRemoved = false;

    for (std::string readKey; std::getline(pathStream, readKey);)
    {

        // Ignore Empty Lines
        if (readKey.empty() || readKey == "\n")
        {
            continue;
        }

        // Read the value
        std::string readValue;
        std::getline(pathStream, readValue);

        // Value was already found and removed, just copy over the read data
        if (valueWasAlreadyRemoved)
        {
            ostreamBkp << readKey << "\n"
                       << readValue << "\n";
            continue;
        }

        // If Key was found, remove key and value, otherwise just copy the old ones
        if (key == readKey)   // Key Was Found
        {
            m_currentByteSize -= readKey.size() + readValue.size();
            m_currentSize -= 1;
            valueWasAlreadyRemoved = true;
        }
        else
        {
            ostreamBkp << readKey << "\n"
                       << readValue << "\n";
        }
    }

    // Switch the original file with the new one
    std::filesystem::remove(m_storagePath);
    std::filesystem::rename(pathBkp, m_storagePath);

    return valueWasAlreadyRemoved;
}


std::optional<std::pair<std::string, std::string>> StorageCacheLinearFile::get(const std::string& key) const
{
    std::lock_guard<std::mutex> guard(m_fileMutex);
    std::ifstream pathStream{m_storagePath};
    for (std::string readKey; std::getline(pathStream, readKey);)
    {

        // Ignore Empty Lines
        if (readKey.empty() || readKey == "\n")
        {
            continue;
        }

        // Read the value
        std::string value;
        std::getline(pathStream, value);

        // If the key was found, return, otherwise continue
        if (key == readKey)   // Key Was Found
        {
            m_logger->info("StorageCacheLinearFile::get() found key={}", key);
            return std::make_pair(key, value);
        }
    }
    m_logger->error("StorageCacheLinearFile::get() failed for key={}", key);
    return {};
}


size_t StorageCacheLinearFile::getByteSize() const
{
    std::lock_guard<std::mutex> guard(m_fileMutex);
    m_logger->info("StorageCacheLinearFile::getByteSize() = {}", m_currentByteSize);
    return m_currentByteSize;
}

size_t StorageCacheLinearFile::size() const
{
    std::lock_guard<std::mutex> guard(m_fileMutex);
    m_logger->info("StorageCacheLinearFile::getSize() = {}", m_currentSize);
    return m_currentSize;
}