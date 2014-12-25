#pragma once
#include "ArithmeticOperation.h"

using namespace std;

class Multiply : public ArithmeticOperation
{
public:
    Multiply(Node*, Node*);
    void Accept(Visitor*);
private:
    int AGetIntValue();
};
