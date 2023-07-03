#include "StmListScope.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
#include <vector>

StmListScope::StmListScope(std::wstring name,SharedBaseScope parentScope)
:
    BaseScope(name,parentScope),
    locals(
        std::make_shared<std::map<std::wstring,SharedVariable>>()
    ),
    stmList(
        std::make_shared<std::vector<SharedIStatement>>()
    )
{}

SharedMap<std::wstring, SharedVariable> StmListScope::getLocals(){
    return locals;
}
