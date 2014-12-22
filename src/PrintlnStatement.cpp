#include "stdafx.h"
#include "Node.h"
#include "PrintlnStatement.h"
#include <string>

PrintlnStatement::PrintlnStatement(Node* a) : UnaryNode(a)
{

}
void PrintlnStatement::SetSetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    UnaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void PrintlnStatement::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool PrintlnStatement::SemanticCheck()
{
    return UnaryNode::SemanticCheck();
}
bool PrintlnStatement::Initialize()
{
    return UnaryNode::Initialize();
}
