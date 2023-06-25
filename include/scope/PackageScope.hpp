#pragma once
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
#include <map>
#include <string>
class PackageScope:public BaseScope{
    private:
        std::map<std::wstring, SharedPackageScope> packages;
        std::map<std::wstring, SharedFileScope> files;
    public:
        PackageScope(std::wstring name,SharedPackageScope parentScope=nullptr);
        /**
        @brief search for an internal package by @param[name]
        @if found it will @return it
        @else @returns nullptr
        */
        SharedPackageScope findPackageByName(std::wstring name);

        /**
        @brief search for an internal file by @param[path]
        @if found it will @return it
        @else @returns nullptr
        */
        SharedFileScope findFileByPath(std::wstring path);

        void addPackage(SharedPackageScope package);

        void addFile(SharedFileScope file);

        static SharedPackageScope AIN_PACKAGE;

};