#include "FileManipulation.hxx"

#include <fstream>
#include <sstream>
#include <set>

namespace File
{
    void createFileFromString(std::string_view fileName, std::string_view fileContent)
    {
        std::ofstream out(fileName.data());
        out << fileContent.data();
        out.close();
    }

    std::string loadToString(std::string_view fileName)
    {
        std::ifstream in{fileName.data()};
        std::string result;
        std::string line;
        while (std::getline(in, line))
        {
            result += line + "\n";
        }
        in.close();
        return result;
    }

    std::set<std::string> loadFileToSet(std::string_view fileName)
    {
        std::set<std::string> result;
        std::ifstream in{fileName.data()};
        std::string line;

        // Extract each column name
        while (std::getline(in, line))
        {
            result.insert(line);
        }
        in.close();
        return result;
    }

    void saveSetToFile(const std::string_view & fileName, const std::set<std::string> & set)
    {
        std::ofstream out(fileName.data());
        for(const auto & value : set)
        {
            out << value << "\n";
        }
        out.close();
    }
}   // namespace File
