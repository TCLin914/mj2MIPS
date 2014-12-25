#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class Assignment: public BinaryNode
{
public:
    Assignment(Node*, Node*); // (Identifier, Expression)
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
private:
    static const char MISSING_OPERAND_ERROR[];
    static const char UNASSIGNABLE_ERROR[];
    static const char WRONG_TYPE_ERROR[];
};
