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



#define Class 1
#define Public 2
#define Static 3
#define Void 4
#define Main 5
#define String 6
#define Extends 7
#define Return 8
#define Integer 9
#define Boolean 10
#define If 11
#define Else 12
#define While 13
#define Println 14
#define ArrayLength 15
#define True 16
#define False 17
#define This 18
#define And 19
#define New 20
#define Id 21
#define Number 22



extern YYSTYPE yylval;
