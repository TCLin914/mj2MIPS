%{
#include <stdio.h>
// #include "y.tab.h"
#include "mj_tab.h"
int line_no;
void count();

extern void yyerror(char const *s);
extern YYSTYPE yylval;
#define yylex yylexical
char const *unknown = "Unknown character";
%}

alpha                             [A-Za-z]
digit                             [0-9]
alphanum                          ({alpha}|{digit})

%%
"if"                              { count(); return If; }
"else"                            { count(); return Else; }
"while"                           { count(); return While; }
"class"                           { count(); return Class; }
"extends"                         { count(); return Extends; }
"public"                          { count(); return Public; }
"static"                          { count(); return Static; }
"void"                            { count(); return Void; }
"boolean"                         { count(); return Boolean; }
"int"                             { count(); return Integer; }
"String"                          { count(); return String; }
"true"                            { count(); return True; }
"false"                           { count(); return False; }
"this"                            { count(); return This; }
"new"                             { count(); return New; }
"System.out.println"              { count(); return Println; }
"return"                          { count(); return Return; }
"length"                          { count(); return ArrayLength; }
"main"                            { count(); return Main; }

{alpha}({alphanum}|"_")*          { 
                                      count();
                                      yylval.tokenstr = strdup(yytext); 
                                      return Id; }
{digit}+                          { 
                                      count();
                                      yylval.tokenstr = strdup(yytext);
                                      return Number; 
                                  }

    /*\"(.|"\n")*\"                     { count(); return Text; }*/

"&&"                              { count(); return And; }
"<"                               { count(); return '<'; }
"+"                               { count(); return '+'; }
"-"                               { count(); return '-'; }
"*"                               { count(); return '*'; }
"!"                               { count(); return '!'; }
"="                               { count(); return '='; }
"."                               { count(); return '.'; }

"("                               { count(); return '('; }
")"                               { count(); return ')'; }
"["                               { count(); return '['; }
"]"                               { count(); return ']'; }
"{"                               { count(); return '{'; }
"}"                               { count(); return '}'; }
","                               { count(); return ','; }
";"                               { count(); return ';'; }

"//".*"\n"                        { /* Comment */yylineno++; }
"/*"(.|"\n")*"*\\"                { /* Comment */yylineno++; }
[ \t\r]                           { count(); }
\n                                { count(); yylineno++; }
.                                 {yyerror(unknown);}

%%

int yywrap()
{
    return 1;
}

int column = 0;

void count() {
    int i;

    for(i = 0; yytext[i] != '\0'; i++)
        if(yytext[i] == '\n')
            column = 0;
        else if(yytext[i] == '\t')
            column += 8 - (column % 8);
        else
            column++;
}


