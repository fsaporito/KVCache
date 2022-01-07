#pragma once
#include "../KVCacheInterface/KVCacheAbstract.h"
#include <memory>

namespace KVCache
{
    namespace Internal
    {

        class KVCacheImpl: public Interface::KVCacheAbstract
        {
          public:
            KVCacheImpl();
            KVCacheImpl(const Interface::KVOptionalParameters& optionalParams);
            virtual ~KVCacheImpl() = default;
            KVCacheImpl(const KVCacheImpl&) = delete;
            KVCacheImpl& operator=(KVCacheImpl const&) = delete;

            void put(const std::string& key, const std::string& value) override;
            void remove(const std::string& key) override;
            std::pair<std::string, std::string> get(const std::string& key) const override;

          protected:
            void setupKVCache(const Interface::KVOptionalParameters& optionalParams);
        };
    }   // namespace Internal
}   // namespace KVCache