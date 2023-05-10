#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "string_helper.hpp"

class AinFile{
    private:
        std::vector<std::string> lines;

    public:
        AinFile(std::string &path);

        std::vector<std::string> getLines();

};