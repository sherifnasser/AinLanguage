#include "PrintlnFunScope.hpp"
#include "BuiltInFunScope.hpp"
#include "FunDecl.hpp"
#include "FunParam.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "UnitValue.hpp"
#include "ainio.hpp"
#include "IValue.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

PrintlnFunScope::PrintlnFunScope()
    : BuiltInFunScope(
        L"اظهر_",
        Type::UNIT,
        std::map<std::wstring, SharedType>{
            {L"الرسالة",Type::STRING}
        }
    )

{
    
}

void PrintlnFunScope::check(){
    
}

SharedIValue PrintlnFunScope::invoke(SharedMap<std::wstring, SharedIValue> params) {
    for(auto paramIterator:*params){
        auto paramVal=paramIterator.second->toString();
        ainprint(paramVal, true);
    }
    return std::make_shared<UnitValue>();
}
