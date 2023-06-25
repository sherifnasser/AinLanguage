#include "PackageScope.hpp"
#include "FileScope.hpp"
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

SharedFileScope PackageScope::findFileByPath(std::wstring path) {
    auto file=files.find(path);
    if(file==files.end())
        return nullptr;
    return file->second;
}

void PackageScope::addPackage(SharedPackageScope package) {
    packages[package->getName()]=package;
}

void PackageScope::addFile(SharedFileScope file){
    files[file->getName()]=file;
}

SharedPackageScope PackageScope::AIN_PACKAGE=std::make_shared<PackageScope>(L"عين");