#include "stdafx.h"
#include "Node.h"
#include "ArrayAssignment.h"

const char ArrayAssignment::MISSING_OPERAND_ERROR[] = "The = operator lose (a) operand(s).";
const char ArrayAssignment::UNASSIGNABLE_ERROR[] = "The left-hand-side of = operator must be assignable.";
const char ArrayAssignment::WRONG_TYPE_ERROR[] = "Wrong element type.";
const char ArrayAssignment::OUT_OF_INDEX_ERROR[] = "Out of array index error.";
const char ArrayAssignment::MISSING_ARRAY_INDEX[] = "Miss index of array.";

ArrayAssignment::ArrayAssignment(Node* a, Node* b, Node* c) : TernaryNode(a, b, c)
{

}
void ArrayAssignment::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    TernaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void ArrayAssignment::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool ArrayAssignment::SemanticCheck()
{
    bool result = TernaryNode::SemanticCheck();
    if(children[0] == NULL || children[2] == NULL)
    {
        Node::ErrorReport(MISSING_OPERAND_ERROR);
	return false;
    }
    if(children[1] == NULL)
    {
        Node::ErrorReport(MISSING_ARRAY_INDEX);
	return false;
    }
    if(!children[0] -> IsAssignable())
    {
        Node::ErrorReport(UNASSIGNABLE_ERROR);
        return false;
    }
    if(children[3] -> GetType() != INTEGER_T)
    {
        Node::ErrorReport(WRONG_TYPE_ERROR);
	return false;    
    }
    return result;
}
bool ArrayAssignment::Initialize()
{
    return TernaryNode::Initialize();
}
