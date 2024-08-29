/// File: Attributes.hxx
/// @brief Provides functionality to serialize and deserialize properties
/// as attributes (only available in XML).

#pragma once

#include <string>
#include <functional>

#include "StringConversion.hxx"

namespace FileParse
{
    template<typename T>
    struct is_basic_type : std::false_type
    {};

    // Specializations for allowed types
    template<>
    struct is_basic_type<int> : std::true_type
    {};

    template<>
    struct is_basic_type<double> : std::true_type
    {};

    template<>
    struct is_basic_type<float> : std::true_type
    {};

    template<>
    struct is_basic_type<size_t> : std::true_type
    {};

    template<>
    struct is_basic_type<std::string> : std::true_type
    {};

    template<typename NodeAdapter,
             typename T,
             typename std::enable_if<is_basic_type<T>::value, int>::type = 0>
    void saveAttribute(NodeAdapter & node, const std::string & name, const T & value)
    {
        node.addAttribute(name, std::to_string(value));
    }

    template<typename NodeAdapter,
             typename T,
             typename std::enable_if<is_basic_type<T>::value, int>::type = 0>
    T loadAttribute(const NodeAdapter & node, const std::string & name)
    {
        return FileParse::from_string<T>(node.getAttribute(name));
    }

    // Traits to check if a type is an enumeration
    template<typename T>
    struct is_enum_type : std::is_enum<T>
    {};

    // Save attribute for enumerations with custom conversion functions
    template<typename NodeAdapter,
             typename T,
             typename std::enable_if<is_enum_type<T>::value, int>::type = 0>
    void saveAttribute(NodeAdapter & node,
                       const std::string & name,
                       const T & value,
                       const std::function<std::string(T)> & enumToString)
    {
        node.addAttribute(name, enumToString(value));
    }

    // Load attribute for enumerations with custom conversion functions
    template<typename NodeAdapter,
             typename T,
             typename std::enable_if<is_enum_type<T>::value, int>::type = 0>
    T loadAttribute(const NodeAdapter & node,
                    const std::string & name,
                    const std::function<T(const std::string &)> & stringToEnum)
    {
        return stringToEnum(node.getAttribute(name));
    }
}   // namespace FileParse