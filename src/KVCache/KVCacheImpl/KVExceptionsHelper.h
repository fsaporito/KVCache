#pragma once

#include "../KVCacheInterface/KVCacheException.h"
#include <memory>
#include <spdlog/logger.h>


#define ThrowKVExceptionWithoutLogAndLoc(errorMsg) \
    throw KVCache::Interface::Exceptions::KVCacheException(errorMsg);

#define ThrowKVExceptionWithoutLog(errorMsg) \
    throw KVCache::Interface::Exceptions::KVCacheException(errorMsg, __FILE__, __LINE__);

#define ThrowKVExceptionWithLog(errorMsg, logger) \
    logger.error(errorMsg);                       \
    ThrowKVExceptionWithLog(errorMsg);

namespace KVCache
{
    namespace Internal
    {
        namespace Exceptions
        {

            inline void kvCacheExceptionHandler(const std::shared_ptr<spdlog::logger> logger,
                                                const std::string& location,
                                                const int lineNumber)
            {

                // Define log messages partial strings
                std::string exceptionTypeStr;
                std::string exceptionMessage;
                int effectiveLineNumber = lineNumber;
                std::string exceptionLocation;
                if (!exceptionLocation.empty())
                {
                    exceptionLocation = "@" + location;
                }

                // Rethrow last thrown exception
                try
                {
                    throw;
                }
                catch (const std::runtime_error& e)
                {
                    exceptionTypeStr = "std::runtime_error";
                    exceptionMessage = e.what();
                }
                catch (KVCache::Interface::Exceptions::KVCacheException& e)
                {
                    exceptionTypeStr = "KVCacheException";
                    exceptionLocation = e.getLocation();
                    exceptionMessage = e.getMessage();
                    if (!exceptionLocation.empty())
                    {
                        exceptionLocation = "@" + exceptionLocation;
                    }
                    effectiveLineNumber = e.getLineNumber();
                }
                catch (const std::exception& e)
                {
                    exceptionTypeStr = "std::exception";
                    exceptionMessage = e.what();
                }
                catch (...)
                {
                    exceptionTypeStr = "Unknown Exception";
                    exceptionMessage = "Unknown Error";
                }

                // Build the logMessage
                std::string logErrorMsg = exceptionTypeStr;
                if (!exceptionLocation.empty())
                {
                    logErrorMsg += " " + exceptionLocation;
                }
                if (effectiveLineNumber >= 0)
                {
                    logErrorMsg += " at line " + std::to_string(effectiveLineNumber);
                }

                // Log and Throw
                if (logger)
                {
                    logger->error(logErrorMsg);
                }
                ThrowKVExceptionWithoutLogAndLoc(exceptionMessage);
            }

            inline void kvCacheExceptionHandler(const std::shared_ptr<spdlog::logger> logger)
            {
                kvCacheExceptionHandler(logger, "", -1);
            }

            inline void kvCacheExceptionHandler()
            {
                kvCacheExceptionHandler(std::shared_ptr<spdlog::logger>(nullptr), "", -1);
            }


            template<typename Callable, typename... Args>
            inline auto kvCacheCallableExecutor(Callable&& functionCallable,
                                                const std::shared_ptr<spdlog::logger>
                                                    logger,
                                                const std::string& location,
                                                const int lineNumber,
                                                Args&&... args)
                -> decltype(functionCallable())
            {
                // Try to execute the callable
                try
                {
                    return std::forward<Callable>(functionCallable)(std::forward<Args>(args)...);
                }
                catch (...)
                {
                    kvCacheExceptionHandler(logger, location, lineNumber);
                }
            }

        }   // namespace Exceptions

    }   // namespace Internal

}   // namespace KVCache