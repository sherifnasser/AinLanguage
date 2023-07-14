#include "StringClassScope.hpp"
#include <string>

StringClassScope::StringClassScope()
:ClassScope(*Type::STRING_NAME,PackageScope::AIN_PACKAGE),
valueStack(std::make_shared<std::vector<std::wstring>>()){}

std::wstring StringClassScope::getValue(){
    return (*valueStack)[valueStack->size()-1];
}

void StringClassScope::setValue(std::wstring value){
    (*valueStack)[valueStack->size()-1]=value;
}

void StringClassScope::pushNewValue(){
    valueStack->push_back(L"");
}

void StringClassScope::popLastValue(){
    valueStack->pop_back();
}
