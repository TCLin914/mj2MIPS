#include "stdafx.h"
#include "Node.h"
#include "MethodDeclaration.h"
#include <string>

const char MethodDeclaration::MISSING_METHOD_ERROR[] = "The method '%s' got error.";

MethodDeclaration::MethodDeclaration(string id, Node* a, Node* b) : UnaryNode(a, b)
{
    this -> id = id;
}
void MethodDeclaration::SetSymbolTable(SymbolTable* gSymTable, SymbolTable* lSymTable)
{
    methodEntry = gSymTable -> GetSymbol(id);
    if(methodEntry == NULL)
	Node::ErrorReport(MISSING_METHOD_ERROR, id.c_str());
    UnaryNode::SetSymbolTable(gSymTable, methodEntry -> symbolTable);
}
void MethodDeclaration::SetSymbol(Symbol* symbol)
{
    this -> symbol = symbol;
}
Symbol* MethodDeclaration::GetSymbol()
{
    return symbol;
}
void MethodDeclaration::Accept(Visitor* visitor)
{
    visitor->Visit(this);
}
bool MethodDeclaration::SemanticCheck()
{
    return UnaryNode::SemanticCheck();
}
bool MethodDeclaration::Initialize()
{
    return UnaryNode::Initialize();
}
Symbol* MethodDeclaration::GetMethodSymbol()
{
    return methodEntry;
}
