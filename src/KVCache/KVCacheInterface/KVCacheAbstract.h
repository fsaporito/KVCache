#pragma once
#include "KVOptionalParameters.h"
#include <memory>
#include <string>
#include <utility>


namespace KVCache
{
    namespace Interface
    {
        /*!
         *  This class gives a virtual interface for a Key-Value Cache.
         */
        class KVCacheAbstract
        {
          public:

            /*! Virtual Destructor for the Object */
            virtual ~KVCacheAbstract() = default;

            /*! The KV Object is not copyable: Copy Constructor is Deleted */
            KVCacheAbstract(const KVCacheAbstract&) = delete;

            /*! The KV Object is not copyable: Assignment Operator is Deleted */
            KVCacheAbstract& operator=(KVCacheAbstract const&) = delete;

            /*! This method is used to create the KVCache with default parameters*/
            static std::unique_ptr<KVCacheAbstract> createKVCache();

            /*! This method is used to create the KVCache with custom parameters*/
            static std::unique_ptr<KVCacheAbstract> createKVCache(const Interface::KVOptionalParameters& optionalParams);

            /*! This method is used to put a KV pair in the Cache */
            virtual void put(const std::string& key, const std::string& value) = 0;

            /*! This method is used to remove a KV pair in the Cache given the Key */
            virtual void remove(const std::string& key) = 0;

            /*! This method is used to get a Value from the cache given the corrensponding Key */
            virtual std::pair<std::string, std::string> get(const std::string& key) const = 0;

          protected:
            /*! Default Constructor is Protected */
            KVCacheAbstract() = default;
        };

    }   // namespace Interface
}   // namespace KVCache