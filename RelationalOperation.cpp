#include <cstdlib>
#include "stdafx.h"
#include "Node.h"
#include "RelationalOperation.h"

const char RelationalOperation::MISSING_OPERAND_ERROR[] = "The arithmetic operator lose (an) operand(s)";
const char RelationalOperation::WRONG_TYPE_ERROR[] = "Wrong element type";

RelationalOperation::RelationalOperation(Node* a, Node* b) : BinaryNode(a, b)
{

}
void RelationalOperation::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);
}
bool RelationalOperation::SemanticCheck()
{
    bool result = BinaryNode::SemanticCheck();
    if(children[0] == NULL || children[1] == NULL)
    {
        Node::ErrorReport(MISSING_OPERAND_ERROR);
	return false;
    }
    // Check whether type of two operands is equal and the type is integer.
    if((children[0] -> GetType() != children[1] -> GetType()) || (children[0] -> GetType() !=INTEGER_T))
    {
        Node::ErrorReport(WRONG_TYPE_ERROR);
	return false;
    }
    return result;
}
bool RelationalOperation::Initialize()
{
    type = BOOL_T;
    return BinaryNode::Initialize();
}
bool RelationalOperation::IsEvaluable()
{
    if(children[0] != NULL && children[1] != NULL)
        return children[0] -> IsEvaluable() && children[1] -> IsEvaluable();
    return false;
}
