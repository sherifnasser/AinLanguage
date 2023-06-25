#pragma once
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
class FileScope:public BaseScope{
    public:
        FileScope(std::wstring filePath,SharedPackageScope parentScope);
};