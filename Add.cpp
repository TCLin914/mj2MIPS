#include "stdafx.h"
#include "Node.h"
#include "Add.h"

Add::Add(Node* a, Node* b) : ArithmeticOperation(a, b)
{

}
int Add::AGetIntValue()
{
    return children[0] -> GetIntValue() + children -> GetIntValue();
}
void Add::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
