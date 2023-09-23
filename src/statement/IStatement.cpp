#include "IStatement.hpp"

IStatement::IStatement(int lineNumber,SharedBaseScope runScope)
:lineNumber(lineNumber),runScope(runScope){}

int IStatement::getLineNumber()const{
    return lineNumber;
}

SharedBaseScope IStatement::getRunScope()const{
    return runScope;
}
