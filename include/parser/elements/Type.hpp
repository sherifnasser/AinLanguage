#pragma once
#include "SharedPtrTypes.hpp"
#include <string>
class Type{
    private:
        SharedWString name;
        SharedClassScope classScope;
    public:
        Type(SharedWString name);
        bool operator==(const Type& type)const;
        bool operator!=(const Type& type)const;
        static SharedType UNIT;
        static SharedType CHAR;
        static SharedType INT;
        static SharedType LONG;
        static SharedType FLOAT;
        static SharedType UINT;
        static SharedType ULONG;
        static SharedType DOUBLE;
        static SharedType BOOL;
        static SharedType STRING;

        SharedClassScope getClassScope();
        
        void setClassScope(SharedClassScope classScope);

        SharedWString getName();
};