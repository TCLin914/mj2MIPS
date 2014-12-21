#pragma once
#include "UnaryNode.h"
#include <string>

using namespace std;

class Println : public UnaryNode
{
public:
    Println(Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
};
