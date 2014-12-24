#include "stdafx.h"
#include "Node.h"
#include "FunctionCall.h"
#include "ExpressionList.h"
#include <string>

const char FunctionCall::UNDECLARED_FUNCTION_ERROR[] = "The function '%s' wasn't declared";
const char FunctionCall::NOT_FUNCTION_ERROR[] = "The '%s' isn't a function";
const char FunctionCall::UNDECLARED_CLASS_ERROR[] = "The class '%s' wasn't declared";
const char FunctionCall::NOT_CLASS_ERROR[] = "The '%s' isn't a class";

const char FunctionCall::ARGS_TYPE_ERROR[] = "The arguments of the function/procedure '%s' do not match its prototype";
const char FunctionCall::TOO_FEW_ARGS_ERROR[] = "The function/procedure call '%s' is too few arguments";
const char FunctionCall::TOO_MANY_ARGS_ERROR[] = "The function/procedure call '%s' is too many arguments";

FunctionCall::FunctionCall(Node* a, string id, Node* b): BinaryNode(a, b)
{
    this -> id = id;
}
void FunctionCall::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    BinaryNode::SetSymbolTable(gSymTable, lSymTable);
}
void FunctionCall::Accept(Visitor* visitor)
{
    visitor->Visit(this);
}
bool FunctionCall::SemanticCheck()
{
    bool result = BinaryNode::SemanticCheck();
    if(funcSymbol == NULL)
    {
        Node::ErrorReport(UNDECLARED_ERROR, id.c_str());
        return false;
    }
    else
    {
        if(funcSymbol -> symbolTable == NULL)
        {
            Node::ErrorReport(UNDECLARED_FUNCTION_ERROR, id.c_str());
            return false;
        }
        Node* ptr = children[1]; // expressionList (parameters)  
        for(int i = 0; i < (funcSymbol -> parameters) -> size(); i++, ptr -> GetChild(ExpressionList::INDEX_OF_MORE))	
        {
            if(ptr == NULL)
            {
                Node::ErrorReport(TOO_FEW_ARGS_ERROR, id.c_str());
	        return false;
            }
            if(ptr -> GetType() != (*(funcSymbol -> parameters))[i] -> type)
            {
                Node::ErrorReport(ARGS_TYPE_ERROR, id.c_str());
	        return false;
	    }
	}
	if(ptr != NULL)
	{
	    Node::ErrorReport(TOO_MANY_ARGS_ERROR, id.c_str());
	    return false;
	}    
    }
    return result;    
}
bool FunctionCall::Initialize()
{
    bool result = BinaryNode::Initialze();
    classSymbol = globalSymbolTable -> GetSymbol(children[0] -> id) // Get class symbol from globalSymbolTable
    if(classSymbol != NULL)
    {
        if(classSymbol -> symbolTable == NULL)
        {
            Node::ErrorReport(NOT_CLASS_ERROR, id.c_str());
	    return false;        
        }
        funcSymbol = (classSymbol -> symbolTable) -> GetSymbol(id);
        if(funcSymbol != NULL)
        {
            type -> funcSymbol -> type;
            return result;
        }
        else
        {
            Node::ErrorReport(UNDECLARED_FUNCTION_ERROR, id.c_str());
            return false;
        }    
    }   
    else
    {
        Node::ErrorReport(UNDECLARED_CLASS_ERROR, id.c_str());
        return false;    
    }
}
Symbol* FunctionCall:GetClassSymbol()
{
    return classSymbol;
}
Symbol* FunctionCall::GetFuncSymbol()
{
    return funcSymbol;
}

