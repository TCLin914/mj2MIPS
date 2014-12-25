#include <cstdlib>
#include "stdafx.h"
#include "Node.h"
#include "RelationalOpFactory.h"

RelationalOperation* RelationalOpFactory::CreateRelationalOpNode(OpCode_t op, Node* a, Node* b)
{
    if(op == LESS_THAN_OP)
        return new LessThan(a, b);
    else if(op == AND_OP)
	return new And(a, b);
    else
    {
	printf("RelationalOpFactory error occurs: No such operation");
	system("pause");
	return NULL;
    }
}
