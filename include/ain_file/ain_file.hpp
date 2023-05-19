#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "string_helper.hpp"

class AinFile{
    private:
        std::vector<std::wstring> lines;

    public:
        AinFile(std::string &path);

        std::vector<std::wstring> getLines();

};