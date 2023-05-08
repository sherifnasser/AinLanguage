#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#define cout std::cout
#define endl std::endl
#define string std::string
#define vector std::vector
namespace fs=std::filesystem;


const string C_SRC_FILES="set(SRC_FILES";
string SRC_FILES=C_SRC_FILES;
const string C_INCLUDE="set(INCLUDE";
string INCLUDE=C_INCLUDE;
vector<string> cmake_lines;
vector<string> new_cmake_lines;

bool startsWith(string str, string prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

void read_from_cmake_file(){
    std::ifstream file("CMakeLists.txt");
    string line;
    while(std::getline(file,line)){
        cmake_lines.push_back(line);
    }
    file.close();
}

void write_to_cmake_file(){
    int i=0; // number of reading ) after src
    bool deleteNextLines=false;
    for(auto &line:cmake_lines){
        // if the line starts with SRC_FILES pre-defined value
        if(startsWith(line,C_SRC_FILES)){
            new_cmake_lines.push_back(SRC_FILES);
            new_cmake_lines.push_back(INCLUDE);
            deleteNextLines=true;
        }
        else if(deleteNextLines){
            // do nothing and stops when see )
            if(startsWith(line,")")){
                if(i==1)
                deleteNextLines=false;
            else
                i++;
            }
        }
        else{
            new_cmake_lines.push_back(line);
        }
    }
    
    std::ofstream file("CMakeLists.txt");
    for(auto &line:new_cmake_lines){
        file<<line<<endl;
    }
    file.close();
}

void readinclude(string path){
    for(const auto & entry: fs::directory_iterator(path)){
        auto p=entry.path();
        if(fs::is_directory(p)){
            INCLUDE.append("\n    ").append(p).append("/");
            readinclude(p);
        }
    }
}

void readsrc(string path){
    for(const auto & entry: fs::directory_iterator(path)){
        auto p=entry.path();
        if(fs::is_directory(p)){
            readsrc(p);
        }
        else if(p.extension()==".cpp"&&p.filename()!="main.cpp"){
            SRC_FILES.append("\n    ").append(p);
        }
    }
}

void setsrc(){
    readsrc("src");
    SRC_FILES.append("\n)");
}

void setinclude(){
    readinclude("include");
    INCLUDE.append("\n)");
}

int main(){
    SRC_FILES.append("\n    src/main.cpp");
    INCLUDE.append("\n    include/");
    setsrc();
    setinclude();
    read_from_cmake_file();
    write_to_cmake_file();
    return 0;
}