#pragma once
#include "KVOptionalParameters.h"
#include <memory>
#include <string>
#include <utility>


namespace KVCache
{
    namespace Interface
    {
        class KVCacheAbstract
        {
          public:
            static std::unique_ptr<KVCacheAbstract> createKVCache();
            static std::unique_ptr<KVCacheAbstract> createKVCache(const Interface::KVOptionalParameters& optionalParams);

            virtual ~KVCacheAbstract() = default;
            KVCacheAbstract(const KVCacheAbstract&) = delete;
            KVCacheAbstract& operator=(KVCacheAbstract const&) = delete;

            virtual void put(const std::string& key, const std::string& value) = 0;
            virtual void remove(const std::string& key) = 0;
            virtual std::pair<std::string, std::string> get(const std::string& key) const = 0;

          protected:
            KVCacheAbstract() = default;
        };

    }   // namespace Interface
}   // namespace KVCache