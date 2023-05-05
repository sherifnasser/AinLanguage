#include <iostream>
#include <string>
#include <vector>
#include "ain_file.hpp"
#define string std::string
#define vector std::vector
#define cout std::cout
#define endl std::endl
int main(){
    AinFile file("app.ain");
    vector<string> lines=file.getLines();
    for(string &line:lines){
        cout<<line<<endl;
    }
    return 0;
}