#include "FP_Formatter.hxx"

namespace FileParse
{

    void formatDouble(std::ostringstream & oss,
                      double value,
                      int precision,
                      double scientificLowerBound,
                      double scientificUpperBound)
    {
        bool useScientific
          = (std::abs(value) < scientificLowerBound || std::abs(value) > scientificUpperBound)
            && value != 0.0;

        if(useScientific)
        {
            oss.setf(std::ios::scientific, std::ios::floatfield);
        }
        else
        {
            oss.setf(std::ios::fixed, std::ios::floatfield);
        }
        oss.precision(precision);

        oss << value;

        std::string str = oss.str();
        // Trim trailing zeros
        if(str.find('.') != std::string::npos)
        {
            if(useScientific)
            {
                // For scientific notation, find the position of 'e' or 'E'
                auto ePos = str.find('e') != std::string::npos ? str.find('e') : str.find('E');
                auto lastNonZero = str.find_last_not_of('0', ePos - 1);
                if(lastNonZero != std::string::npos && lastNonZero + 1 < ePos)
                {
                    str.erase(lastNonZero + 1, ePos - lastNonZero - 1);
                }
                // Further trim if ".e" occurs
                auto dotEPos
                  = str.find(".e") != std::string::npos ? str.find(".e") : str.find(".E");
                if(dotEPos != std::string::npos)
                {
                    str.erase(dotEPos, 1);   // Remove the dot before 'e'
                }
            }
            else
            {
                // Remove trailing zeros for fixed notation
                str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                // Remove decimal point if no decimal part
                if(str.back() == '.')
                {
                    str.erase(str.length() - 1);
                }
            }
        }

        // Clear the ostringstream and insert the trimmed string
        oss.str("");
        oss.clear();
        oss << str;
    }
}   // namespace FileParse