#pragma once
#include "Add.h"
#include "Multiply.h"
#include "Subtract.h"
#include "OpCode.h"

using namespace std;

class ArithmeticOpFactory
{
public:
    static ArithmeticOperation* CreateArithmeticOpNode(OpCode_t, Node*, Node*);
};
