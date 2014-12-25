#pragma once

using namespace std;

class TernaryNode : public Node
{
public:
    TernaryNode(Node*, Node*, Node*);
    virtual void SetSymbolTable(SymbolTable*, SymbolTable*);
    virtual bool SemanticCheck();
    virtual bool Initialize();
};
