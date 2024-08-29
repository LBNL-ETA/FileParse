/// File: Attributes.hxx
/// @brief Provides functionality to serialize and deserialize properties
/// as attributes (only available in XML).

#pragma once

#include <string>
#include <functional>
#include <optional>

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

    // Generic saveAttribute for basic types, excluding std::string
    template<typename NodeAdapter,
             typename T,
             typename std::
               enable_if<is_basic_type<T>::value && !std::is_same<T, std::string>::value, int>::type
             = 0>
    void saveAttribute(NodeAdapter & node, const std::string & name, const T & value)
    {
        node.addAttribute(name, std::to_string(value));
    }

    // Specialization for std::string
    template<typename NodeAdapter>
    void saveAttribute(NodeAdapter & node, const std::string & name, const std::string & value)
    {
        node.addAttribute(name, value);
    }

    // Generic loadAttribute for basic types, excluding std::string
    template<typename NodeAdapter,
             typename T,
             typename std::
               enable_if<is_basic_type<T>::value && !std::is_same<T, std::string>::value, int>::type
             = 0>
    void loadAttribute(const NodeAdapter & node, const std::string & name, T & attribute)
    {
        auto stringValue = node.getAttribute(name);

        if(stringValue.has_value())
        {
            attribute = FileParse::from_string<T>(stringValue.value());
        }
    }

    // Specialization for std::string
    template<typename NodeAdapter>
    void loadAttribute(const NodeAdapter & node, const std::string & name, std::string & attribute)
    {
        auto value = node.getAttribute(name);
        if(value.has_value())
            attribute = value.value();
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
    void loadAttribute(const NodeAdapter & node,
                       const std::string & name,
                       T & attribute,
                       const std::function<T(std::string_view)> & stringToEnum)
    {
        auto value = node.getAttribute(name);
        if(value.has_value())
            attribute = stringToEnum(value.value());
    }
}   // namespace FileParse