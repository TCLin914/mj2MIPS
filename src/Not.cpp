#include "stdafx.h"
#include "Node.h"
#include "Not.h"
#include <string>

const char Not::MISSING_OPERAND_ERROR[] = "The NOT operator lose a operand";
const char Not::WRONG_TYPE_ERROR[] = "The element must be a boolean value following NOT operator";

Not::Not(Node* a) : UnaryNode(a)
{

}
void Not::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    UnaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void Not::Accept(Visitor* visitor)
{
    visitor->Visit(this);
}
bool Not::SemanticCheck()
{
    bool result = UnaryNode::SemanticCheck();
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
bool Not::Initialize()
{
	type = BOOL_T;
	return UnaryNode::Initialize();
}
