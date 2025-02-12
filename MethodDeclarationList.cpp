#include "stdafx.h"
#include "Node.h"
#include "MethodDeclarationList.h"
#include <string>

MethodDeclarationList::MethodDeclarationList(Node* a, Node* b) : BinaryNode(a, b)
{

}
void MethodDeclarationList::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void MethodDeclarationList::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool MethodDeclarationList::SemanticCheck()
{
    return BinaryNode::SemanticCheck();
}
bool MethodDeclarationList::Initialize()
{
    return BinaryNode::Initialize();
}

