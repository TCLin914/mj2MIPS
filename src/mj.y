%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cstdlib>
#include <vector>
#include <string>
#include "stdafx.h"
#include "Node.h"
#include "OpCode.h"
// Binary node
#include "Add.h"
#include "Subtract.h"
#include "Multiply.h"
#include "And.h" 
#include "LessThan.h"
#include "Assignment.h"
// Unary node
#include "Not.h" 
// Ternary node
#include "IfStatement.h"
#include "WhileStatement.h"
// Factory 
#include "ArithmeticOpFactory.h"
#include "RelationalOpFactory.h"

#include "Symbol.h"
#include "SymbolTable.h"


extern char yytext[];
extern int column;
extern int yylineno;

int yylex(void);
void yyerror(char *s);
%}

%token Class
%token Public
%token Static
%token Void
%token Main
%token String
%token Extend
%token Return
%token Integer
%token Boolean
%token If
%token Else
%token While
%token Println
%token ArrayLength
%token True
%token False
%token This
%token And
%token New
%token Id
%token Number

%right '='
%left '{'
%left '['
%left And
%left '+' '-'
%left '*'
%left '.'
%left '!'
%nonassoc '<'

%start Goal

%type <node> Goal
%type 


%%
Goal
    :   MainClass ClassDeclarationList      { printf("OK\n"); }
    ;

MainClass
    :   Class Identifier '{' Public Static Void Main '(' String '[' ']' Identifier ')' '{' Statement '}' '}'
    ;

ClassDeclarationList
    :   ClassDeclaration ClassDeclarationList
    |   /* Empty */
    ;

ClassDeclaration
    :   Class Identifier '{' VarDeclarationList MethodDeclarationList '}'
    |   Class Identifier '{' MethodDeclarationList '}'
    |   Class Identifier Extends Identifier '{' VarDeclarationList MethodDeclarationList '}'
    |   Class Identifier Extends Identifier '{' MethodDeclarationList '}'
    ;

VarDeclarationList
    :   VarDeclaration
    |   VarDeclarationList VarDeclaration
    ;

VarDeclaration
    :   Type Identifier ';'
    ;

MethodDeclarationList
    :   MethodDeclaration MethodDeclarationList
    |   /* Empty */
    ;

MethodDeclaration
    :   Public Type Identifier '(' ParameterList ')' '{' VarDeclarationList StatementList Return Expression ';' '}'
    |   Public Type Identifier '(' ParameterList ')' '{' StatementList Return Expression ';' '}'
    ;

ParameterList
    :   Type Identifier
    |   Type Identifier ',' ParameterList
    |   /* Empty */
    ;

Type
    :   Integer '[' ']'
    |   Boolean
    |   Integer
    |   Identifier
    ;

StatementList
    :   Statement StatementList
    |   /* Empty */
    ;

Statement
    :   '{' StatementList '}'
    |   If '(' Expression ')' Statement Else Statement
    |   While '(' Expression ')' Statement
    |   Println '(' Expression ')' ';'
    |   Identifier '=' Expression ';'
    |   Identifier '[' Expression ']' '=' Expression ';'
    ;

ExpressionList
    :   Expression {$$ = $1}
    |   Expression ',' ExpressionList
    |   /* Empty */
    ;

Expression
    :   Expression And Expression {$$ = RelationalOpFactory::CreateRelationalOpNode(AND_OP, $1, $3);}
    |   Expression '<' Expression {$$ = RelationalOpFactory::CreateRelationalOpNode(LESS_THAN_OP, $1, $3);}
    |   Expression '+' Expression {$$ = RelationalOpFactory::CreateRelationalOpNode(ADD_OP, $1, $3);}
    |   Expression '-' Expression {$$ = RelationalOpFactory::CreateRelationalOpNode(SUBTRACT, $1, $3);}
    |   Expression '*' Expression {$$ = RelationalOpFactory::CreateRelationalOpNode(MULTIPLY_OP, $1, $3);}
    |   Expression '[' Expression ']'
    |   Expression '.' ArrayLength
    |   Expression '.' Identifier '(' ExpressionList ')'
    |   Number
    |   True
    |   False
    |   Identifier
    |   This
    |   New Integer '[' Expression ']'
    |   New Identifier '(' ')'
    |   '!' Expression
    |   '(' Expression ')'
    ;

Identifier
    :   Id
    ;

%%
vector<Symbol*>* SetAllType(Symbol* type, vector<Symbol*>* symbols)
{
    for(int i = 0; i < symbols -> size(); i++)
    {
        (*symbols)[i] -> type = type -> type;
	(*symbols)[i] -> dimensions = type -> dimensions;
}
void yyerror(char *s) {
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

int main(void) {
    yyparse();
    return 0;
}
