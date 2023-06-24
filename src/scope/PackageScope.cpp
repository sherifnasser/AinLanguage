#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
PackageScope::PackageScope(std::wstring name,SharedPackageScope parentScope)
:BaseScope(name,parentScope){}

SharedPackageScope PackageScope::findPackageByName(std::wstring name){
    auto package=packages.find(name);
    if(package==packages.end())
        return nullptr;
    return package->second;
}

void PackageScope::addPackage(SharedPackageScope package) {
    packages[package->getName()]=package;
}

SharedPackageScope PackageScope::AIN_PACKAGE=std::make_shared<PackageScope>(L"عين");