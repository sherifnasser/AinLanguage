#pragma once
#include "SharedPtrTypes.hpp"
#include <string>
class Type{
    private:
        SharedWString name;
        SharedClassScope classScope;
    public:
        Type(SharedWString name,SharedClassScope classScope=nullptr);
        bool operator==(const Type& type)const;
        bool operator!=(const Type& type)const;
        static SharedWString UNIT_NAME;
        static SharedWString INT_NAME;
        static SharedWString UINT_NAME;
        static SharedWString LONG_NAME;
        static SharedWString ULONG_NAME;
        static SharedWString FLOAT_NAME;
        static SharedWString DOUBLE_NAME;
        static SharedWString CHAR_NAME;
        static SharedWString STRING_NAME;
        static SharedWString BOOL_NAME;
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

        static void addBuiltInClassesTo(SharedFileScope fileScope);
};