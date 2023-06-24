#pragma once
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
#include <map>
#include <string>
class PackageScope:public BaseScope{
    private:
        std::map<std::wstring, SharedPackageScope> packages;
    public:
        PackageScope(std::wstring name,SharedPackageScope parentScope=nullptr);
        /**
        @brief search for an internal package by @param[name]
        @if found it will @return it
        @else @returns nullptr
        */
        SharedPackageScope findPackageByName(std::wstring name);

        void addPackage(SharedPackageScope package);

        static SharedPackageScope AIN_PACKAGE;

};