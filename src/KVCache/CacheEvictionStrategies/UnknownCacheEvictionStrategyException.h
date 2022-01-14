#pragma once
#include <exception>
#include <string>

namespace KVCache
{
    namespace Internal
    {
        namespace CacheEvictionsStrategies
        {
            class UnknownCacheEvictionStrategyException: public std::exception
            {
                std::string m_errorMsg;

              public:
                UnknownCacheEvictionStrategyException(const std::string& msg)
                    : m_errorMsg(msg)
                {}

                virtual const char* what() const noexcept override
                {
                    return m_errorMsg.c_str();
                }
            };
        }   // namespace CacheEvictionsStrategies
    }   // namespace Internal
}   // namespace KVCache