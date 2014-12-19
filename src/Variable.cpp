#include "stdafx.h"
#include "Node.h"
#include "Variable.h"
#include "ExpressionList.h"
#include <string>
#include "BinaryNode.h"

const char Variable::DIMENSION_ERROR[] = "The dimension of array '%s' is wrong";
const char Variable::UNDECLARED_VARIABLE_ERROR[] = "The variable '%s' wasn't declared";
const char Variable::INDEX_TYPE_ERROR[] = "The index of '%s' must be a integer value";
const char Variable::INDEX_RANGE_ERROR[] = "The index value '%d' of '%s' is not in it's range";

Variable::Variable(string id, Node* a): UnaryNode(a)
{
	this->id = id;
}
void Variable::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
	UnaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void Variable::Accept(Visitor* visitor)
{
    visitor->Visit(this);
}
bool Variable::SemanticCheck()
{
	bool result = UnaryNode::SemanticCheck();
	Node* ptr = children[0];
	if(varSymbol->dimensions.size() < Depth(children[0], ExpressionList::INDEX_OF_MORE))
	{
		Node::ErrorReport(DIMENSION_ERROR, id.c_str());
		return false;
	}
	for(int i = 0; ptr != NULL; ptr = ptr->GetChild(ExpressionList::INDEX_OF_MORE), i++)
	{
		if(ptr->GetType() != INTEGER_T)
		{
			Node::ErrorReport(INDEX_TYPE_ERROR, id.c_str());
			return false;
		}
		if(ptr->GetChild(ExpressionList::INDEX_OF_EXPRESSION) != NULL && ptr->GetChild(ExpressionList::INDEX_OF_EXPRESSION)->IsEvaluable())
		{
			int index = ptr->GetChild(ExpressionList::INDEX_OF_EXPRESSION)->GetIntValue();
			if(index > varSymbol->dimensions[i].max || index < varSymbol->dimensions[i].min)
			{
				Node::ErrorReport(INDEX_RANGE_ERROR, index, id.c_str());
				return false;
			}
		}
	}
	return result;
}
bool Variable::Initialize()
{
	bool result = UnaryNode::Initialize();
	varSymbol = GetSymbol(id);
	if(varSymbol != NULL)
	{
		Node* ptr = children[0];
		int depth = Depth(ptr, ExpressionList::INDEX_OF_MORE);
		if(depth < varSymbol->dimensions.size())
			type = ARRAY_T;
		else
			type = varSymbol->type;
		return result;
	}
	else
	{
		Node::ErrorReport(UNDECLARED_VARIABLE_ERROR, id.c_str());
		return false;
	}
}
bool Variable::IsAssignable()
{
	return true;
}
bool Variable::IsLocalVariable()
{
    return localSymbolTable->GetSymbol(id) != NULL && globalSymbolTable != localSymbolTable;
}
int Variable::Dimensions()
{
    return varSymbol->dimensions.size();
}
Symbol* Variable::GetSymbol()
{
    return varSymbol;
}
Symbol* Variable::GetSymbol(string id)
{
	Symbol* symbol = localSymbolTable->GetSymbol(id);
	if(symbol == NULL)
		symbol = globalSymbolTable->GetSymbol(id);
	return symbol;
}
