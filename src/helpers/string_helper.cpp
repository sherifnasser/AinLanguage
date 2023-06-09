#include <string>
#include <algorithm>
#include "string_helper.hpp"
bool startsWith(std::string str, std::string prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

bool endsWith(std::string str, std::string suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

void removeUnderscores(std::wstring* wstr){
    wstr->erase(
        std::remove_if(
            wstr->begin(),
            wstr->end(),
            [](auto c){return c==L'_';}
        ),
        wstr->end()
    );
}