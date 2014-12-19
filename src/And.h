#pragma once
#include "RelationalOperation.h"

using namespace std;

class And : public RelationalOperator
{
public:
    And(Node*, Node*);
    void Accept(Visitor*);
};
