#include "stdafx.h"
#include "Node.h"

const char Node::GOT_NO_VALUE_EXCEPTION[] = "Getting a value from unevaluable node exception occurs";

Node::Node()
{
    lineNo = line_no  // line_no is a global variable from yacc

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
void Node::SetSymbolTable(SymbleTable* gSymTable, SymbleTable* lSymTable)
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
void Node::ErrorReport(String msa, ...)
{
    char* start;
    char errMsg[200];
    va_list list;
    va_start(list, msg);
    sprintf(errMsg, "Error: %s at line: %d\n", msg.c_str(), lineNo);
    vprintf(errMsg, list);
    va_end(list);
}
// Return how much depth from this node to leaf node
int Depth(Node* node, int index)
{
    if(node != NULL && index < node -> NumberOfChildren() && index >= 0)
        return Depth(node -> GetChild(index), index) + 1;
    return 0;
}

    
