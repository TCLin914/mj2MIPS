#pragma once
#include "NullaryNode.h"
#include <string>

using namespace std;

class NewExpression : public NullaryNode
{
public:
    NewExpression(string);
    void Accept(Visitor*);
    bool Initialize();
private:
    string id;
};
