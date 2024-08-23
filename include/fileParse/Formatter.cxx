#include "Formatter.hxx"

namespace FileParse
{

    void trimTrailingZeros(std::string & str, bool useScientific)
    {
        if(useScientific)
        {
            // Find the exponent and trim zeros before it
            auto ePos = str.find_first_of("eE");
            auto lastNonZero = str.find_last_not_of('0', ePos - 1);
            if(lastNonZero != std::string::npos && lastNonZero + 1 < ePos)
            {
                str.erase(lastNonZero + 1, ePos - lastNonZero - 1);
            }
            // Remove the decimal point if it's directly before 'e' or 'E'
            auto dotEPos = str.find_first_of(".eE", lastNonZero);
            if (dotEPos != std::string::npos &&
               (dotEPos + 1 < str.size()) &&
               (str[dotEPos + 1] == 'e' || str[dotEPos + 1] == 'E'))
            {
                str.erase(dotEPos, 1);
            }

        }
        else
        {
            // Remove trailing zeros for non-scientific notation
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            // Remove decimal point if no decimal part remains
            if(str.back() == '.')
            {
                str.erase(str.length() - 1);
            }
        }
    }

    void formatDouble(std::ostringstream & oss,
                      double value,
                      int precision,
                      double scientificLowerBound,
                      double scientificUpperBound)
    {
        bool useScientific
          = (std::abs(value) < scientificLowerBound || std::abs(value) > scientificUpperBound)
            && value != 0.0;

        oss.setf(useScientific ? std::ios::scientific : std::ios::fixed, std::ios::floatfield);
        oss.precision(precision);
        oss << value;

        std::string str = oss.str();
        if(str.find('.') != std::string::npos)
        {
            trimTrailingZeros(str, useScientific);
        }

        // Reassign trimmed string to the ostringstream
        oss.str(str);
        oss.clear();
    }
}   // namespace FileParse