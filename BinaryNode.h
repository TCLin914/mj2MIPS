

using namespace std;

class BinaryNode : public Node
{
public: 
    BinaryNode(Node*, Node*);
    virtual void SetSymbolTable(SymbolTable*, SymbolTable*);
    virtual bool SemanticCheck();
    virtual bool Initialize();
protected:
};
