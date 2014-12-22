#include "stdafx.h"
#include "Node.h"
#include "ExpressionList.h"
#include <string>

ExpressionList::ExpressionList(Node* a, Node* b): BinaryNode(a, b)
{
}
void ExpressionList::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void ExpressionList::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool ExpressionList::SemanticCheck()
{
    return BinaryNode::SemanticCheck();
}
bool ExpressionList::Initialize()
{
    bool result = BinaryNode::Initialize();
    if(children[0] != NULL)
		type = children[0]->GetType();
    return result;
}
