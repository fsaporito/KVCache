#pragma once
#include <exception>
#include <string>

namespace KVCache
{
    namespace Internal
    {
        namespace StorageCache
        {
            class UnknownStorageCacheTypeException: public std::exception
            {
                std::string m_errorMsg;

              public:
                UnknownStorageCacheTypeException(const std::string& msg)
                    : m_errorMsg(msg)
                {}

                virtual const char* what() const noexcept override
                {
                    return m_errorMsg.c_str();
                }
            };
        }
    }
}