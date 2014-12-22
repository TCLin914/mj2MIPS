#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class MethodDeclaration : public BinaryNode
{
public:
    MethodDeclaration(string, Node*, Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
    Symbol* GetMethodSymbol();

    void SetSymbol(Symbol*);
    Symbol* GetSymbol;
private:
    Symbol* methodEntry;
    string id;
    Symbol* symbol;
    static const char MISSING_METHOD_ERROR[];
};
