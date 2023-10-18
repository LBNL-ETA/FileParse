#pragma once

#include <string>

namespace FileParse
{
    template<typename T>
    inline T from_string(const std::string & str);

    // Specialization for int
    template<>
    inline int from_string<int>(const std::string & str)
    {
        return std::stoi(str);
    }

    // Specialization for double
    template<>
    inline double from_string<double>(const std::string & str)
    {
        return std::stod(str);
    }

    // Specialization for size_t
    template<>
    inline size_t from_string<size_t>(const std::string & str)
    {
        return std::stoul(str);
    }

    // Specialization for std::string
    template<>
    inline std::string from_string<std::string>(const std::string & str)
    {
        return str;
    }


    template<typename T>
    T from_string_helper(const std::string & str)
    {
        return from_string<T>(str);
    }
}   // namespace FileParse