#include "globalscope.hpp"

void globalscope::addfunction(funscope &funscope){
    getfuns()->push_back(funscope);
}