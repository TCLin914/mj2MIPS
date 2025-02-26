#pragma once

using namespace std;

class UnaryNode : public Node
{
public:
    UnaryNode(Node*);
    virtual void SetSymbolTable(SymbolTable*, SymbolTable*);
    virtual bool SemanticCheck();
    virtual bool Initialize();
};
