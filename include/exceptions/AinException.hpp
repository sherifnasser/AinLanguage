#pragma once
#include<iostream>
#include<algorithm>
#include<string>
#include <cstdlib>
#include <cwchar>

class AinException:public std::exception{
    private:
    std::wstring msgStr;

    public:

    AinException(std::wstring msgStr):msgStr(msgStr){}

    const char* what() const noexcept override{
        
        std::setlocale(0,"en_US.UTF-8");
        
        auto wmsg=msgStr.c_str();
        
        // Get the length of the multibyte string
        std::size_t len = std::wcstombs(nullptr, wmsg, 0);

        // Allocate a buffer to hold the multibyte string
        char* mbstr = new char[len + 1];

        // Convert the wide character string to a multibyte character string
        std::wcstombs(mbstr, wmsg, len + 1);

        return mbstr;
    }

    std::wstring whatWstr(){
        return msgStr;
    }

    static std::wstring errorWString(std::wstring wstr){
        return L"\033[1;31m"+wstr+L"\033[0m";
    }

    static std::wstring betweenAngleBrackets(std::wstring wstr){
        return L"<"+wstr+L">";
    }
    
    static std::wstring removeNullChar(std::wstring wstr){
        wstr.erase(remove(wstr.begin(), wstr.end(), L'\0'), wstr.end());
        return wstr;
    }
};