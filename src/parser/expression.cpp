#include <iostream>
#include <vector>
#include <cmath>
#include "symboltoken.hpp"
#include "keywordtoken.hpp"
#include "expression.hpp"
#include "number_helper.hpp"
#include "string_helper.hpp"
#include "ainprint.hpp"
#define wcout std::wcout
#define endl std::endl
#define toint std::stoi
#define tolong std::stol
#define todouble std::stod
#define tofloat std::stof

bool boolexpression::boolfromstr(std::wstring s){
    return s==keywordtoken::TRUE.getval();
}

std::wstring boolexpression::strfrombool(bool b){
    return (b)?keywordtoken::TRUE.getval():keywordtoken::FALSE.getval();
}

boolexpression::boolexpression(std::wstring &val):val(val){}

void boolexpression::print(std::wstring tabsize){
    wcout<<tabsize<<"boolexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<std::boolalpha<<newtabsize<<boolfromstr(val)<<endl;
}

std::wstring boolexpression::evaluate(scope* evalscope){
    return val;
}

stringexpression::stringexpression(std::wstring &val):val(val){}

void stringexpression::print(std::wstring tabsize){
    wcout<<tabsize<<"stringexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<val<<endl;
}

std::wstring stringexpression::evaluate(scope* evalscope){
    // TODO: evaluate ctrl chars
    return val.substr(1,val.size()-2);
}

numberexpression::numberexpression(std::wstring &val):val(val){}

void numberexpression::print(std::wstring tabsize){
    wcout<<tabsize<<"numberexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<val<<endl;
}

std::wstring numberexpression::evaluate(scope* evalscope){
    return val;
}

binaryexpression::binaryexpression(expression* left, lexertoken &operation, expression* right):
left(left),right(right){
    if(
        operation==symboltoken::LOGICAL_OR||
        operation==symboltoken::LOGICAL_AND||
        operation==symboltoken::EQUAL_EQUAL||
        operation==symboltoken::NOT_EQUAL||
        operation==symboltoken::LESS_EQUAL||
        operation==symboltoken::GREATER_EQUAL||
        operation==symboltoken::LEFT_ANGLE_BRACKET||
        operation==symboltoken::RIGHT_ANGLE_BRACKET||
        operation==symboltoken::EXCLAMATION_MARK||
        operation==symboltoken::PLUS||
        operation==symboltoken::MINUS||
        operation==symboltoken::STAR||
        operation==symboltoken::SLASH||
        operation==symboltoken::MODULO||
        operation==symboltoken::POWER
    )
        this->operation=operation;
    else{
        wcout<<L"val: "<<operation.getval();
        std::__throw_invalid_argument("Binary operation must be +, -, *, /, ^, %, >=, <=, ==, !=, && or ||");
    }
}

void binaryexpression::print(std::wstring tabsize){
    wcout<<tabsize<<"binaryxpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    left->print(newtabsize);
    wcout<<newtabsize<<"Operation"<<endl;
    wcout<<newtabsize+L"\t"<<operation.getval()<<endl;
    right->print(newtabsize);
}

std::wstring binaryexpression::evaluate(scope* evalscope){
    std::wstring result;
    auto leftRes=left->evaluate(evalscope);
    auto rightRes=right->evaluate(evalscope);

    if(operation==symboltoken::LOGICAL_OR){
        result=evaluatelogicalor(leftRes,rightRes);
    }
    else if(operation==symboltoken::LOGICAL_AND){
        result=evaluatelogicaland(leftRes,rightRes);
    }
    else if(operation==symboltoken::EQUAL_EQUAL){
        result=evaluateequalequal(leftRes,rightRes);
    }
    else if(operation==symboltoken::NOT_EQUAL){
        result=evaluatenotequal(leftRes,rightRes);
    }
    else if(operation==symboltoken::GREATER_EQUAL){
        result=evaluategreaterequal(leftRes,rightRes);
    }
    else if(operation==symboltoken::LESS_EQUAL){
        result=evaluatelessequal(leftRes,rightRes);
    }
    else if(operation==symboltoken::RIGHT_ANGLE_BRACKET){
        result=evaluategreater(leftRes,rightRes);
    }
    else if(operation==symboltoken::LEFT_ANGLE_BRACKET){
        result=evaluateless(leftRes,rightRes);
    }
    else if(operation==symboltoken::PLUS){
        result=evaluateplus(leftRes,rightRes);
    }
    else if(operation==symboltoken::MINUS){
        result=evaluateminus(leftRes,rightRes);
    }
    else if(operation==symboltoken::STAR){
        result=evaluatestar(leftRes,rightRes);
    }
    else if(operation==symboltoken::SLASH){
        result=evaluateslash(leftRes,rightRes);
    }
    else if(operation==symboltoken::MODULO){
        result=evaluatemodulo(leftRes,rightRes);
    }
    else if(operation==symboltoken::POWER){
        result=evaluatepower(leftRes,rightRes);
    }

    return result;
}

std::wstring binaryexpression::evaluatelogicalor(std::wstring l, std::wstring r){
    auto res=boolexpression::boolfromstr(l)||boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluatelogicaland(std::wstring l, std::wstring r){
    auto res=boolexpression::boolfromstr(l)&&boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluateequalequal(std::wstring l, std::wstring r){
    auto res=l==r;
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluatenotequal(std::wstring l, std::wstring r){
    auto res=l!=r;
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluatelessequal(std::wstring l, std::wstring r){
    auto res=todouble(l)<=todouble(r);
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluategreaterequal(std::wstring l, std::wstring r){
    auto res=todouble(l)>=todouble(r);
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluateless(std::wstring l, std::wstring r){
    auto res=todouble(l)<todouble(r);
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluategreater(std::wstring l, std::wstring r){
    auto res=todouble(l)>todouble(r);
    return boolexpression::strfrombool(res);
}

std::wstring binaryexpression::evaluateplus(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)+todouble(r));
    }
    else return l.append(r);
}

std::wstring binaryexpression::evaluateminus(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)-todouble(r));
    }
    return L"";
}

std::wstring binaryexpression::evaluatestar(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)*todouble(r));
    }
    return L"";
}

std::wstring binaryexpression::evaluateslash(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)/todouble(r));
    }
    return L"";
}

std::wstring binaryexpression::evaluatemodulo(std::wstring l, std::wstring r){
    if(isint(l)&&isint(r)){
        return std::to_wstring(toint(l)%toint(r));
    }
    return L"";
}

std::wstring binaryexpression::evaluatepower(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(pow(todouble(l),todouble(r)));
    }
    return L"";
}

variableaccessexpression::variableaccessexpression(std::wstring &name):name(name){}

void variableaccessexpression::print(std::wstring tabsize){
    wcout<<tabsize<<"variableaccessexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<name<<endl;
}

std::wstring variableaccessexpression::evaluate(scope* evalscope){
    auto var=evalscope->getvarbyname(this->name);
    return var->getcurrentvalue();
}

funcallexpression::
funcallexpression(std::wstring &funname, std::vector<expression*>* argsexpressions):
funname(funname),argsexpressions(argsexpressions){}

void funcallexpression::print(std::wstring tabsize){
    wcout<<tabsize<<"funcallexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<funname<<endl;
    for(auto ex:*argsexpressions){
        ex->print(newtabsize);
    }
}

std::wstring funcallexpression::evaluate(scope* evalscope){
    auto fun=evalscope->getparentscope()->getfunbyname(this->funname);
    if(fun==nullptr){

        if(funname==L"اظهر"){
            if(argsexpressions->size()>1)
                throw(L"Too many arguments for calling " + funname + L"().");

            auto exval = (*argsexpressions)[0]->evaluate(evalscope);
            ainprint(exval,false);
            return L"";
        }

        else if(funname==L"اظهر_"){
            if(argsexpressions->size()>1)
                throw(L"Too many arguments for calling " + funname + L"().");
            
            auto exval = (*argsexpressions)[0]->evaluate(evalscope);
            ainprint(exval,true);
            return L"";
        }

        else if(funname==L"أدخل"){
            if(argsexpressions->size()>0)
                throw(L"Too many arguments for calling "+funname+L"().");
            
            std::wstring input;
            std::wcin >> input;
            return input;
        }
        else throw (L"function with name "+funname+L"() is not found.");
    }
    else if(argsexpressions->size()!=fun->getargs()->size()){
        throw (L"Too many arguments for calling "+funname+L"().");
    }
    else{
        auto args=fun->getargs();
        for(int i=0;i<args->size();i++){
            auto arg=(*args)[i];
            auto exval=(*argsexpressions)[i]->evaluate(evalscope);
            // TODO: type matching
            auto val=new constant(fun,arg.first,arg.second);
            val->setcurrentvalue(exval);
            fun->getvars()->push_back(val);
        }
        fun->call();
        auto returnedvalue=fun->getreturnvalue();
        /*for(auto var:*fun->getvars()){
            wcout<<L"var-"<<fun->getname()<<L": "<<var->getname()<<L", "<<var->getcurrentvalue()<<endl;
        }*/
        fun->getvars()->clear();
        return returnedvalue;
    }
    return NULL;
}