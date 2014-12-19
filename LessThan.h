#pragma once
#include "RelationalOperation.h"

using namespace std;

class LessThan : public RelationalOperator
{
public:
    LessThan(Node*, Node*);
    void Accept(Visitor*);
};
