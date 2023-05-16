#include "globalscope.hpp"

globalscope::globalscope(){
    setfuns(new std::vector<funscope*>());
}

void globalscope::addfunction(funscope* funscope){
    getfuns()->push_back(funscope);
}

funscope* globalscope::getmain(){
    for(auto fun:*getfuns()){
        if(fun->getname()==L"البداية")
            return fun;
    }
    throw L"Couldn't find the main function";
}