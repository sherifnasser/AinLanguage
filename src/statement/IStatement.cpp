#include "IStatement.hpp"

IStatement::IStatement(int lineNumber,SharedBaseScope runScope)
:lineNumber(lineNumber),runScope(runScope){}