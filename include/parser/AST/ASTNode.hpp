#pragma once
#include "ASTVisitor.hpp"
class ASTNode{
    public:
        virtual void accept(ASTVisitor* visitor)=0;
        virtual ~ASTNode(){}  
};