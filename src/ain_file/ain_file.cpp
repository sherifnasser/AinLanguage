#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "string_helper.hpp"
#include "ain_file.hpp"

#define string std::string
#define vector std::vector
#define ifstream std::ifstream
#define getline std::getline

AinFile::AinFile(string &path){
    if(endsWith(path,".ain")){
        ifstream ainFile=ifstream(path);
        string line;
        while(getline(ainFile,line)){
            this->lines.push_back(line);
        }
        ainFile.close();
    }
    else{
        std::__throw_runtime_error("The passed file should be in .ain format.");
    }
}

vector<string> AinFile::getLines(){
    return this->lines;
}