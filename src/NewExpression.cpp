#include "stdafx.h"
#include "Node.h"
#include "NewExpression.h"

NewExpression::NewExpression(string id) : NullaryNode()
{
    this -> id = id;
}
void NewExpression::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
bool NewExpression::Initialize()
{
    type = CLASS_T;
}
