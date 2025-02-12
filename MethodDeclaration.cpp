#include "stdafx.h"
#include "Node.h"
#include "MethodDeclaration.h"
#include <string>

const char MethodDeclaration::MISSING_METHOD_ERROR[] = "The method '%s' got error.";

MethodDeclaration::MethodDeclaration(string id, Node* a, Node* b) : BinaryNode(a, b)
{
    this -> id = id;
}
void MethodDeclaration::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    methodEntry = lSymTable -> GetSymbol(id);
    if(methodEntry == NULL)
	Node::ErrorReport(MISSING_METHOD_ERROR, id.c_str());
    BinaryNode::SetSymbolTable(lSymTable, methodEntry -> symbolTable);
}
void MethodDeclaration::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool MethodDeclaration::SemanticCheck()
{
    return BinaryNode::SemanticCheck();
}
bool MethodDeclaration::Initialize()
{
    return BinaryNode::Initialize();
}
Symbol* MethodDeclaration::GetMethodSymbol()
{
    return methodEntry;
}
