#pragma once

#include <gtest/gtest.h>
#include <vector>
#include <sstream>

namespace Helper
{
    template<typename T>
    void checkVectorValues(const std::vector<T> & correct, const std::vector<T> & values, T tolerance)
    {
        ASSERT_EQ(correct.size(), values.size());

        for(size_t i = 0u; i < correct.size(); ++i)
        {
            EXPECT_NEAR(correct[i], values[i], tolerance);
        }
    }
}   // namespace Helper
