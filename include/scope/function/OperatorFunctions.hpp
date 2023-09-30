#pragma once
#include "LexerToken.hpp"
#include "SymbolToken.hpp"
#include <string>

namespace OperatorFunctions{

    inline auto PLUS_NAME=L"زائد";
    inline auto MINUS_NAME=L"ناقص";
    inline auto TIMES_NAME=L"ضرب";
    inline auto DIV_NAME=L"قسمة";
    inline auto MOD_NAME=L"باقي";
    inline auto POW_NAME=L"أس";
    inline auto COMPARE_TO_NAME=L"قارن_مع";
    inline auto EQUALS_NAME=L"يساوي";
    inline auto LOGICAL_NOT_NAME=L"نفي";
    inline auto UNARY_PLUS_NAME=L"موجب";
    inline auto UNARY_MINUS_NAME=L"سالب";
    inline auto INC_NAME=L"زد";
    inline auto DEC_NAME=L"أنقص";

    inline bool isOperatorFunName(std::wstring name){
        
        auto OPERATORS_NAMES={
            // Binary operators
            PLUS_NAME,MINUS_NAME,
            TIMES_NAME,DIV_NAME,
            MOD_NAME,POW_NAME,
            COMPARE_TO_NAME,EQUALS_NAME,
            // Unary operators
            UNARY_PLUS_NAME,UNARY_MINUS_NAME,LOGICAL_NOT_NAME,INC_NAME,DEC_NAME
        };

        for(auto& binOp:OPERATORS_NAMES){
            if(name==binOp)
                return true;
        }

        return false;
    }
    
}