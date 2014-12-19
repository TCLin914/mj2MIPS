#pragma once
#include <vector>
#include "Type.h"
#include "Symbol.h"

using namespace std;

class Symbol;

class SymbolTable
{
public:
    bool Insert(Symbol*);
    bool INsert(vector<Symbol*>*);
    Symbol* GetSymbol(int);
    Symbol* GetSymbol(string);
    int Size();
private:
    int Rank(string);
    vector<Symbol*> symbols;
    static const char DUPLICATED_SYMBOL_ERROR[];
};
bool InsertInto(SymbolTable*, SymbolTable*);
bool Initialize(SymbolTable*);
