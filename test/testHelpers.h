#pragma once
#include <string>
#include <utility>
#include <vector>

namespace TestHelper
{

    inline std::string generateLongValueOfGivenSize(size_t size = 10.000, char value = '0')
    {
        std::string valueStr;
        valueStr.reserve(size);
        for (size_t i = 0; i < 10000; i++)
        {
            valueStr.push_back(value);
        }
        return valueStr;
    };

    inline std::pair<std::vector<std::string>, std::vector<std::string>> generateKVPairs(const size_t sampleNum,
                                                                                         const std::string& keyBaseContent = "Key",
                                                                                         const std::string& valueBaseContent = "Value")
    {
        std::vector<std::string> keys;
        keys.reserve(sampleNum);
        std::vector<std::string> values;
        values.reserve(sampleNum);

        for (size_t i = 0; i < sampleNum; i++)
        {
            keys.push_back(keyBaseContent + std::to_string(i));
            values.push_back(valueBaseContent + std::to_string(i));
        }

        return std::make_pair(keys, values);
    };
}   // namespace TestHelper
