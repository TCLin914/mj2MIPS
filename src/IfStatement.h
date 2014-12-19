#pragma once
#include "TernaryNode.h"
#include <string>

using namespace std;

class IfStatement : public TernaryNode
{
public:
    IfStatement(Node*, Node*, Node*); // (if-expression, true-statement, false-statement)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
private:
    static const char MISSING_OPERAND_ERROR[];
    static const char WRONG_TYPE_ERROR[];
};
