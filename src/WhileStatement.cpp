#include "stdafx.h"
#include "Node.h"
#include "WhileStatement.h"
#include <string>

const char WhileStatement::MISSING_OPERAND_ERROR[] = "Missing while-predicate";
const char WhileStatement::WRONG_TYPE_ERROR[] = "The type of while-predicate must be a boolean value";

WhileStatement::WhileStatement(Node* a, Node* b) : BinaryNode(a, b)
{
}
void WhileStatement::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void WhileStatement::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool WhileStatement::SemanticCheck()
{
    bool result = BinaryNode::SemanticCheck();
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
bool WhileStatement::Initialize()
{
    return BinaryNode::Initialize();
}
