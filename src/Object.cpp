#include "../include/Object.h"


bool checkString(const std::string& str)
{
    auto pred = [] (char chr) -> bool 
    {
        if (chr == ' ' || chr == '\t' || chr == '\n')
            return true;
        return false;
    };

    auto iter = std::find_if(str.begin(), str.end(), pred);
    
    if (iter != str.end() || str.length() == 0)
        return false;
    return true;
}

bool checkIfFloat(const std::string& str)
{
    if (str.empty() || str == "-" || str == "-.")
        return false;

    if (!isdigit(str[0]) && str[0] != '-')
        return false;

    char dotCount = 0;
    for (size_t i = 1; i < str.length(); i++)
    {
        char chr = str[i];

        if (chr == '.')
            dotCount++;

        if (!isdigit(chr) && chr != '.' || dotCount > 1)
            return false;
    }

    return true;
}
