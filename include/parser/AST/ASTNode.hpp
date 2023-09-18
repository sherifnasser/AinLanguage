#pragma once
#include "AST/ASTVisitor.hpp"
class ASTNode{
    public:
        virtual void accept(ASTVisitor* visitor)=0;
        virtual ~ASTNode(){}  
};