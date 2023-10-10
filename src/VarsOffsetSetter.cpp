#include "VarsOffsetSetter.hpp"
#include "FunDecl.hpp"
#include "FunParam.hpp"

VarsOffsetSetter::Offset::Offset(int* reg, int value):
    reg(reg),
    value(value)
{}

VarsOffsetSetter::Offset::Offset():
    reg(0),
    value(0)
{}

VarsOffsetSetter::VarsOffsetSetter(
    std::unordered_map<Variable*, Offset>*offsets,
    int* BP,
    int* BX
)
:offsets(offsets),
BP(BP),
BX(BX){}

void VarsOffsetSetter::offsetStmListScope(StmListScope* scope){
    auto locals=scope->getLocals();

    auto offset=1;

    for(auto varIt:*scope->getLocals()){
        
        (*offsets)[varIt.second.get()]=Offset(
            BP,
            offset
        );

        offset++;
    }

    for(auto stm:*scope->getStmList())
        stm->accept(this);
}

void VarsOffsetSetter::visit(PackageScope* scope){
    for(auto packageIterator:scope->getPackages()){
        packageIterator.second->accept(this);
    }
    for(auto fileIterator:scope->getFiles()){
        fileIterator.second->accept(this);
    }
}

void VarsOffsetSetter::visit(FileScope* scope){
    for(auto funIt:*scope->getPublicFunctions()){
        funIt.second->accept(this);
    }
    for(auto funIt:*scope->getPrivateFunctions()){
        funIt.second->accept(this);
    }
    for(auto funIt:*scope->getPublicClasses()){
        funIt.second->accept(this);
    }
    for(auto funIt:*scope->getPrivateClasses()){
        funIt.second->accept(this);
    }
}

void VarsOffsetSetter::visit(ClassScope* scope){
    auto varsOffset=1;
    for(auto varIt:*scope->getPublicVariables()){
        (*offsets)[varIt.second.get()]=Offset(
            BX,
            varsOffset
        );

        varsOffset++;
    }
    for(auto varIt:*scope->getPrivateVariables()){
        (*offsets)[varIt.second.get()]=Offset(
            BX,
            varsOffset
        );

        varsOffset++;
    }
    for(auto funIt:*scope->getPublicFunctions()){
        funIt.second->accept(this);
    }
    for(auto funIt:*scope->getPrivateFunctions()){
        funIt.second->accept(this);
    }
}

void VarsOffsetSetter::visit(FunScope* scope){
    auto params=scope->getDecl()->params;

    auto paramsOffsets=std::unordered_map<std::wstring,int>{};

    auto offset=-1;
    for(auto paramIt=params->rbegin();paramIt!=params->rend();paramIt++){

        paramsOffsets[
            *paramIt->get()->name
        ]=offset--;

    }

    offset=1;
    for(auto varIt:*scope->getLocals()){
        
        auto paramOffsetIt=paramsOffsets.find(varIt.first);
        
        (*offsets)[varIt.second.get()]=Offset(
            BP,
            (paramOffsetIt==paramsOffsets.end())
            ?offset
            :paramOffsetIt->second
        );

        if(paramOffsetIt==paramsOffsets.end())
            offset++;
    }

    for(auto stm:*scope->getStmList())
        stm->accept(this);
}

void VarsOffsetSetter::visit(IfStatement* stm){
    offsetStmListScope(stm->getIfScope().get());

    if(auto elseScope=stm->getElseScope().get())
        offsetStmListScope(elseScope);
}

void VarsOffsetSetter::visit(WhileStatement* stm){
    offsetStmListScope(stm->getLoopScope().get());
}

void VarsOffsetSetter::visit(DoWhileStatement* stm){
    offsetStmListScope(stm->getLoopScope().get());
}