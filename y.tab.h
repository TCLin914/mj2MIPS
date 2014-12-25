/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Class = 1,
    Public = 2,
    Static = 3,
    Void = 4,
    Main = 5,
    String = 6,
    Extends = 7,
    Return = 8,
    Integer = 9,
    Boolean = 10,
    If = 11,
    Else = 12,
    While = 13,
    Println = 14,
    ArrayLength = 15,
    True = 16,
    False = 17,
    This = 18,
    And = 19,
    New = 20,
    Id = 21,
    Number = 22
  };
#endif
/* Tokens.  */
/*
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
*/
/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
