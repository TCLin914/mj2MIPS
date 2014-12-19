#pragma once
#include "ArithmeticOperation.h"

using namespace std;

class Subtract : public ArithmeticOperation
{
public:
    Subtract(Node*, Node*);
    void Accept(Visitor*);
private:
    int AGetIntValue();
};
