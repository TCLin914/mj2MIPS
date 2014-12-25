#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class StatementList : public BinaryNode
{
public:
    StatementList(Node*, Node*); // (Statement, StatementList)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
    
