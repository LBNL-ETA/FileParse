#pragma once

#include "test/helper/structures/CMAValues.hxx"

namespace Helper
{
    inline void compareCMAValues(const Helper::CMAValues & expected,
                           const Helper::CMAValues & actual,
                           double tolerance)
    {
        EXPECT_NEAR(expected.conductivity, actual.conductivity, tolerance);
        EXPECT_NEAR(expected.filmCoefficient, actual.filmCoefficient, tolerance);
    }


    template<typename MapType>
    inline void checkCMAValuesMap(const MapType & expected, const MapType & actual, double tolerance)
    {
        static_assert(Helper::is_valid_map<MapType>::value,
                      "MapType must be a map or unordered_map");

        ASSERT_EQ(expected.size(), actual.size());

        for(const auto & [expectedKey, expectedValue] : expected)
        {
            auto actualIter = actual.find(expectedKey);
            ASSERT_NE(actualIter, actual.end());
            const auto & actualValue = actualIter->second;

            compareCMAValues(expectedValue, actualValue, tolerance);
        }
    }
}   // namespace Helper