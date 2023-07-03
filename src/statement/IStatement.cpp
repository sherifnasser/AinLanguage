#include "IStatement.hpp"

IStatement::IStatement(int lineNumber,SharedStmListScope runScope)
:lineNumber(lineNumber),runScope(runScope){}