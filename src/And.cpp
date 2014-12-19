#include "stdafx.h"
#include "Node.h"
#include "And.h"

And::And(Node* a, Node* b) : RelationalOperation(a, b)
{

}
void And::Accept(Visitor* visitor)
{
    visitor -> Visit(this);
}

