#pragma once
#include <iostream>
#include <string>
#include <vector>

class IAinFile{

    protected:
        virtual void readAinFile(std::string &path)=0;

    public:
        virtual std::vector<std::wstring> getLines()=0;

};