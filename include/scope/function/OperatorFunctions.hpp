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
    inline auto LOGICAL_AND_NAME=L"و";
    inline auto LOGICAL_OR_NAME=L"أو";
    inline auto COMPARE_TO_NAME=L"قارن_مع";
    inline auto EQUALS_NAME=L"يساوي";
    inline auto NOT_NAME=L"نفي";
    inline auto UNARY_PLUS_NAME=L"موجب";
    inline auto UNARY_MINUS_NAME=L"سالب";

    inline int isOperatorFunName(std::wstring name){

        auto BINARY_OPERATORS_NAMES={
            PLUS_NAME,MINUS_NAME,
            TIMES_NAME,DIV_NAME,
            MOD_NAME,POW_NAME,
            LOGICAL_AND_NAME,LOGICAL_OR_NAME,
            COMPARE_TO_NAME,EQUALS_NAME
        };

        for(auto& binOp:BINARY_OPERATORS_NAMES){
            if(name==binOp)
                return 1;
        }

        auto UNARY_OPERATORS_NAMES={
            UNARY_PLUS_NAME,UNARY_MINUS_NAME,NOT_NAME
        };
        for(auto& binOp:UNARY_OPERATORS_NAMES){
            if(name==binOp)
                return 0;
        }

        return -1;
    }

    inline std::wstring getUnaryOperatorFunNameByToken(LexerToken token){
        if(token==SymbolToken::PLUS)
            return UNARY_PLUS_NAME;
        if(token==SymbolToken::MINUS)
            return UNARY_MINUS_NAME;
        if(token==SymbolToken::EXCLAMATION_MARK)
            return NOT_NAME;
        return L"";
    }

    inline std::wstring getOperatorFunNameByToken(LexerToken token){
        if(token==SymbolToken::PLUS)
            return PLUS_NAME;
        if(token==SymbolToken::MINUS)
            return MINUS_NAME;
        if(token==SymbolToken::STAR)
            return TIMES_NAME;
        if(token==SymbolToken::SLASH)
            return DIV_NAME;
        if(token==SymbolToken::POWER)
            return POW_NAME;
        if(token==SymbolToken::MODULO)
            return MOD_NAME;
        if(token==SymbolToken::LOGICAL_AND)
            return LOGICAL_AND_NAME;
        if(token==SymbolToken::LOGICAL_OR)
            return LOGICAL_OR_NAME;
        if(token==SymbolToken::EXCLAMATION_MARK)
            return NOT_NAME;
        
        // FIXME: need to decide from parser
        if(token==SymbolToken::EQUAL_EQUAL||token==SymbolToken::NOT_EQUAL)
            return EQUALS_NAME;
        if(
            token==SymbolToken::LESS_EQUAL||token==SymbolToken::GREATER_EQUAL
            ||
            token==SymbolToken::LEFT_ANGLE_BRACKET||token==SymbolToken::RIGHT_ANGLE_BRACKET
        )
            return COMPARE_TO_NAME;
        return L"";
    }

    inline std::wstring getOperatorAssignEqualFunNameByToken(LexerToken token){
        if(token==SymbolToken::PLUS_EQUAL)
            return PLUS_NAME;
        if(token==SymbolToken::MINUS_EQUAL)
            return MINUS_NAME;
        if(token==SymbolToken::STAR_EQUAL)
            return TIMES_NAME;
        if(token==SymbolToken::SLASH_EQUAL)
            return DIV_NAME;
        if(token==SymbolToken::POWER_EQUAL)
            return POW_NAME;
        if(token==SymbolToken::MODULO_EQUAL)
            return MOD_NAME;
        return L"";
    }
}