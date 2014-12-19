
using namespace std;

class UnaryNode : public Node
{
public:
    UnaryNode(Node*);
    virtual void SetSymbleTable(symbolTable*, SymbolTable*);
    virtual bool SemanticCheck();
    virtual bool Initialize();
};
