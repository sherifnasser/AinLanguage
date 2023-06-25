#include "FileScope.hpp"
#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"

FileScope::FileScope(std::wstring filePath,SharedPackageScope parentScope)
:BaseScope(filePath,parentScope){}
