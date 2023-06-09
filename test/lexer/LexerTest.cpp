
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>
#include "Lexer.hpp"

class FakeAinFile: public IAinFile{
    private:
        void readAinFile(std::string& path) override{}

        std::vector<std::wstring> getLines() override{
            return {
                L"line0",
            };
        }
};
