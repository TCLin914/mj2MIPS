#pragma once
#include "UnaryNode.h"
#include <string>

using namespace std;

class Variable : public UnaryNode
{
public:
    Variable(string, Node*);	// (id, [])
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
    bool IsAssignable();
    bool IsLocalVariable();
    int Dimensions();
    Symbol* GetSymbol();
private:
    Symbol* GetSymbol(string id);
    Symbol* varSymbol;
    string id;
    static const int INDEX_OF_MORE_EXPRESSION_LIST = 1;
    static const char DIMENSION_ERROR[];
    static const char UNDECLARED_VARIABLE_ERROR[];
    static const char INDEX_TYPE_ERROR[];
    static const char INDEX_RANGE_ERROR[];
};
