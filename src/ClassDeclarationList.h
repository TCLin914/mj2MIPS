#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class ClassDeclarationList : public BinaryNode
{
public:
    ClassDeclarationList(Node*, Node*); // (ClassDeclaration, ClassDeclarationList)
    void SetSymbleTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
