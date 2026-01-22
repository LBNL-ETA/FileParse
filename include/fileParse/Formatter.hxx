/// File: Formatter.hxx
/// @brief Provides formatting utilities for converting numeric values to strings
///        with configurable precision and scientific notation bounds.

#pragma once

#include <string>

namespace FileParse
{
    /// Formats a double value as a string with configurable precision and scientific notation.
    /// @param value The double value to format.
    /// @param precision The number of significant digits to use.
    /// @param scientificLowerBound Values below this threshold use scientific notation.
    /// @param scientificUpperBound Values above this threshold use scientific notation.
    /// @return The formatted string representation of the value.
    extern std::string formatDouble(double value,
                                    int precision,
                                    double scientificLowerBound = 0.001,
                                    double scientificUpperBound = 100000);
}