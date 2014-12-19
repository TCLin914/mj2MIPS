#pragma once
#include <vector>
#include <cstdarg>
#include "Type.h"
#include "SymbolTable.h"
#include "Visitor.h"

extern int line_no;
using namespace std;

class Node
{
public:
    virtual bool SemanticCheck() = 0;
    virtual bool Initialize() = 0;
    virtual bool IsAssignable();
    virtual bool IsEvaluable();
    virtual void SetSymbleTable(SymbolTable*, SymbolTable*);
    virtual void Accept(Visitor*) = 0;
    virtual int GetIntValue();
    virtual Type_t GetType();
    int NumberOfChildren();
    Node* GetChild(int);
    Node();
protected:
    virtual void ErrorReport(string, ...);
    SymbolTable* globalSymbleTable;
    SymbolTable* localSymbleTable;
    Type_t type;
    bool isVar;
    vector<Node*> children;
    int lineno;
private:
    static const char GOT_NO_VALUE_EXCEPTION[];
};
int Depth(Node*, int);
