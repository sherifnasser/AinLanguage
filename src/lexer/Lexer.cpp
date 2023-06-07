#include <iostream>
#include "Lexer.hpp"
#include "LexerLine.hpp"
#include "string_helper.hpp"
#include "wchar_t_helper.hpp"
#include "KeywordToken.hpp"
#include "SymbolToken.hpp"

#define DOUBLE_QOUTE L'\"'
#define BACK_SLASH L'\\'
#define SLASH L'/'
#define DOT L'.'
#define MINUS2 L'-'

Lexer::Lexer(std::shared_ptr<IAinFile> ainFile):ainFile(ainFile){
    lexerlines=std::make_shared<std::vector<LexerLine>>();

    auto lines=ainFile->getLines();

    int lineNumber=0;

    for(auto &line:lines){
        lineNumber++;
        
        if(line.empty())
            continue;

        auto nextlexerline=lexLine(line,lineNumber);
        lexerlines->push_back(nextlexerline);
        
    }

}

LexerLine Lexer::lexLine(std::wstring line,int linenumber){

    LexerLine _lexerline=LexerLine(line,linenumber);
    auto tokens=_lexerline.getTokens();
    std::wstring newword;
    LexerToken::TOKEN_TYPE newtoken=LexerToken::NOT_SET_TOKEN;

    for(int i=0;i<line.size();i++){
        
        auto &c=line[i];
        if(isainpunct(c)){ // exclude the underscore as they represent identifier
            newtoken=LexerToken::SYMBOL_TOKEN;
            newword=c;

            // we're facing a string
            if(c==DOUBLE_QOUTE){
                newtoken=LexerToken::LITERAL_TOKEN;

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
                    newtoken=LexerToken::COMMENT_TOKEN;
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
            newtoken=LexerToken::LITERAL_TOKEN;
            auto size=tokens->size();
            auto last=(size>=1)?(*tokens)[size-1]:std::make_shared<LexerToken>(LexerToken::notsettoken);
            auto beforelast=(size>=2)?(*tokens)[size-2]:std::make_shared<LexerToken>(LexerToken::notsettoken);
            newword=L"";
            if(
                (*last==SymbolToken::PLUS||*last==SymbolToken::MINUS)
                &&
                (beforelast->getTokenType()==LexerToken::SYMBOL_TOKEN)
                &&
                (beforelast->getVal()!=L")")
            ){
                newword+=last->getVal();
                tokens->pop_back();
            }
            newword+=c;
            //std::wcout<<newword<<std::endl;

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

                while(i<line.size()){
                    auto &ch = line[i];
                    auto npos=std::string::npos;

                    bool isliteraloperator=ch==DOT||ispower10literaloperator(ch)||ch==MINUS2;

                    // if next char is a digit or underscore or dot or power 10 
                    if(std::iswdigit(ch)||ch==L'_'||isliteraloperator){

                        if(isliteraloperator){
                            auto ipower10E=newword.find(L'E');
                            auto ipower10e=newword.find(L'e');
                            auto ipower10=(ipower10E==npos)?ipower10e:ipower10E;
                            auto haspower10=ipower10!=npos;
                            auto ipower10minus=newword.find_last_of(L'-');
                            auto haspower10minus=haspower10&&(ipower10+1==ipower10minus);
                            auto finddot=newword.find(L'.');
                            auto hasdot=finddot!=npos||haspower10;
                            if(
                                (ispower10literaloperator(ch)&&haspower10)
                                ||
                                (ch==DOT&&hasdot)
                                ||
                                (ch==MINUS2&&ipower10!=newword.size()-1)
                            ){
                                i--; // to make the main char loop read them as symbols 
                                break;
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
            newtoken=(KeywordToken::iskeyword(newword))
                ?LexerToken::KEYWORD_TOKEN:LexerToken::IDENTIFIER_TOKEN;
        }

        // write the next token
        if(!iswempty(c)){
            auto token=std::make_shared<LexerToken>(LexerToken(newtoken,newword));
            tokens->push_back(token);
        }
        
    }

    return _lexerline;
}

std::vector<LexerLine> Lexer::getLexerLines(){
    return *lexerlines;
}