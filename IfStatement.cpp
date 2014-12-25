#include "stdafx.h"
#include "Node.h"
#include "IfStatement.h"
#include <string>

const char IfStatement::MISSING_OPERAND_ERROR[] = "Missing if-predicate";
const char IfStatement::WRONG_TYPE_ERROR[] = "The type of if-predicate must be a boolean value";

IfStatement::IfStatement(Node* a, Node* b, Node* c) : TernaryNode(a, b, c)
{

}
void IfStatement::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    Node::SetSymbolTable(gSymTable, lSymTable);
    TernaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void IfStatement::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool IfStatement::SemanticCheck()
{
    bool result = TernaryNode::SemanticCheck();
    if(children[0] == NULL)
    {
	Node::ErrorReport(MISSING_OPERAND_ERROR);
	return false;
    }
    if(children[0] -> GetType() != BOOL_T)
    {
	Node::ErrorReport(WRONG_TYPE_ERROR);
	return false;
    }
    return result;
}
bool IfStatement::Initialize()
{
    return TernaryNode::Initialize();
}
