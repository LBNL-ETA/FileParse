#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <optional>

#include "XMLNodeAdapter.hxx"

namespace Common
{
    namespace
    {
        void createFileFromString(std::string_view fileName, std::string_view fileContent)
        {
            std::ofstream out(fileName.data());
            out << fileContent;
            out.close();
        }
    }   // namespace

    template<typename T>
    std::optional<T> loadFromXMLString(const std::string & data, const std::string & nodeTypeName)
    {
        // Attempt to load the top node for the given type
        const auto xmlNode = getTopNodeFromString(data, nodeTypeName);

        // Create an instance of the type
        if(xmlNode.has_value())
        {
            T model;
            // Assume that `operator>>` is overloaded for T and xmlNode type
            xmlNode.value() >> model;
            return model;
        }

        return std::nullopt;
    }

    template<typename T>
    std::optional<T> loadFromXMLFile(std::string_view fileName, const std::string & nodeTypeName)
    {
        // Convert std::string_view to std::string for file operations
        std::string fileNameStr(fileName);

        // Check if file exists and is accessible; if not, create it with default content
        if(std::ifstream f(fileNameStr.c_str()); !f.good())
        {
            const std::string fileContent = "<" + nodeTypeName + ">\n</" + nodeTypeName + ">";
            createFileFromString(fileNameStr, fileContent);
        }

        // Attempt to load the top node for the given type
        const auto xmlNode = getTopNodeFromFile(fileNameStr, nodeTypeName);


        if(xmlNode.has_value())
        {
            T model;
            // Assume that `operator>>` is overloaded for T and xmlNode type
            xmlNode.value() >> model;
            return model;
        }

        return std::nullopt;
    }

    template<typename T>
    int saveToXMLFile(const T & object, std::string_view fileName, const std::string & nodeName)

    {
        auto node = createTopNode(nodeName);

        node << object;

        return node.writeToFile(fileName.data());
    }

    template<typename T>
    std::string saveToXMLString(const T & object, const std::string & nodeName)
    {
        auto node = createTopNode(nodeName);

        node << object;

        return node.getContent();
    }
}   // namespace Common