#include <iostream>
#include <string>
#include <vector>
#include "ain_file.hpp"
#define string std::string
#define vector std::vector
#define cout std::cout
#define endl std::endl
int main(int argc, char * argv[]){
    if(argc > 2){ // 2 as it includes the prgram name
        std::__throw_out_of_range("You can only pass one argumet for the ain file path.");
        return -1;
    }
        
    string path(argv[1]); // as it's the second arg
    AinFile file(path);
    vector<string> lines=file.getLines();
    for(string &line:lines){
        cout<<line<<endl;
    }
    return 0;
}