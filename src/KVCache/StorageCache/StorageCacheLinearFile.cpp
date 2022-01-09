#include "StorageCacheLinearFile.h"

#include <filesystem>
#include <stdexcept>


using namespace KVCache::Internal::StorageCache;


StorageCacheLinearFile::StorageCacheLinearFile(const std::string& storagePath)
    : AbstractStorageCache(storagePath, "logs/StorageCacheLinearFile.log")
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

    bool updateValue = false;
    bool valueWasAlreadyUpdated = false;
    bool nextValueIsKey = true;

    for (std::string line; std::getline(pathStream, line);)
    {

        // Value was already found and updated, just copy over the read data
        if (valueWasAlreadyUpdated)
        {
            ostreamBkp << line << "\n";
            continue;
        }

        // Next line is a key or an empty line
        if (line == "\n")
        {
            ostreamBkp << "\n";
            nextValueIsKey = true;
            continue;
        }

        // Analize the Key
        if (nextValueIsKey)
        {
            ostreamBkp << key << "\n";
            nextValueIsKey = false;
            if (key == line)   // Key Was Found
            {
                updateValue = true;
            }
            continue;
        }

        // Update the value if it was found by the previous iteration (Size remains the same)
        if (updateValue)
        {
            m_logger->info("StorageCacheLinearFile::put() key={} is present, value will be updated", key);
            ostreamBkp << value << "\n";
            updateValue = false;
            valueWasAlreadyUpdated = true;
            m_currentByteSize -= line.size();
            constexpr size_t NUMBER_OF_INTRODUCED_NEW_LINES = 1;
            m_currentByteSize += (value.size() + NUMBER_OF_INTRODUCED_NEW_LINES * NUMBER_OF_CHARACTERS_IN_NEW_LINE) * sizeof(char);
        }
        else   // Value is not the correct one, keep the old one
        {
            ostreamBkp << line << "\n";
        }
    }

    // Add value if it wasn't found
    if (!valueWasAlreadyUpdated)
    {
        m_logger->info("StorageCacheLinearFile::put() key={} isn't present, value will be added", key);
        ostreamBkp << key << "\n"
                   << value << "\n"
                   << "\n";
        constexpr size_t NUMBER_OF_INTRODUCED_NEW_LINES = 3;
        m_currentByteSize += (key.size() + value.size() + NUMBER_OF_INTRODUCED_NEW_LINES * NUMBER_OF_CHARACTERS_IN_NEW_LINE) * sizeof(char);
        m_currentSize += 1;
    }

    // Switch the original file with the new one
    std::filesystem::remove(m_storagePath);
    std::filesystem::rename(pathBkp, m_storagePath);


    m_logger->info("StorageCacheLinearFile::put() completed for key={}, new bytesize={}", key, m_currentByteSize);
}

void StorageCacheLinearFile::remove(const std::string& key)
{

    std::lock_guard<std::mutex> guard(m_fileMutex);

    m_logger->info("StorageCacheLinearFile::remove() remove key={}", key);

    std::ifstream pathStream{m_storagePath};

    const std::string pathBkp = m_storagePath + "__bkp.temp";
    std::ofstream ostreamBkp{pathBkp};

    size_t skipLines = 0;
    bool nextValueIsKey = true;
    bool valueWasAlreadyRemoved = false;

    for (std::string line; std::getline(pathStream, line);)
    {
        // Skip Current Line
        if (skipLines > 0)
        {
            skipLines--;
            continue;
        }

        // Value was already found and removed, just copy over the read data
        if (valueWasAlreadyRemoved)
        {
            ostreamBkp << line << "\n";
            continue;
        }

        // Next line is a key or an empty line
        if (line == "\n")
        {
            ostreamBkp << "\n";
            nextValueIsKey = true;
            continue;
        }

        // Analize the Key
        if (nextValueIsKey)
        {
            nextValueIsKey = false;
            if (key == line)   // Key Was Found
            {
                skipLines = 2;
                std::string value;
                std::getline(pathStream, value);
                m_currentByteSize -= line.size();
                constexpr size_t NUMBER_OF_NEW_LINES = 3;
                m_currentByteSize += (key.size() + value.size() + NUMBER_OF_NEW_LINES * NUMBER_OF_CHARACTERS_IN_NEW_LINE) * sizeof(char);
                m_currentSize -= 1;
                valueWasAlreadyRemoved = true;
            }
            else
            {
                ostreamBkp << line;
            }
        }
        else
        {
            ostreamBkp << line;
        }
    }

    // Switch the original file with the new one
    std::filesystem::remove(m_storagePath);
    std::filesystem::rename(pathBkp, m_storagePath);
}


std::pair<std::string, std::string> StorageCacheLinearFile::get(const std::string& key) const
{
    std::lock_guard<std::mutex> guard(m_fileMutex);
    std::ifstream pathStream{m_storagePath};
    bool nextValueIsKey = true;
    size_t skipLines = 0;
    for (std::string line; std::getline(pathStream, line);)
    {
        // Skip Current Line
        if (skipLines > 0)
        {
            skipLines--;
            continue;
        }

        // Next line is a key or an empty line
        if (line == "\n")
        {
            nextValueIsKey = true;
            continue;
        }

        // Analize the Key
        if (nextValueIsKey)
        {
            nextValueIsKey = false;
            if (key == line)   // Key Was Found
            {
                std::string value;
                std::getline(pathStream, value);
                m_logger->info("StorageCacheLinearFile::get() found key={}", key);
                return std::make_pair(key, value);
            }
            else   // Key not found, skip next value and empty line
            {
                skipLines = 2;
            }
            continue;
        }
    }
    m_logger->error("StorageCacheLinearFile::get() failed for key={}", key);
    throw std::runtime_error("Didn't find element with key: " + key);
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