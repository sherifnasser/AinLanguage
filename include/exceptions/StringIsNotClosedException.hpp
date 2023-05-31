#pragma once
#include<iostream>
#include<string>
#include <cstdlib>
#include <cwchar>

class StringIsNotClosedException:public std::exception{
    private:
    std::wstring msgStr;

    public:

    StringIsNotClosedException(int lineNumber,std::wstring strLiteral){

        std::wstring c1=L"\033[1;31m";
        std::wstring lineNumStr=std::to_wstring(lineNumber);
        std::wstring armsg=L"في السطر "+lineNumStr+L" عند "+strLiteral+L"\n"+L"لم يتم إغلاق النص بعلامة تنصيص";
        std::wstring c2=L"\033[0m";
        msgStr=c1+armsg+c2;
    }

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
};