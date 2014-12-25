#include "stdafx.h"
#include "Node.h"
#include "TernaryNode.h"

TernaryNode::TernaryNode(Node* a, Node* b, Node* c): Node()
{
    children.push_back(a);
    children.push_back(b);
    children.push_back(c);
    type = UNDEFINED;
}
void TernaryNode::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    if(children[0] != NULL)
        children[0] -> SetSymbolTable(gSymTable, lSymTable);
    if(children[1] != NULL)
	children[1] -> SetSymbolTable(gSymTable, lSymTable);
    if(children[2] != NULL)
	children[2] -> SetSymbolTable(gSymTable, lSymTable);
}
bool TernaryNode::SemanticCheck()
{
    bool result = true;
    if(children[0] != NULL)
	result &= children[0] -> SemanticCheck();
    if(children[1] != NULL)
	result &= children[1] -> SemanticCheck();
    if(children[2] != NULL)
	result &= children[2] -> SemanticCheck();
    return result;
}
bool TernaryNode::Initialize()
{
    bool result = true;
    if(children[0] != NULL)
	result &= children[0] -> Initialize();
    if(children[1] != NULL)
	result &= children[1] -> Initialize();
    if(children[2] != NULL)
	result &= children[2] -> Initialize();
    return result;
}
