#pragma once
#include "IAinFile.hpp"

class AinFile:public IAinFile{

    private:
        std::vector<std::wstring> lines;

    public:
        AinFile(std::string &path);

        void readAinFile(std::string &path) override;

        std::vector<std::wstring> getLines() override;

};