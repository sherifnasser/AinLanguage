#include<iostream>
#include "ainio.hpp"

void ainprint(std::wstring s,bool endl){
    std::wios::sync_with_stdio(false);
    std::locale myloc("en_US.UTF-8");                                           
    std::wcout.imbue(myloc);
    std::wcout<<s;
    if(endl)
        std::wcout<<L"\n";
}

std::wstring ainread(bool readline){
    std::wios::sync_with_stdio(false);
    std::locale myloc("en_US.UTF-8");                                           
    std::wcin.imbue(myloc);
    std::wstring input;
    if(readline)
        getline(std::wcin,input);
    else
        std::wcin >> input;
    return input;
}
