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
    /// Type trait to check if a type is a basic serializable type.
    /// @tparam T The type to check.
    template<typename T>
    struct is_basic_type : std::false_type
    {};

    /// Specialization of is_basic_type for int.
    template<>
    struct is_basic_type<int> : std::true_type
    {};

    /// Specialization of is_basic_type for double.
    template<>
    struct is_basic_type<double> : std::true_type
    {};

    /// Specialization of is_basic_type for float.
    template<>
    struct is_basic_type<float> : std::true_type
    {};

    /// Specialization of is_basic_type for size_t.
    template<>
    struct is_basic_type<size_t> : std::true_type
    {};

    /// Specialization of is_basic_type for std::string.
    template<>
    struct is_basic_type<std::string> : std::true_type
    {};

    /// Saves a basic type value as an XML attribute.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the value (must be a basic type, excluding std::string).
    /// @param node The node to add the attribute to.
    /// @param name The attribute name.
    /// @param value The value to save.
    template<typename NodeAdapter,
             typename T,
             typename std::
               enable_if<is_basic_type<T>::value && !std::is_same<T, std::string>::value, int>::type
             = 0>
    void saveAttribute(NodeAdapter & node, const std::string & name, const T & value)
    {
        node.addAttribute(name, std::to_string(value));
    }

    /// Saves a string value as an XML attribute.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @param node The node to add the attribute to.
    /// @param name The attribute name.
    /// @param value The string value to save.
    template<typename NodeAdapter>
    void saveAttribute(NodeAdapter & node, const std::string & name, const std::string & value)
    {
        node.addAttribute(name, value);
    }

    /// Loads a basic type value from an XML attribute.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the value (must be a basic type, excluding std::string).
    /// @param node The node to read the attribute from.
    /// @param name The attribute name.
    /// @param attribute The variable to store the loaded value.
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

    /// Loads a string value from an XML attribute.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @param node The node to read the attribute from.
    /// @param name The attribute name.
    /// @param attribute The variable to store the loaded string.
    template<typename NodeAdapter>
    void loadAttribute(const NodeAdapter & node, const std::string & name, std::string & attribute)
    {
        auto value = node.getAttribute(name);
        if(value.has_value())
            attribute = value.value();
    }

    /// Type trait to check if a type is an enumeration.
    /// @tparam T The type to check.
    template<typename T>
    struct is_enum_type : std::is_enum<T>
    {};

    /// Saves an enumeration value as an XML attribute using a converter function.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The enumeration type.
    /// @param node The node to add the attribute to.
    /// @param name The attribute name.
    /// @param value The enumeration value to save.
    /// @param enumToString Function to convert the enum to its string representation.
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

    /// Loads an enumeration value from an XML attribute using a converter function.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The enumeration type.
    /// @param node The node to read the attribute from.
    /// @param name The attribute name.
    /// @param attribute The variable to store the loaded enum value.
    /// @param stringToEnum Function to convert a string to its enum representation.
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

    //////////////////////////////////////////////////////////////////
    // Optional value attribute handlers
    //////////////////////////////////////////////////////////////////

    /// Saves an optional basic type value as an XML attribute.
    /// If the optional is empty, no attribute is written.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the value (must be a basic type, excluding std::string).
    /// @param node The node to add the attribute to.
    /// @param name The attribute name.
    /// @param value The optional value to save.
    template<typename NodeAdapter,
             typename T,
             typename std::
               enable_if<is_basic_type<T>::value && !std::is_same<T, std::string>::value, int>::type
             = 0>
    void saveAttribute(NodeAdapter & node, const std::string & name, const std::optional<T> & value)
    {
        if(value.has_value())
        {
            node.addAttribute(name, std::to_string(value.value()));
        }
    }

    /// Saves an optional string value as an XML attribute.
    /// If the optional is empty, no attribute is written.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @param node The node to add the attribute to.
    /// @param name The attribute name.
    /// @param value The optional string value to save.
    template<typename NodeAdapter>
    void saveAttribute(NodeAdapter & node,
                       const std::string & name,
                       const std::optional<std::string> & value)
    {
        if(value.has_value())
        {
            node.addAttribute(name, value.value());
        }
    }

    /// Saves an optional enumeration value as an XML attribute using a converter function.
    /// If the optional is empty, no attribute is written.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The enumeration type.
    /// @param node The node to add the attribute to.
    /// @param name The attribute name.
    /// @param value The optional enumeration value to save.
    /// @param enumToString Function to convert the enum to its string representation.
    template<typename NodeAdapter,
             typename T,
             typename std::enable_if<is_enum_type<T>::value, int>::type = 0>
    void saveAttribute(NodeAdapter & node,
                       const std::string & name,
                       const std::optional<T> & value,
                       const std::function<std::string(T)> & enumToString)
    {
        if(value.has_value())
        {
            node.addAttribute(name, enumToString(value.value()));
        }
    }

    /// Loads an optional basic type value from an XML attribute.
    /// If the attribute doesn't exist, the optional remains unchanged.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The type of the value (must be a basic type, excluding std::string).
    /// @param node The node to read the attribute from.
    /// @param name The attribute name.
    /// @param attribute The optional variable to store the loaded value.
    template<typename NodeAdapter,
             typename T,
             typename std::
               enable_if<is_basic_type<T>::value && !std::is_same<T, std::string>::value, int>::type
             = 0>
    void loadAttribute(const NodeAdapter & node,
                       const std::string & name,
                       std::optional<T> & attribute)
    {
        auto stringValue = node.getAttribute(name);
        if(stringValue.has_value())
        {
            attribute = FileParse::from_string<T>(stringValue.value());
        }
    }

    /// Loads an optional string value from an XML attribute.
    /// If the attribute doesn't exist, the optional remains unchanged.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @param node The node to read the attribute from.
    /// @param name The attribute name.
    /// @param attribute The optional variable to store the loaded string.
    template<typename NodeAdapter>
    void loadAttribute(const NodeAdapter & node,
                       const std::string & name,
                       std::optional<std::string> & attribute)
    {
        auto value = node.getAttribute(name);
        if(value.has_value())
        {
            attribute = value.value();
        }
    }

    /// Loads an optional enumeration value from an XML attribute using a converter function.
    /// If the attribute doesn't exist, the optional remains unchanged.
    /// @tparam NodeAdapter The type of the node adapter.
    /// @tparam T The enumeration type.
    /// @param node The node to read the attribute from.
    /// @param name The attribute name.
    /// @param attribute The optional variable to store the loaded enum value.
    /// @param stringToEnum Function to convert a string to its enum representation.
    template<typename NodeAdapter,
             typename T,
             typename std::enable_if<is_enum_type<T>::value, int>::type = 0>
    void loadAttribute(const NodeAdapter & node,
                       const std::string & name,
                       std::optional<T> & attribute,
                       const std::function<T(std::string_view)> & stringToEnum)
    {
        auto value = node.getAttribute(name);
        if(value.has_value())
        {
            attribute = stringToEnum(value.value());
        }
    }
}   // namespace FileParse