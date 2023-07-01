#include "FunCallExpression.hpp"
#include "OldFunScope.hpp"
#include "OldConstant.hpp"
#include "ainio.hpp"
#define wcout std::wcout
#define endl std::endl

FunCallExpression::
FunCallExpression(std::wstring &funName, SharedVector<SharedIOldExpression> argsExpressions):
funName(funName),argsExpressions(argsExpressions){}

void FunCallExpression::print(std::wstring tabsize){
    wcout<<tabsize<<"FunCallExpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<funName<<endl;
    for(auto ex:*argsExpressions){
        ex->print(newtabsize);
    }
}

std::wstring FunCallExpression::evaluate(SharedScope evalScope){
    auto fun=evalScope->getparentScope()->getFunByName(this->funName);
    if(fun==nullptr){

        if(funName==L"اظهر"){
            if(argsExpressions->size()>1)
                throw(L"Too many arguments for calling " + funName + L"().");

            auto exval = (*argsExpressions)[0]->evaluate(evalScope);
            ainprint(exval,false);
            return L"";
        }

        else if(funName==L"اظهر_"){
            if(argsExpressions->size()>1)
                throw(L"Too many arguments for calling " + funName + L"().");
            
            auto exval = (*argsExpressions)[0]->evaluate(evalScope);
            ainprint(exval,true);
            return L"";
        }

        else if(funName==L"أدخل"){
            if(argsExpressions->size()>0)
                throw(L"Too many arguments for calling "+funName+L"().");
            
            std::wstring input=ainread(false);
            return input;
        }
        else if(funName==L"أدخل_"){
            if(argsExpressions->size()>0)
                throw(L"Too many arguments for calling "+funName+L"().");

            std::wstring input=ainread(true);
            return input;
        }
        else throw (L"function with name "+funName+L"() is not found.");
    }
    else if(argsExpressions->size()!=fun->getArgs()->size()){
        throw (L"Too many arguments for calling "+funName+L"().");
    }
    else{
        auto args=fun->getArgs();
        for(int i=0;i<args->size();i++){
            auto arg=(*args)[i];
            auto exval=(*argsExpressions)[i]->evaluate(evalScope);
            // TODO: type matching
            auto val=std::make_shared<OldConstant>(fun,arg.first,arg.second);
            val->setCurrentValue(exval);
            fun->getVars()->push_back(val);
        }
        fun->call();
        auto returnedvalue=fun->getReturnValue();
        /*for(auto var:*fun->getVars()){
            wcout<<L"var-"<<fun->getName()<<L": "<<var->getName()<<L", "<<var->getCurrentValue()<<endl;
        }*/
        fun->getVars()->clear();
        return returnedvalue;
    }
    return NULL;
}