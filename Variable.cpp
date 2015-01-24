#include "stdafx.h"
#include "Node.h"
#include "Variable.h"
#include "ExpressionList.h"
#include <string>
#include "UnaryNode.h"

const char Variable::DIMENSION_ERROR[] = "The dimension of array '%s' is wrong";
const char Variable::UNDECLARED_VARIABLE_ERROR[] = "The variable '%s' wasn't declared";
const char Variable::TYPE_ERROR[] = "The variable '%s' is a array";
const char Variable::INDEX_RANGE_ERROR[] = "The index value '%d' of '%s' is not in it's range";

Variable::Variable(string id, Node* a) : UnaryNode(a)
{
    this -> id = id;
}
void Variable::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    UnaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void Variable::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool Variable::SemanticCheck()
{
    bool result = UnaryNode::SemanticCheck();   
    Node* ptr = children[0];
    
    if(ptr == NULL)
    {
        if((varSymbol -> type != INTEGER_T) && (varSymbol -> type != BOOL_T) && (varSymbol -> type != CLASS_T))
        {
            Node::ErrorReport(TYPE_ERROR, id.c_str());
	    return false;
        }    
    } else 
    {
    
    }     
    /*
    if(ptr -> GetChild(ExpressionList::INDEX_OF_EXPRESSION) != NULL && ptr -> GetChild(ExpressionList::INDEX_OF_EXPRESSION) -> IsEvaluable())
    {
        //a = 5
        //int[a]
        int index = ptr -> GetChild(ExpressionList::INDEX_OF_EXPRESSION) -> GetIntValue();
        if(index > varSymbol -> arraySize)
        {
            Node::ErrorReport(INDEX_RANGE_ERROR, index, id.c_str());
            return false;
        }
    }
    */
    return result;
}
bool Variable::Initialize()
{
    bool result = UnaryNode::Initialize();
    varSymbol = GetSymbol(id);  
    if(varSymbol == NULL)
    {
        Node::ErrorReport(UNDECLARED_VARIABLE_ERROR, id.c_str());
	return false;
    }
    type = varSymbol -> type;
    return result && true;    
}
bool Variable::IsAssignable()
{
    return true;
}
bool Variable::IsLocalVariable()
{
    return localSymbolTable -> GetSymbol(id) != NULL && globalSymbolTable != localSymbolTable;
}
int Variable::ArraySize()
{
    return varSymbol -> arraySize;
}
Symbol* Variable::GetSymbol()
{
    return varSymbol;
}
Symbol* Variable::GetSymbol(string id)
{
    Symbol* symbol = localSymbolTable -> GetSymbol(id);
    if(symbol == NULL)
        symbol = globalSymbolTable -> GetSymbol(id);
    return symbol;
}
