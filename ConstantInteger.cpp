#include "stdafx.h"
#include "Node.h"
#include "ConstantInteger.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

ConstantInteger::ConstantInteger(string num) : NullaryNode()
{
    this -> num = atoi(num.c_str());
}
int ConstantInteger::GetIntValue()
{
    return num;
}
bool ConstantInteger::Initialize()
{
    type = INTEGER_T;
    return true;
}
void ConstantInteger::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
