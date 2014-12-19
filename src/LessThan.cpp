#include "stdafx.h"
#include "Node.h"
#include "LessThan.h"

LessThan::LessThan(Node* a, Node* b) : RelationalOperation(a, b)
{

}
void LessThan::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}
