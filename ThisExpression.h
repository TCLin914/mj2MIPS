#pragma once
#include "NullaryNode.h"

using namespace std;

class ThisExpression : public NullaryNode
{
public:
    ThisExpression();
    //void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);    
    bool Initialize();
};
    
    
