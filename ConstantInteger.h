#pragma once
#include "NullaryNode.h"
#include <string>

using namespace std;

class ConstantInteger : public NullaryNode
{
public:
    ConstantInteger(string);
    int GetIntValue();
    bool Initialize();
    void Accept(Visitor*);
private:
    int num;
};
