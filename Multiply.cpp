#include "stdafx.h"
#include "Node.h"
#include "Multiply.h"

Multiply::Multiply(Node* a, Node* b) : ArithmeticOperation(a, b)
{

}
int Multiply::AGetIntValue()
{
    return children[0] -> GetIntValue() * children[1] -> GetIntValue();
}
void Multiply::Accept(Visitor visitor)
{
    visitor -> Visit(this);
}
