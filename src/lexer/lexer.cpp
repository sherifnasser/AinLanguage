#include <iostream>
#include "lexer.hpp"
#include "lexerline.hpp"
#include "string_helper.hpp"

lexer::lexer(AinFile ainFile):ainFile(ainFile){
    lexerlines=new std::vector<lexerline>();

    auto lines=ainFile.getLines();

    int linenumber=0;

    for(auto &line:lines){
        linenumber++;
        if(line.empty())
            continue;
        lexerline nextlexerline=lexerline(linenumber);
        auto tokens=nextlexerline.gettokens();

        std::string prevword, newword;
        lexertoken::TOKEN_TYPE prevtoken=lexertoken::NOT_SET_TOKEN, newtoken=lexertoken::NOT_SET_TOKEN;

        for(int i=0;i<line.size();i++){
            
            char &c=line[i];
            if(std::ispunct(c)&&c!='_'){ // exclude the underscore as they represent identifier
                newtoken=lexertoken::SYMBOL_TOKEN;
                newword=c;

                // we're facing a string
                if(c==lexertoken::DOUBLE_QUOTE){
                    newtoken=lexertoken::LITERAL_TOKEN;

                    // increase i before the loop, as it might reach the end of the line, so the loop won't start
                    i++;

                    // append every char in the line until finding another DOUBLE_QUOTE
                    while(i<line.size()){
                        char &ch=line[i];
                        newword+=ch;
                        /*
                         we found a DOUBLE_QUOTE,
                         but check if there is no a BACK_SLASH before it,
                         then stop appending
                        */
                        if(ch==lexertoken::DOUBLE_QUOTE && line[i-1]!=lexertoken::BACK_SLASH)
                            break;
                        i++;
                    }
                }

                /******* TODO -> the multiline comment *******/

                // is it a start for a comment
                else if(c==lexertoken::SLASH){
                    // we're facing a single line comment
                    // we found a SLASH, but check if there is another SLASH after it
                    if(line[i+1]==lexertoken::SLASH){
                        newtoken=lexertoken::COMMENT_TOKEN;
                        // append everything from second slash to the end of the line
                        newword+=line.substr(i+1);

                        /*
                        to stop the loop in next iteration,
                        also to execute the push token command down below (break will not do it)
                        */ 
                        i=line.size();
                    }
                }
            }else if(std::isdigit(c)){
                newtoken=lexertoken::LITERAL_TOKEN;
                newword=c;

                /*
                TODO -> may delete the opertors and define it in the language as operator fun
                */

                // increase i before the loop, as it might reach the end of the line, so the loop won't start
                i++;

                bool hasdot=false;
                bool haspower10=false;
                bool haspower10minus=false;

                while(i<line.size()){
                    char ch = line[i];
                    auto DOT=lexertoken::DOT;
                    auto MINUS=lexertoken::MINUS;
                    auto npos=std::string::npos;

                    bool isliteraloperator=ch==DOT||ch=='E'||ch=='e'||ch==MINUS;

                    // if next char is a digit or underscore or dot or power 10 
                    if(std::isdigit(ch)||ch=='_'||isliteraloperator){

                        if(isliteraloperator){
                            if(
                                (hasdot&&ch==DOT)
                                ||(haspower10&&(ch=='E'||ch=='e'))
                                ||(haspower10minus&&ch==MINUS)
                            ){
                                i--; // to make the main char loop read them as symbols 
                                break;
                            }

                            if(!hasdot)
                                hasdot=ch==DOT;
                            if(!haspower10)
                                haspower10=ch=='E'||ch=='e';
                            if(haspower10){
                                hasdot=true; // as there shouldn't be a dot after the power
                                // there should be power first then minus
                                if(!haspower10minus){
                                    auto last=newword[newword.size()-1];
                                    // the minus should be after the power
                                    haspower10minus=ch==MINUS&&(last=='E'||last=='e');
                                }
                            }
                            
                        }
                        
                        newword += ch;
                        i++;
                    }
                    else break;
                }
            }else if(!std::isspace(c)||!std::isblank(c)){

            }

            // write the next token
            if(!std::isspace(c)||!std::isblank(c)){
                tokens->push_back(lexertoken(newtoken,newword));
                prevtoken=newtoken;
                prevword=newword;
            }
        }
        lexerlines->push_back(nextlexerline);
        
    }


}


std::vector<lexerline> lexer::getlexerlines(){
    return *lexerlines;
}