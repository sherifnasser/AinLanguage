#pragma once
#include "IValue.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class ObjectValue:public virtual IValue{
    private:
        SharedMap<std::wstring, SharedIValue> properties;
    public:
        ObjectValue(SharedType type,SharedMap<std::wstring, SharedIValue> properties);
        void linkWithClass()override;
        void unlinkWithClass()override;
        std::wstring toString()override;
        SharedIValue findPropertyValue(std::wstring propertyName);
        void assignProperty(std::wstring propertyName,SharedIValue value);
};