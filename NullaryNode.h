#pragma once

using namespace std;

class NullaryNode : public Node
{
public: 
    NullaryNode();
    virtual bool SemanticCheck();
    virtual bool IsEvaluable();
};
