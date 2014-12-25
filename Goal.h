#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class Goal : public BinaryNode
{
public:
    Goal(Node*, Node*); // (MainClass, ClassDeclarationList)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
