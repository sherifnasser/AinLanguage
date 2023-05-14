#include "globalscope.hpp"

globalscope::globalscope(){
    setfuns(new std::vector<funscope>());
}

void globalscope::addfunction(funscope* funscope){
    getfuns()->push_back(*funscope);
}