#pragma once

#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace Helper
{
    template<typename T>
    void checkVectorValues(const std::vector<T> & correct, const std::vector<T> & values, T tolerance)
    {
        ASSERT_EQ(correct.size(), values.size())
          << "Vectors have different sizes: expected " << correct.size() << ", but got " << values.size();

        for(size_t i = 0u; i < correct.size(); ++i)
        {
            std::ostringstream message;
            message << "At index " << i << ": expected " << correct[i] << ", but got " << values[i]
                    << " with tolerance " << tolerance;
            EXPECT_NEAR(correct[i], values[i], tolerance) << message.str();
        }
    }

    template<typename T>
    void checkSetValues(const std::set<T> & correct, const std::set<T> & values, T tolerance)
    {
        ASSERT_EQ(correct.size(), values.size())
          << "Sets have different sizes: expected " << correct.size() << ", but got " << values.size();

        auto correctIt = correct.begin();
        auto valuesIt = values.begin();

        for(size_t i = 0u; correctIt != correct.end() && valuesIt != values.end(); ++correctIt, ++valuesIt, ++i)
        {
            std::ostringstream message;
            message << "At position " << i << ": expected " << *correctIt << ", but got " << *valuesIt
                    << " with tolerance " << tolerance;
            EXPECT_NEAR(*correctIt, *valuesIt, tolerance) << message.str();
        }
    }

}   // namespace Helper
