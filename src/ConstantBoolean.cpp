#include "Node.h"
#include "ConstantBoolean.h"
#include <string>

ConstantBoolean::ConstantBoolean(bool value) : NullaryNode()
{
    this -> value = value;
}
bool ConstantBoolean::GetBoolValue()
{
    return value;
}
bool ConstantBoolean::Initialize() 
{
    type = BOOL_T;
    return true;
}
void ConstantBoolean::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
