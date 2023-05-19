#include<iostream>
#include "ainprint.hpp"

void ainprint(std::wstring s,bool endl){
    std::ios::sync_with_stdio(false);
    std::locale myloc("en_US.UTF-8");                                           
    std::wcout.imbue(myloc);
    std::wcout<<s;
    if(endl)
        std::wcout<<std::endl;
    std::ios::sync_with_stdio(true);
}
