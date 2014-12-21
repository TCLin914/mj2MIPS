#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class StatementList(Node*, Node*); // (Statement, StatementList)
{
public:
    StatementList(Node*, Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
    
