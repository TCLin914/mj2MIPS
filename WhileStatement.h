#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class WhileStatement : public BinaryNode
{
public:
    WhileStatement(Node*, Node*); // (cond-expression, do-statement)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
private:
    static const char MISSING_OPERAND_ERROR[];
    static const char WRONG_TYPE_ERROR[];
};
