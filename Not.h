#pragma once
#include "UnaryNode.h"
#include <string>

using namespace std;

class Not : public UnaryNode
{
public:
    Not(Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
private:
    static const char MISSING_OPERAND_ERROR[];
    static const char WRONG_TYPE_ERROR[];
};
