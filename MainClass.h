#pragma once
#include "UnaryNode.h"
#include <string>

using namespace std;

class MainClass : public UnaryNode
{
public:
    MainClass(string, Node*);
    void SetSymbolTable(SymbolTable*, SymbolTable*);
    void Accept(Visitor*);
    bool SemanticCheck();
    bool Initialize();
    //Symbol* GetMainClassSymbol();
private:
    //Symbol* mainclassEntry;
    string id;
    static const char MISSING_MAIN_CLASS_ERROR[];
};
