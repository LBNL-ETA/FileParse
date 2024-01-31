#pragma once

#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace Helper
{
    template<typename T>
    void
      checkVectorValues(const std::vector<T> & correct, const std::vector<T> & values, T tolerance)
    {
        ASSERT_EQ(correct.size(), values.size()) << "Vectors have different sizes: expected "
                                                 << correct.size() << ", but got " << values.size();

        for(size_t i = 0u; i < correct.size(); ++i)
        {
            std::ostringstream message;
            message << "At index " << i << ": expected " << correct[i] << ", but got " << values[i]
                    << " with tolerance " << tolerance;
            EXPECT_NEAR(correct[i], values[i], tolerance) << message.str();
        }
    }

    template<typename T>
    typename std::enable_if<!std::is_enum<T>::value, void>::type
      checkVectorEquality(const std::vector<T> & expected, const std::vector<T> & actual)
    {
        ASSERT_EQ(expected.size(), actual.size())
          << "Vectors have different sizes: expected " << expected.size() << ", but got "
          << actual.size();

        for(size_t i = 0u; i < expected.size(); ++i)
        {
            EXPECT_EQ(expected[i], actual[i])
              << "At index " << i << ": expected " << expected[i] << ", but got " << actual[i];
        }
    }

    template<typename T>
    typename std::enable_if<std::is_enum<T>::value, void>::type
      checkVectorEquality(const std::vector<T> & expected, const std::vector<T> & actual)
    {
        ASSERT_EQ(expected.size(), actual.size())
          << "Vectors have different sizes: expected " << expected.size() << ", but got "
          << actual.size();

        for(size_t i = 0u; i < expected.size(); ++i)
        {
            // Using static_cast to convert enum to its underlying type for comparison
            ASSERT_EQ(static_cast<typename std::underlying_type<T>::type>(expected[i]),
                      static_cast<typename std::underlying_type<T>::type>(actual[i]))
              << "At index " << i << ": expected "
              << static_cast<typename std::underlying_type<T>::type>(expected[i]) << ", but got "
              << static_cast<typename std::underlying_type<T>::type>(actual[i]);
        }
    }

    template<typename T, typename ConverterFunction>
    void checkVectorEquality(const std::vector<T> & expected,
                             const std::vector<T> & actual,
                             ConverterFunction converter)
    {
        ASSERT_EQ(expected.size(), actual.size())
          << "Vectors have different sizes: expected " << expected.size() << ", but got "
          << actual.size();

        for(size_t i = 0u; i < expected.size(); ++i)
        {
            EXPECT_EQ(expected[i], actual[i])
              << "At index " << i << ": expected " << converter(expected[i]) << ", but got "
              << converter(actual[i]);
        }
    }

    template<typename T>
    void checkSetValues(const std::set<T> & correct, const std::set<T> & values, T tolerance)
    {
        ASSERT_EQ(correct.size(), values.size()) << "Sets have different sizes: expected "
                                                 << correct.size() << ", but got " << values.size();

        auto correctIt = correct.begin();
        auto valuesIt = values.begin();

        for(size_t i = 0u; correctIt != correct.end() && valuesIt != values.end();
            ++correctIt, ++valuesIt, ++i)
        {
            std::ostringstream message;
            message << "At position " << i << ": expected " << *correctIt << ", but got "
                    << *valuesIt << " with tolerance " << tolerance;
            EXPECT_NEAR(*correctIt, *valuesIt, tolerance) << message.str();
        }
    }

    template<typename T, typename ConverterFunction>
    void checkSetEquality(const std::set<T> & expected,
                          const std::set<T> & actual,
                          ConverterFunction converter)
    {
        ASSERT_EQ(expected.size(), actual.size())
          << "Sets have different sizes: expected " << expected.size() << ", but got "
          << actual.size();

        auto expectedIt = expected.begin();
        auto actualIt = actual.begin();
        size_t i = 0;

        while(expectedIt != expected.end() && actualIt != actual.end())
        {
            EXPECT_EQ(*expectedIt, *actualIt)
              << "At position " << i << ": expected " << converter(*expectedIt) << ", but got "
              << converter(*actualIt);
            ++expectedIt;
            ++actualIt;
            ++i;
        }
    }

    template<typename T>
    struct is_valid_map : std::false_type
    {};

    template<typename K, typename V>
    struct is_valid_map<std::map<K, V>> : std::true_type
    {};

    template<typename K, typename V>
    struct is_valid_map<std::unordered_map<K, V>> : std::true_type
    {};

    template<typename MapType>
    std::enable_if_t<is_valid_map<MapType>::value> checkMapEquality(const MapType & expected,
                                                                    const MapType & actual)
    {
        ASSERT_EQ(expected.size(), actual.size());

        for(const auto & [expectedKey, expectedValue] : expected)
        {
            auto actualIter = actual.find(expectedKey);
            ASSERT_NE(actualIter, actual.end());

            EXPECT_EQ(expectedValue, actualIter->second);
        }
    }

    template<typename MapType, typename ValueType>
    std::enable_if_t<is_valid_map<MapType>::value>
      checkMapValues(const MapType & expected, const MapType & actual, ValueType tolerance)
    {
        ASSERT_EQ(expected.size(), actual.size());

        for(const auto & [expectedKey, expectedValue] : expected)
        {
            auto actualIter = actual.find(expectedKey);
            ASSERT_NE(actualIter, actual.end());
            EXPECT_NEAR(expectedValue, actualIter->second, tolerance);
        }
    }


}   // namespace Helper
