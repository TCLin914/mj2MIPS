#pragma once
#include <vector>
#include <cstdarg>
#include "Type.h"
#include "SymbolTable.h"
#include "Visitor.h"
// #include <string>

extern int line_no;
using namespace std;

class Node
{
public:
    virtual bool SemanticCheck() = 0;
    virtual bool Initialize() = 0;
    virtual bool IsAssignable();
    virtual bool IsEvaluable();
    virtual void SetSymbolTable(SymbolTable*, SymbolTable*);
    virtual void Accept(Visitor*) = 0;
    virtual int GetIntValue();
    virtual Type_t GetType();
    int NumberOfChildren();
    Node* GetChild(int);
    Node();    
    
    void SetMethodsSymbolTable(SymbolTable*);
    SymbolTable* GetMethodsSymbolTable();
    void SetSymbol(Symbol*);
    Symbol* GetSymbol();

protected:
    virtual void ErrorReport(string, ...);
    SymbolTable* globalSymbolTable;
    SymbolTable* localSymbolTable;
    Type_t type;
    bool isVar;
    vector<Node*> children;
    int lineNo;   
   

private:
    static const char GOT_NO_VALUE_EXCEPTION[];
    
    Symbol* symbol;
    SymbolTable* methodsSymbolTable;
};
int Depth(Node*, int);
