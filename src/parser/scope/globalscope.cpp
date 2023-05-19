#include "globalscope.hpp"

globalscope::globalscope(){
    setfuns(new std::vector<funscope*>());
}

void globalscope::addfunction(funscope* funscope){
    getfuns()->push_back(funscope);
}

funscope* globalscope::getmain(){
    auto fun=getfunbyname(L"البداية");
    if (fun!=nullptr)
        return fun;
    else
        throw L"Couldn't find the main function";
}