#pragma once
#include "RelationalOperation.h"

using namespace std;

class And : public RelationalOperation
{
public:
    And(Node*, Node*);
    void Accept(Visitor*);
};
