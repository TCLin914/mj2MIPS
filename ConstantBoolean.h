#pragma once
#include "NullaryNode.h"
#include <string>

using namespace std;

class ConstantBoolean : public NullaryNode
{
public:
    ConstantBoolean(bool);
    bool GetBoolValue();
    bool Initialize();
    void Accept(Visitor*);
private:
    bool value;
};
