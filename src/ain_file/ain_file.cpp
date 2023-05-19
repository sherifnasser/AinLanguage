#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "string_helper.hpp"
#include "ain_file.hpp"

#define wstring std::wstring
#define vector std::vector
#define wifstream std::wifstream
#define getline std::getline

AinFile::AinFile(std::string &path){
    if(endsWith(path,".ain")){
        wifstream ainFile=wifstream(path);
        ainFile.imbue(std::locale("en_US.UTF-8"));
        wstring line;
        while(getline(ainFile,line)){
            this->lines.push_back(line);
        }
        ainFile.close();
    }
    else{
        std::__throw_runtime_error("The passed file should be in .ain format.");
    }
}

vector<wstring> AinFile::getLines(){
    return this->lines;
}