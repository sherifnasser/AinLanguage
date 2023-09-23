#include "LoopScope.hpp"
#include "FunScope.hpp"
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"

LoopScope::LoopScope(SharedBaseScope parentScope):
    StmListScope(L"حلقة_تكرارية",parentScope){}