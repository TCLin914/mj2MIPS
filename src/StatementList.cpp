#include "stdafx.h"
#include "Node.h"
#include "StatementList.h"
#include <string>

StatementList::StatementList(Node* a, Node* b) : BinaryNode(a, b)
{

}
void StatementList::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);

}
void StatementList::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool StatementList::SemanticCheck()
{
    return BinaryNode::SemanticCheck();
}
bool StatementList::Initialize()
{
    return BinaryNode::Initialize();
}
