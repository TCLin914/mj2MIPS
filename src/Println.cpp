#include "stdafx.h"
#include "Node.h"
#include "Println.h"
#include <string>

Println::Println(Node* a) : UnaryNode(a)
{

}
void Println::SetSetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    UnaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void Println::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool Println::SemanticCheck()
{
    return UnaryNode::SemanticCheck();
}
bool Println::Initialize()
{
    return UnaryNode::Initialize();
}
