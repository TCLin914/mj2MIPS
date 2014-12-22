#include "stdafx.h"
#include "Node.h"
#include "Goal.h"
#include <string>

Goal::Goal(Node* a, Node* b) : BinaryNode(a, b)
{

}
void Goal::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void Goal::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool Goal::SemanticCheck()
{
    return BinaryNode::SemanticCheck();
}
bool Goal::Initialize()
{
    return BinaryNode::Initialize();
}
