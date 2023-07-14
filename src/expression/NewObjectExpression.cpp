#include "NewObjectExpression.hpp"
#include "FunInvokeExpression.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include <string>
#include <vector>

NewObjectExpression::NewObjectExpression(
    int lineNumber,
    SharedType type,
    SharedVector<SharedIExpression> args
):IExpression(lineNumber,type),args(args){}

std::vector<std::wstring> NewObjectExpression::prettyPrint(){
    auto prints=std::vector<std::wstring>();
    auto lineNumStr=std::to_wstring(lineNumber);
    prints.push_back(L"NewObjectExpression \'"+*returnType->getName()+L"\' at "+lineNumStr);

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

SharedIValue NewObjectExpression::evaluate(){
    
}

void NewObjectExpression::check(SharedBaseScope checkScope) {
    
}
