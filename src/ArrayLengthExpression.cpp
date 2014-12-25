#include "stdafx.h"
#include "Node.h"
#include "ArrayLengthExpression.h"
#include "UnaryNode.h"

ArrayLengthExpression::ArrayLengthExpression(Node* a) : UnaryNode(a)
{
   
}
void ArrayLengthExpression::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    UnaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void ArrayLengthExpression::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool ArrayLengthExpression::SemanticCheck()
{
    bool result = UnaryNode::SemanticCheck();   
    //TODO: children[0] check 
} 
bool ArrayLengthExpression::Initialize()
{
    type = INTEGER_T;
}
