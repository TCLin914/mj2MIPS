#include "stdafx.h"
#include "Node.h"
#include "Subtract.h"

Subtract::Subtract(Node* a, Node* b) : ArithmeticOperation(a, b)
{

}
int Subtract::AGetIntValue()
{
    return children[0] -> GetIntValue() - children[1] -> GetIntValue();
}
void Subtract::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
