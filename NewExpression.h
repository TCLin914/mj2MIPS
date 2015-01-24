#pragma once
#include "NullaryNode.h"
#include <string>

using namespace std;

class NewExpression : public NullaryNode
{
public:
    NewExpression(string);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool Initialize();
    Symbol* GetSymbol();
private:
    //Symbol* GetSymbol(string id);
    Symbol* classEntry;
    string id;
    static const char MISSING_CLASS_ERROR[];
};
