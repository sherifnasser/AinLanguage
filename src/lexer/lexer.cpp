#include <iostream>
#include "lexer.hpp"
#include "lexerline.hpp"
#include "string_helper.hpp"
#include "wchar_t_helper.hpp"
#include "keywordtoken.hpp"

#define DOUBLE_QOUTE L'\"'
#define BACK_SLASH L'\\'
#define SLASH L'/'
#define DOT L'.'
#define MINUS L'-'

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

        wstring prevword, newword;
        lexertoken::TOKEN_TYPE prevtoken=lexertoken::NOT_SET_TOKEN, newtoken=lexertoken::NOT_SET_TOKEN;

        for(int i=0;i<line.size();i++){
            
            auto &c=line[i];
            if(isainpunct(c)){ // exclude the underscore as they represent identifier
                newtoken=lexertoken::SYMBOL_TOKEN;
                newword=c;

                // we're facing a string
                if(c==DOUBLE_QOUTE){
                    newtoken=lexertoken::LITERAL_TOKEN;

                    // increase i before the loop, as it might reach the end of the line, so the loop won't start
                    i++;

                    // append every char in the line until finding another DOUBLE_QUOTE
                    while(i<line.size()){
                        auto &ch=line[i];
                        newword+=ch;
                        /*
                         we found a DOUBLE_QUOTE,
                         but check if there is no a BACK_SLASH before it,
                         then stop appending
                        */
                        if(ch==DOUBLE_QOUTE && line[i-1]!=BACK_SLASH)
                            break;
                        i++;
                    }
                }

                /******* TODO -> the multiline comment *******/

                // is it a start for a comment
                else if(c==SLASH){
                    // we're facing a single line comment
                    // we found a SLASH, but check if there is another SLASH after it
                    if(line[i+1]==SLASH){
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
            }else if(std::iswdigit(c)){
                newtoken=lexertoken::LITERAL_TOKEN;
                newword=c;

                // increase i before the loop, as it might reach the end of the line, so the loop won't start
                i++;

                // next char nc may be hex, oct or bin
                if(c=='0'&&isnumsystemchar(line[i])){
                    
                    auto &nc=line[i];
                    newword+=nc;
                    // increase i before the loop, as it might reach the end of the line, so the loop won't start
                    i++;
                    while (i < line.size()){
                        auto &ch = line[i];
                        if (
                            ((nc==L'x'||nc==L'X')&&!std::iswxdigit(ch))
                            ||
                            ((nc==L'b'||nc==L'B')&&!iswbdigit(ch))
                            ||
                            ((nc==L'o'||nc==L'O')&&!iswodigit(ch))
                        ){
                            i--;
                            break;
                        }
                        newword += ch;
                        i++;
                    }
                    
                }else{
                        /*
                    TODO -> may delete the opertors and define it in the language as operator fun
                    */

                    bool hasdot=false;
                    bool haspower10=false;
                    bool haspower10minus=false;

                    while(i<line.size()){
                        auto &ch = line[i];
                        auto npos=std::string::npos;

                        bool isliteraloperator=ch==DOT||ispower10literaloperator(ch)||ch==MINUS;

                        // if next char is a digit or underscore or dot or power 10 
                        if(std::iswdigit(ch)||ch==L'_'||isliteraloperator){

                            if(isliteraloperator){
                                if(
                                    (hasdot&&ch==DOT)
                                    ||(haspower10&&ispower10literaloperator(ch))
                                    ||(haspower10minus&&ch==MINUS)
                                ){
                                    i--; // to make the main char loop read them as symbols 
                                    break;
                                }

                                if(!hasdot)
                                    hasdot=ch==DOT;
                                if(!haspower10)
                                    haspower10=ispower10literaloperator(ch);
                                if(haspower10){
                                    hasdot=true; // as there shouldn't be a dot after the power
                                    // there should be power first then minus
                                    if(!haspower10minus){
                                        auto last=newword[newword.size()-1];
                                        // the minus should be after the power
                                        haspower10minus=ch==MINUS&&ispower10literaloperator(last);
                                    }
                                }
                                
                            }
                            
                            newword += ch;
                            i++;
                        }
                        else{
                            i--; // to make the main char loop read them as symbols 
                            break;
                        }
                    }
                }
                
            }else if(isainalpha(c)){
                newword=c;
                // increase i before the loop, as it might reach the end of the line, so the loop won't start
                i++;
                // get the full word until facing a space or a symbol (underscore excluded)
                while (i<line.size())
                {
                    auto &ch = line[i];
                    if(isainpunct(ch)||iswempty(ch)){
                        i--; // to make the main char loop read them as symbols 
                        break;
                    }
                    newword+=ch;
                    i++;
                }
                newtoken=(keywordtoken::iskeyword(newword))
                    ?lexertoken::KEYWORD_TOKEN:lexertoken::IDENTIFIER_TOKEN;
            }

            // write the next token
            if(!iswempty(c)){
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