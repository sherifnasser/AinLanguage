#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "string_helper.hpp"
#define string std::string
#define vector std::vector

class AinFile{
    private:
        vector<string> lines;

    public:
        AinFile(string path);

        vector<string> getLines();

};