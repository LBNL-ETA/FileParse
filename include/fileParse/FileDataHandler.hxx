/// File: FileDataHandler.hxx
/// @brief Provides high-level functions for loading and saving data structures
///        to/from XML and JSON files or strings.

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <optional>

#include "XMLNodeAdapter.hxx"
#include "JSONNodeAdapter.hxx"
#include "FileFormat.hxx"

namespace Common
{
    namespace
    {
        /// Creates a file with the specified content.
        /// @param fileName The name of the file to create.
        /// @param fileContent The content to write to the file.
        void createFileFromString(std::string_view fileName, std::string_view fileContent)
        {
            std::ofstream out(fileName.data());
            out << fileContent;
            out.close();
        }
    }   // namespace

    //////////////////////////////////////////////////////////////////////////
    // XML Functions
    //////////////////////////////////////////////////////////////////////////

    /// Deserializes an object from an XML string.
    /// @tparam T The type of object to deserialize (must have operator>> defined).
    /// @param data The XML string to parse.
    /// @param nodeTypeName The name of the root XML element.
    /// @return An optional containing the deserialized object, or std::nullopt on failure.
    template<typename T>
    std::optional<T> loadFromXMLString(const std::string & data, const std::string & nodeTypeName)
    {
        const auto xmlNode = getTopNodeFromString(data, nodeTypeName);

        if(xmlNode.has_value())
        {
            T model;
            xmlNode.value() >> model;
            return model;
        }

        return std::nullopt;
    }

    /// Deserializes an object from an XML file.
    /// If the file doesn't exist, creates an empty XML file with the specified root element.
    /// @tparam T The type of object to deserialize (must have operator>> defined).
    /// @param fileName The path to the XML file.
    /// @param nodeTypeName The name of the root XML element.
    /// @return An optional containing the deserialized object, or std::nullopt on failure.
    template<typename T>
    std::optional<T> loadFromXMLFile(std::string_view fileName, const std::string & nodeTypeName)
    {
        std::string fileNameStr(fileName);

        if(std::ifstream f(fileNameStr.c_str()); !f.good())
        {
            const std::string fileContent = "<" + nodeTypeName + ">\n</" + nodeTypeName + ">";
            createFileFromString(fileNameStr, fileContent);
        }

        const auto xmlNode = getTopNodeFromFile(fileNameStr, nodeTypeName);


        if(xmlNode.has_value())
        {
            T model;
            xmlNode.value() >> model;
            return model;
        }

        return std::nullopt;
    }

    /// Serializes an object to an XML file.
    /// @tparam T The type of object to serialize (must have operator<< defined).
    /// @param object The object to serialize.
    /// @param fileName The path to the output XML file.
    /// @param nodeName The name of the root XML element.
    /// @return 0 on success, non-zero on failure.
    template<typename T>
    int saveToXMLFile(const T & object, std::string_view fileName, const std::string & nodeName)
    {
        auto node = createTopNode(nodeName);

        node << object;

        return node.writeToFile(fileName.data());
    }

    /// Serializes an object to an XML string.
    /// @tparam T The type of object to serialize (must have operator<< defined).
    /// @param object The object to serialize.
    /// @param nodeName The name of the root XML element.
    /// @return The XML string representation of the object.
    template<typename T>
    std::string saveToXMLString(const T & object, const std::string & nodeName)
    {
        auto node = createTopNode(nodeName);

        node << object;

        return node.getContent();
    }

    //////////////////////////////////////////////////////////////////////////
    // JSON Functions
    //////////////////////////////////////////////////////////////////////////

    /// Deserializes an object from a JSON string.
    /// @tparam T The type of object to deserialize (must have operator>> defined).
    /// @param data The JSON string to parse.
    /// @param nodeTypeName The name of the root JSON property.
    /// @return An optional containing the deserialized object, or std::nullopt on failure.
    template<typename T>
    std::optional<T> loadFromJSONString(const std::string & data, const std::string & nodeTypeName)
    {
        const auto jsonNode = getJSONTopNodeFromString(data, nodeTypeName);

        if(jsonNode.has_value())
        {
            T model;
            jsonNode.value() >> model;
            return model;
        }

        return std::nullopt;
    }

    /// Deserializes an object from a JSON file.
    /// If the file doesn't exist, creates an empty JSON file with the specified root property.
    /// @tparam T The type of object to deserialize (must have operator>> defined).
    /// @param fileName The path to the JSON file.
    /// @param nodeTypeName The name of the root JSON property.
    /// @return An optional containing the deserialized object, or std::nullopt on failure.
    template<typename T>
    std::optional<T> loadFromJSONFile(std::string_view fileName, const std::string & nodeTypeName)
    {
        std::string fileNameStr(fileName);

        if(std::ifstream f(fileNameStr.c_str()); !f.good())
        {
            const std::string fileContent = "{\"" + nodeTypeName + "\": {}}";
            createFileFromString(fileNameStr, fileContent);
        }

        const auto jsonNode = getJSONTopNodeFromFile(fileNameStr, nodeTypeName);

        if(jsonNode.has_value())
        {
            T model;
            jsonNode.value() >> model;
            return model;
        }

        return std::nullopt;
    }

    /// Serializes an object to a JSON file.
    /// @tparam T The type of object to serialize (must have operator<< defined).
    /// @param object The object to serialize.
    /// @param fileName The path to the output JSON file.
    /// @param nodeName The name of the root JSON property.
    /// @return 0 on success, non-zero on failure.
    template<typename T>
    int saveToJSONFile(const T & object, std::string_view fileName, const std::string & nodeName)
    {
        auto node = createJSONTopNode(nodeName);

        node << object;

        return node.writeToFile(fileName.data());
    }

    /// Serializes an object to a JSON string.
    /// @tparam T The type of object to serialize (must have operator<< defined).
    /// @param object The object to serialize.
    /// @param nodeName The name of the root JSON property.
    /// @return The JSON string representation of the object.
    template<typename T>
    std::string saveToJSONString(const T & object, const std::string & nodeName)
    {
        auto node = createJSONTopNode(nodeName);

        node << object;

        return node.getContent();
    }

    //////////////////////////////////////////////////////////////////////////
    // Unified Functions (Auto-detect format)
    //////////////////////////////////////////////////////////////////////////

    /// Deserializes an object from a file, automatically detecting format.
    /// @tparam T The type of object to deserialize (must have operator>> defined).
    /// @param fileName The path to the file (format detected from extension, then content).
    /// @param nodeTypeName The name of the root element/property.
    /// @return An optional containing the deserialized object, or std::nullopt on failure.
    /// @note Uses detectFileFormat() to determine format. For files with non-standard
    ///       extensions, use loadFromXMLFile() or loadFromJSONFile() directly.
    template<typename T>
    std::optional<T> loadFromFile(std::string_view fileName, const std::string & nodeTypeName)
    {
        using namespace FileParse;

        switch(detectFileFormat(fileName))
        {
            case FileFormat::XML:
                return loadFromXMLFile<T>(fileName, nodeTypeName);
            case FileFormat::JSON:
                return loadFromJSONFile<T>(fileName, nodeTypeName);
            default:
                return std::nullopt;
        }
    }

    /// Serializes an object to a file, automatically detecting format from extension.
    /// @tparam T The type of object to serialize (must have operator<< defined).
    /// @param object The object to serialize.
    /// @param fileName The path to the output file (format detected from extension).
    /// @param nodeName The name of the root element/property.
    /// @return 0 on success, -1 if format cannot be determined, or other non-zero on write failure.
    /// @note Uses detectFileFormatFromExtension() to determine format. For files with
    ///       non-standard extensions, use saveToXMLFile() or saveToJSONFile() directly.
    template<typename T>
    int saveToFile(const T & object, std::string_view fileName, const std::string & nodeName)
    {
        using namespace FileParse;

        switch(detectFileFormatFromExtension(fileName))
        {
            case FileFormat::XML:
                return saveToXMLFile(object, fileName, nodeName);
            case FileFormat::JSON:
                return saveToJSONFile(object, fileName, nodeName);
            default:
                return -1;
        }
    }
}   // namespace Common