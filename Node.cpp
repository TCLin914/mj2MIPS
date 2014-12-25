#include "stdafx.h"
#include "Node.h"

const char Node::GOT_NO_VALUE_EXCEPTION[] = "Getting a value from unevaluable node exception occurs";

extern int line_no;

Node::Node()
{
    lineNo = line_no;  // line_no is a global variable from yacc
}
Type_t Node::GetType()
{
    return type;
}
bool Node::IsAssignable()
{
    return false;
}
bool Node::IsEvaluable()
{
    return false;
}
void Node::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    globalSymbolTable = gSymTable;
    localSymbolTable = lSymTable;
}
int Node::GetIntValue()
{
    throw new exception();
}
int Node::NumberOfChildren()
{
    return children.size();
}
Node* Node::GetChild(int index)
{
    return children[index];
}
void Node::ErrorReport(string msg, ...)
{
    char* start;
    char errMsg[200];
    va_list list;
    va_start(list, msg);
    sprintf(errMsg, "Error: %s at line: %d\n", msg.c_str(), lineNo);
    vprintf(errMsg, list);
    va_end(list);
}
void Node::SetSymbol(Symbol* symbol)
{
    this -> symbol = symbol;
}
Symbol* Node::GetSymbol()
{
    return symbol;
}
SymbolTable* Node::GetMethodsSymbolTable()
{
    return methodsSymbolTable;
}
void Node::SetMethodsSymbolTable(SymbolTable* symbolTable)
{
    this -> methodsSymbolTable = symbolTable;
}
// Return how much depth from this node to leaf node
int Depth(Node* node, int index)
{
    if(node != NULL && index < node -> NumberOfChildren() && index >= 0)
        return Depth(node -> GetChild(index), index) + 1;
    return 0;
}

    
