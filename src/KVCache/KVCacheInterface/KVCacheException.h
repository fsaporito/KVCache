#pragma once

#include <exception>
#include <string>

namespace KVCache
{
    namespace Interface
    {

        namespace Exceptions
        {

            class KVCacheException: public std::exception
            {

              private:
                std::string m_message;
                std::string m_location;
                int m_lineNumber;

              public:
                KVCacheException()
                    : m_message(""), m_location(""){};

                KVCacheException(const std::string& errorMessage,
                                 const std::string& errorLocation = "",
                                 const int lineNumber = -1)
                    : m_message(errorMessage), m_location(errorLocation), m_lineNumber(lineNumber){};

                ~KVCacheException() = default;

                inline virtual const char* what() const throw()
                {
                    return m_message.c_str();
                }

                inline std::string getMessage() const
                {
                    return m_message;
                }

                inline std::string getLocation() const
                {
                    return m_location;
                }

                inline int getLineNumber() const
                {
                    return m_lineNumber;
                }
            };

        }   // namespace Exceptions
    }   // namespace Interface
}   // namespace KVCache