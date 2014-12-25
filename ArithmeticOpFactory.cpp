#include <cstdlib>
#include "stdafx.h"
#include "Node.h"
#include "ArithmeticOpFactory.h"

ArithmeticOperation* ArithmeticOpFactory::CreateArithmeticOpNode(OpCode_t op, Node* a, Node* b)
{
    if(op == ADD_OP)
	return new Add(a, b);
    else if(op == SUBTRACT_OP)
	return new Subtract(a, b);
    else if(op == MULTIPLY_OP)
	return new Multiply(a, b);
    else
    {
	printf("ArithmeticOpFactory error occurs: No such operation");
	system("pause");
	return NULL;
    }
}
