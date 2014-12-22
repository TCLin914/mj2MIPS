#pragma once
#include "SymbolTable.h"

class Node;
class ClassDeclarationList;
class MethodDeclarationList;
class MethodDeclaration;
class StatementList;
class Assignment;
class And;
class LessThan;
class Add;
class Subtract;
class Multiply;
class Not;
class Println;
class IfStatement;
class WhileStatement;

using namespace std;

class Visitor
{
public:
    virtual void Visit(ClassDeclarationList*) = 0;
    virtual void Visit(MethodDeclarationList*) = 0;
    virtual void Visit(MethodDeclaration*) = 0;
    virtual void Visit(StatementList*) = 0;
    virtual void Visit(Assignment*) = 0;
    virtual void Visit(And*) = 0;
    virtual void Visit(LessThan*) = 0;
    virtual void Visit(Add*) = 0;
    virtual void Visit(Subtract*) = 0;
    virtual void Visit(Multiply*) = 0;
    virtual void Visit(Not*) = 0;
    virtual void Visit(Println*) = 0;
    virtual void Visit(IfStatement*) = 0;
    virtual void Visit(WhileStatement*) = 0;

    virtual void SetSymbolTable(SymbolTable*);
protected:
    SymbolTable* symbolTable;
private:
};
