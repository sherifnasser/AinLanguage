#pragma once
#include "SharedPtrTypes.hpp"
struct FunDecl{
    SharedWString name;
    SharedType returnType;
    SharedBool isOperator;
    SharedVector<SharedFunParamater> params;
    FunDecl(
        SharedWString name,
        SharedType returnType,
        SharedBool isOperator,
        SharedVector<SharedFunParamater> params
    );

    /**
     * @warning This method doesn't check for property [isOperator]
     * and it should be checked explicitly
    */
    bool operator==(const FunDecl& declaration)const;
    
    /**
     * @warning This method doesn't check for property [isOperator]
     * and it should be checked explicitly
    */
    bool operator!=(const FunDecl& declaration)const;
};