#include "stdafx.h"
#include "Node.h"
#include "NewArray.h"

NewArray::NewArray(Node* a) : UnaryNode(a)
{

}
void NewArray::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    UnaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void NewArray::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool NewArray::SemanticCheck()
{
    return UnaryNode::SemanticCheck();
}
bool NewArray::Initialize()
{
    type = ARRAY_T;
}
