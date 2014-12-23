#pragma once
#include "LessThan.h"
#include "And.h"
#include "OpCode.h"

using namespace std;

class RelationalOpFactory
{
public:
    static RelationalOperation* CreateRelationalOpNode(OpCode_t, Node*, Node*);
protected:
};
