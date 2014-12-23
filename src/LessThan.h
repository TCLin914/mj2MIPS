#pragma once
#include "RelationalOperation.h"

using namespace std;

class LessThan : public RelationalOperation
{
public:
    LessThan(Node*, Node*);
    void Accept(Visitor*);
};
