#pragma once
#include <vector>
#include <string>
#include "Type.h"
#include "ArrayRange.h"
#include "SymbolTable.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/DerivedTypes.h"

using namespace std;

class SymbolTable;

class Symbol
{
public:
    Symbol(string, Type_t);
    Symbol(string, Type_t, int);
    string id;
    Type_t type;
    //int maxIndex;
    vector<Symbol*>* parameters;
    SymbolTable* variables;
    
    int arraySize;
    llvm::StructType* structType;
    
    SymbolTable* symbolTable;
    int declaredLine;
    llvm::Value* value;
private:
    //int[] array;
};
