#pragma once
#include "BinaryNode.h"

using namespace std;

class ArithmeticOperation : public BinaryNode
{
public: 
    ArithmeticOperation(Node*, Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    bool SemanticCheck();
    bool Initialize();
    bool IsEvaluable();
    int GetIntValue();
protected:
    virtual int AGetIntValue() = 0;
private:
    bool locallySemanticCheck();
    static const char MISSING_OPERAND_ERROR[];
    static const char WRONG_TYPE_ERROR[];
    static const char NOT_INTEGER_EXCEPTION[];
};
