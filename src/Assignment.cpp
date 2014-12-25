#include "stdafx.h"
#include "Node.h"
#include "Assignment.h"
#include <string>

const char Assignment::MISSING_OPERAND_ERROR[] = "The = operator lose (a) operand(s)";
const char Assignment::UNASSIGNABLE_ERROR[] = "The left-hand-side of = operator must be assignable";
const char Assignment::WRONG_TYPE_ERROR[] = "Wrong element type";

Assignment::Assignment(Node* a, Node* b) : BinaryNode(a, b)
{

}
void Assignment::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void Assignment::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool Assignment::SemanticCheck()
{
    bool result = BinaryNode::SemanticCheck();
    if(children[0] == NULL || children[1] == NULL)
    {
        Node::ErrorReport(MISSING_OPERAND_ERROR);
	return false;
    }
    if(!children[0]->IsAssignable())
    {
	Node::ErrorReport(UNASSIGNABLE_ERROR);
	return false;
    }
    if((children[0] -> GetType() != children[1] -> GetType()) || (children[0] -> GetType() != INTEGER_T && children[0] -> GetType() != BOOL_T && children[0] -> GetType() != ARRAY_T))
    {
	Node::ErrorReport(WRONG_TYPE_ERROR);
	return false;
    }
    return result;
}
bool Assignment::Initialize()
{
	return BinaryNode::Initialize();
}
