#pragma once
#include "UnaryNode.h"
#include <string>

using namespace std;

class PrintlnStatement : public UnaryNode
{
public:
    PrintlnStatement(Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
