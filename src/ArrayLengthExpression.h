#pragma once
#include "UnaryNode.h"

using namespace std;

class ArrayLengthExpression : public UnaryNode
{
public:
    ArrayLengthExpression(Node*); // (Expression) 
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
    //bool IsAssignable();
    //bool IsLocalVariable();    
    Symbol* GetSymbol();
private:
    Symbol* varSymbol;    
};
