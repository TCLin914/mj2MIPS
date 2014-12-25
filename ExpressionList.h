#pragma once
#include "BinaryNode.h"
#include <string>

using namespace std;

class ExpressionList: public BinaryNode
{
public:
    ExpressionList(Node*, Node*);		//(expression, expressionList) 
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
    static const int INDEX_OF_EXPRESSION = 0;
    static const int INDEX_OF_MORE = 1;
private:
};
