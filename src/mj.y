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
#include "Type.h"
// Binary node
#include "Add.h"
#include "Subtract.h"
#include "Multiply.h"
#include "And.h" 
#include "LessThan.h"
#include "Assignment.h"
#include "ClassDeclarationList.h"
#include "MethodDeclarationList.h"
#include "StatementList.h"
// Unary node
#include "Not.h" 
#include "Println.h"
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

SymbolTable yySymbolTable = SymbolTable();
Node* yyHeader = NULL;

vector<Symbol*> SetAllType(Symbol*, vector<Symblo*>*);
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
    :   ClassDeclaration ClassDeclarationList {$$ = new ClassDeclarationList($1, $2);}
    |   {$$ = NULL;}
    ;

ClassDeclaration
    :   Class Identifier '{' VarDeclarationList MethodDeclarationList '}'
    |   Class Identifier '{' MethodDeclarationList '}'
    |   Class Identifier Extends Identifier '{' VarDeclarationList MethodDeclarationList '}'
    |   Class Identifier Extends Identifier '{' MethodDeclarationList '}'
    ;

VarDeclarationList
    :   VarDeclaration 
        {
	    SymbleTable* varSymbolTable = new SymbolTable();
	    yyIntegratedSymbolTable &= varSymbolTable -> Insert($1);  /* SymbleTable::Insert(Symbol* symbol) */
	    $$ = varSymbolTable;
	}
    |   VarDeclarationList VarDeclaration 
        {
	    SymbleTable* varSymbolTable = $1;
            yyIntegratedSymbolTable &= varSymbolTable -> Insert($2);  
	    $$ = varSymbolTable;
	}
    ;	

VarDeclaration
    :   Type Identifier ';' {$$ = new Symbol($2, $1, line_no);}  /* Symbol::Symbol(string id, Type_t type, int declaredLine) */
    ;

MethodDeclarationList
    :   MethodDeclaration MethodDeclarationList {$$ = new MethodDeclarationList($1, $2);}
    |   {$$ = NULL;}
    ;

MethodDeclaration
    :   Public Type Identifier '(' ParameterList ')' '{' VarDeclarationList StatementList Return Expression ';' '}'
        {
            yyIntegratedSymbolTable &= ($8) -> Insert(new Symbol($3, $2, line_no)); // Insert symbol(string method_name, Type_t return_type, int declaredLine) to VarDeclarationList(SymbolTable)
            yyIntegratedSymbolTable &= ($8) -> Insert($5); // Insert vector<Symbol*>* to VarDeclarationList(symbolTable)
            
            $$ = MethodDeclaration($3, $9); // (Indentifier, StatementList)
	}
    |   Public Type Identifier '(' ParameterList ')' '{' StatementList Return Expression ';' '}'
    ;

ParameterList
    :   Type Identifier 
        {
	    vector<Symbol*>* para = new vector<Symbol*>();
	    (*para).push_back(new Symbol($2, $1, line_no);
	    $$ = para;
	} 
    |   Type Identifier ',' ParameterList 
        {
            vector<Symbol*>* para = $4;
	    (*para).push_back(new Symbol($2, $1, line_no);
	    $$ = para;
	}
    |   {$$ = NULL;}
    ;

Type
    :   Integer '[' ']'
    |   Boolean {$$ = BOOL_T}  /* {$$ = new Symbol("", BOOL_T);} */
    |   Integer {$$ = INTEGER_T}  /* {$$ = new Symbol("", INTEGER_T);} */
    |   Identifier // TODO
    ;

StatementList
    :   Statement StatementList {$$ = new StatementList($1, $2);}
    |   {$$ = NULL;}	
    ;

Statement
    :   '{' StatementList '}' {$$ = $2;}
    |   If '(' Expression ')' Statement Else Statement {$$ = new IfStatement($3, $5, $7);}
    |   While '(' Expression ')' Statement {$$ = new WhileStatement($3, $5);}
    |   Println '(' Expression ')' ';' {$$ = new Println($3);}
    |   Identifier '=' Expression ';' {$$ = new Assingment($1, $3);}
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
    |   Number {$$ = $1;}
    |   True 
    |   False
    |   Identifier 
    |   This
    |   New Integer '[' Expression ']'
    |   New Identifier '(' ')'
    |   '!' Expression {$$ = new Not($2);}
    |   '(' Expression ')' {$$ = $2;}
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
    return symbols;
}
void yyerror(char *s) {
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

int main(void) {
    yyparse();
    return 0;
}
