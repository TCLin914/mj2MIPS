#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class MethodDeclarationList : public BinaryNode
{
public:
    MethodDeclarationList(Node*, Node*); // (MethodDeclaration, MethodDeclarationList)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
