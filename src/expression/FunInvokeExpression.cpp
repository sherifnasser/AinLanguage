#include "FunInvokeExpression.hpp"
#include <iostream>
#include <string>
#include <vector>

FunInvokeExpression::FunInvokeExpression(int lineNumber,std::wstring funName, SharedVector<SharedIExpression> args)
    : IExpression(lineNumber,nullptr),
      funName(funName),
      args(args){}

std::vector<std::wstring> FunInvokeExpression::prettyPrint(){
    auto prints=std::vector<std::wstring>();
    auto lineNumStr=std::to_wstring(lineNumber);
    prints.push_back(L"FunExpression \'"+funName+L"\' at "+lineNumStr);

    for(int i=0;i<args->size();i++){
        auto argPrints=args->at(i)->prettyPrint();
        
        argPrints[0]=
            ((i==args->size()-1)?L"└──":L"├──")+argPrints[0];

        for(int j=1;j<argPrints.size();j++){
            argPrints[j]=
                ((i==args->size()-1)?L"    ":L"│   ")+argPrints[j];
        }

        prints.insert(prints.end(),argPrints.begin(),argPrints.end());
    }
    return prints;
}

SharedIValue FunInvokeExpression::evaluate() {
    
}

void FunInvokeExpression::check(SharedBaseScope checkScope) {
    
}


