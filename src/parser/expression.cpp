#include <iostream>
#include <vector>
#include <cmath>
#include "symboltoken.hpp"
#include "keywordtoken.hpp"
#include "expression.hpp"
#include "number_helper.hpp"
#include "string_helper.hpp"
#define wcout std::wcout
#define endl std::endl
#define toint std::stoi
#define tolong std::stol
#define todouble std::stod
#define tofloat std::stof

bool boolexpression::boolfromstr(wstring s){
    return s==keywordtoken::TRUE.getval();
}

wstring boolexpression::strfrombool(bool b){
    return (b)?keywordtoken::TRUE.getval():keywordtoken::FALSE.getval();
}

boolexpression::boolexpression(wstring &val):val(val){}

void boolexpression::print(wstring tabsize){
    wcout<<tabsize<<"boolexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<std::boolalpha<<newtabsize<<boolfromstr(val)<<endl;
}

wstring boolexpression::evaluate(scope* evalscope){
    return val;
}

stringexpression::stringexpression(wstring &val):val(val){}

void stringexpression::print(wstring tabsize){
    wcout<<tabsize<<"stringexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<val<<endl;
}

wstring stringexpression::evaluate(scope* evalscope){
    // TODO: evaluate ctrl chars
    return val.substr(1,val.size()-2);
}

numberexpression::numberexpression(wstring &val):val(val){}

void numberexpression::print(wstring tabsize){
    wcout<<tabsize<<"numberexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<val<<endl;
}

wstring numberexpression::evaluate(scope* evalscope){
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

void binaryexpression::print(wstring tabsize){
    wcout<<tabsize<<"binaryxpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    left->print(newtabsize);
    wcout<<newtabsize<<"Operation"<<endl;
    wcout<<newtabsize+L"\t"<<operation.getval()<<endl;
    right->print(newtabsize);
}

wstring binaryexpression::evaluate(scope* evalscope){
    wstring result;
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

wstring binaryexpression::evaluatelogicalor(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)||boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluatelogicaland(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)&&boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluateequalequal(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)==boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluatenotequal(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)!=boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluatelessequal(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)<=boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluategreaterequal(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)>=boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluateless(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)<boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluategreater(wstring l, wstring r){
    auto res=boolexpression::boolfromstr(l)>boolexpression::boolfromstr(r);
    return boolexpression::strfrombool(res);
}

wstring binaryexpression::evaluateplus(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)+todouble(r));
    }
    else return l.append(r);
}

wstring binaryexpression::evaluateminus(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)-todouble(r));
    }
    return L"";
}

wstring binaryexpression::evaluatestar(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)*todouble(r));
    }
    return L"";
}

wstring binaryexpression::evaluateslash(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)/todouble(r));
    }
    return L"";
}

wstring binaryexpression::evaluatemodulo(wstring l, wstring r){
    if(isint(l)&&isint(r)){
        return std::to_wstring(toint(l)%toint(r));
    }
    return L"";
}

wstring binaryexpression::evaluatepower(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(pow(todouble(l),todouble(r)));
    }
    return L"";
}

variableaccessexpression::variableaccessexpression(wstring &name):name(name){}

void variableaccessexpression::print(wstring tabsize){
    wcout<<tabsize<<"variableaccessexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<name<<endl;
}

wstring variableaccessexpression::evaluate(scope* evalscope){
    auto var=evalscope->getvarbyname(this->name);
    return var->getcurrentvalue();
}

funcallexpression::
funcallexpression(wstring &funname, std::vector<expression*>* argsexpressions):
funname(funname),argsexpressions(argsexpressions){}

void funcallexpression::print(wstring tabsize){
    wcout<<tabsize<<"funcallexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<funname<<endl;
    for(auto ex:*argsexpressions){
        ex->print(newtabsize);
    }
}

wstring funcallexpression::evaluate(scope* evalscope){
    auto fun=evalscope->getparentscope()->getfunbyname(this->funname);
    if(fun==nullptr){

        if(funname==L"اظهر"){
            if(argsexpressions->size()>1)
                throw(L"Too many arguments for calling " + funname + L"().");

            auto exval = (*argsexpressions)[0]->evaluate(evalscope);
            wcout << exval;
            return L"";
        }

        else if(funname==L"اظهر_"){
            if(argsexpressions->size()>1)
                throw(L"Too many arguments for calling " + funname + L"().");
            
            auto exval = (*argsexpressions)[0]->evaluate(evalscope);
            wcout << exval << endl;
            return L"";
        }

        else if(funname==L"أدخل"){
            if(argsexpressions->size()>0)
                throw(L"Too many arguments for calling "+funname+L"().");
            
            wstring input;
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