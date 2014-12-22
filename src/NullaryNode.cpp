#include "stdafx.h"
#include "Node.h"
#include "NullaryNode.h"

NullaryNode::NullaryNode() : Node()
{
    type = UNDEFINED;
}
bool NullaryNode::SemanticCheck()
{
    return true;
}
bool NullaryNode::IsEvaluable()
{
    return true;
}
