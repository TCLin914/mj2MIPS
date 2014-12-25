#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class FunctionCall : public BinaryNode
{
public:
    FunctionCall(Node*, string, Node*); // (expression, function name, expressionlist)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
    Symbol* GetFuncSymbol();
    Symbol* GetClassSymbol();
private:
    string id;
    Symbol* funcSymbol;
    Symbol* classSymbol;
    static const char UNDECLARED_FUNCTION_ERROR[];
    static const char NOT_FUNCTION_ERROR[];
    static const char UNDECLARED_CLASS_ERROR[];
    static const char NOT_CLASS_ERROR[];    
    
    static const char ARGS_TYPE_ERROR[];
    static const char TOO_FEW_ARGS_ERROR[];
    static const char TOO_MANY_ARGS_ERROR[]; 
};
