#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "string_helper.hpp"
#include "AinFile.hpp"
#include "BadFileFormatException.hpp"

#define vector std::vector
#define wifstream std::wifstream
#define getline std::getline

AinFile::AinFile(std::string &path){

    if(!endsWith(path,".ain")){
        throw BadFileFormatException(path);
    }
    
    readAinFile(path);
    
}

void AinFile::readAinFile(std::string &path){

    wifstream ainFile=wifstream(path);
    ainFile.imbue(std::locale("en_US.UTF-8"));
    std::wstring line;
    while(getline(ainFile,line)){
        this->lines.push_back(line);
    }
    ainFile.close();

}

vector<std::wstring> AinFile::getLines(){
    return this->lines;
}