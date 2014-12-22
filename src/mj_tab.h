#include "YaccCompatible.h"

using namespace std;

typedef union {
    int tokenval;
    char* tokenstr;
    OpCode_t opCode;
    vector<Symbol*>* symbolList;
    Symbol* symbol;
    Type_t type_t;
    SymbolTable* symbolTable;
    Node* node;
} YYSTYPE;

extern YYSTYPE yylval;
