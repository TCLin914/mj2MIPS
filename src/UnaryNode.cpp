#include "stdafx.h"
#include "Node.h"
#include "UnaryNode.h"

UnaryNode::UnaryNode(Node* a) : node()
{
    children.push_back(a);
}
void UnaryNode::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    Node::SetSymbolTable(gSymTable, lSymTable);
    if(children[0] != NULL)
        children[0] -> SetSymbolTable(gSymTable, lSymTable);
}
bool UnaryNode::SemanticCheck()
{
    if(children[0] != NULL)
        return children[0] -> SemanticCheck();
    return true;
}
bool UnaryNode::Initialize()
{
    if(children[0] != NULL)
        return children[0] -> Initialize();
    return true;
}
