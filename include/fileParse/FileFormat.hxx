/// @file FileFormat.hxx
/// @brief Provides file format detection utilities for automatic XML/JSON handling.

#pragma once

#include <string>
#include <string_view>
#include <algorithm>
#include <fstream>
#include <cctype>

namespace FileParse
{
    /// Supported file formats for serialization.
    enum class FileFormat
    {
        Unknown,   ///< Format could not be determined
        XML,       ///< XML format
        JSON       ///< JSON format
    };

    namespace Detail
    {
        /// Converts a string to lowercase.
        /// @param str The string to convert.
        /// @return The lowercase version of the string.
        inline std::string toLower(std::string_view str)
        {
            std::string result(str);
            std::transform(result.begin(), result.end(), result.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            return result;
        }

        /// Checks if a string ends with a given suffix (case-insensitive).
        /// @param str The string to check.
        /// @param suffix The suffix to look for.
        /// @return True if str ends with suffix.
        inline bool endsWithIgnoreCase(std::string_view str, std::string_view suffix)
        {
            if(suffix.size() > str.size())
            {
                return false;
            }
            auto strEnd = toLower(str.substr(str.size() - suffix.size()));
            auto suffixLower = toLower(suffix);
            return strEnd == suffixLower;
        }
    }   // namespace Detail

    /// Detects file format based on file extension.
    /// @param fileName The filename to analyze.
    /// @return The detected FileFormat, or FileFormat::Unknown if extension is not recognized.
    /// @note This function only examines the file extension, not the file contents.
    ///       Recognized extensions: .xml, .json (case-insensitive)
    inline FileFormat detectFileFormatFromExtension(std::string_view fileName)
    {
        if(Detail::endsWithIgnoreCase(fileName, ".json"))
        {
            return FileFormat::JSON;
        }
        if(Detail::endsWithIgnoreCase(fileName, ".xml"))
        {
            return FileFormat::XML;
        }
        return FileFormat::Unknown;
    }

    /// Detects file format by inspecting file contents.
    /// @param fileName The path to the file to analyze.
    /// @return The detected FileFormat, or FileFormat::Unknown if format cannot be determined.
    /// @note This function reads the beginning of the file and looks for:
    ///       - '{' as first non-whitespace character → JSON
    ///       - '<' as first non-whitespace character → XML
    inline FileFormat detectFileFormatFromContent(std::string_view fileName)
    {
        std::string fileNameStr(fileName);
        std::ifstream file(fileNameStr);
        if(!file.good())
        {
            return FileFormat::Unknown;
        }

        char ch;
        while(file.get(ch))
        {
            if(std::isspace(static_cast<unsigned char>(ch)))
            {
                continue;
            }
            if(ch == '{')
            {
                return FileFormat::JSON;
            }
            if(ch == '<')
            {
                return FileFormat::XML;
            }
            break;
        }
        return FileFormat::Unknown;
    }

    /// Detects file format by inspecting string contents.
    /// @param content The string content to analyze.
    /// @return The detected FileFormat, or FileFormat::Unknown if format cannot be determined.
    /// @note This function looks for:
    ///       - '{' as first non-whitespace character → JSON
    ///       - '<' as first non-whitespace character → XML
    inline FileFormat detectFormatFromStringContent(std::string_view content)
    {
        for(char ch : content)
        {
            if(std::isspace(static_cast<unsigned char>(ch)))
            {
                continue;
            }
            if(ch == '{')
            {
                return FileFormat::JSON;
            }
            if(ch == '<')
            {
                return FileFormat::XML;
            }
            break;
        }
        return FileFormat::Unknown;
    }

    /// Detects file format using extension first, then content as fallback.
    /// @param fileName The path to the file to analyze.
    /// @return The detected FileFormat, or FileFormat::Unknown if format cannot be determined.
    /// @note This function first checks the file extension. If the extension is not
    ///       recognized (.json or .xml), it falls back to inspecting the file contents.
    inline FileFormat detectFileFormat(std::string_view fileName)
    {
        auto format = detectFileFormatFromExtension(fileName);
        if(format != FileFormat::Unknown)
        {
            return format;
        }
        return detectFileFormatFromContent(fileName);
    }
}   // namespace FileParse
