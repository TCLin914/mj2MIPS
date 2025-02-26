#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class MethodDeclaration : public BinaryNode
{
public:
    MethodDeclaration(string, Node*, Node*); // (method name, statementList, (return) Expression)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
    Symbol* GetMethodSymbol();
        
private:
    Symbol* methodEntry;
    string id;   
    static const char MISSING_METHOD_ERROR[];
};
