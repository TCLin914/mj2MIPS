#pragma once
#include "UnaryNode.h"
#include <string>

using namespace std;

class NewArray : public UnaryNode
{
public:
    NewArray(Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
