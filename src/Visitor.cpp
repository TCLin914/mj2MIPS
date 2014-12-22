#include "Visitor.h"
#include "Node.h"

void Visitor::SetSymbolTable(SymbolTable* symbolTable)
{
    this -> symbolTable = symbolTable;
}
