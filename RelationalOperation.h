#pragma once
#include "BinaryNode.h"

using namespace std;

class RelationalOperation : public BinaryNode
{
public:
    RelationalOperation(Node*, Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    bool SemanticCheck();
    bool Initialize();
    bool IsEvaluable();
protected:
    static const char MISSING_OPERAND_ERROR[];
    static const char WRONG_TYPE_ERROR[];
};
