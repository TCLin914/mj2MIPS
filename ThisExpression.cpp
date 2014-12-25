#include "stdafx.h"
#include "Node.h"
#include "ThisExpression.h"

ThisExpression::ThisExpression() : NullaryNode()
{

}
void ThisExpression::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}    
bool ThisExpression::Initialize()
{
    type = CLASS_T;
    return true;
}
