#pragma once
#include <exception>
#include <string>

namespace KVCache
{
    namespace Internal
    {
        namespace MemoryCache
        {
            class UnknownMemCacheTypeException: public std::exception
            {
                std::string m_errorMsg;

              public:
                UnknownMemCacheTypeException(const std::string& msg)
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