#pragma once
#include "ArithmeticOperation.h"

using namespace std;

class Add : public ArithmeticOperation
{
public:
    Add(Node*, Node*);
    void Accept(Visitor*);
private:
    int AGetIntValue();
};
