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
    Class = 258,
    Public = 259,
    Static = 260,
    Void = 261,
    Main = 262,
    String = 263,
    Extends = 264,
    Return = 265,
    Integer = 266,
    Boolean = 267,
    If = 268,
    Else = 269,
    While = 270,
    Println = 271,
    ArrayLength = 272,
    True = 273,
    False = 274,
    This = 275,
    And = 276,
    New = 277,
    Id = 278,
    Number = 279
  };
#endif
/* Tokens.  */
#define Class 258
#define Public 259
#define Static 260
#define Void 261
#define Main 262
#define String 263
#define Extends 264
#define Return 265
#define Integer 266
#define Boolean 267
#define If 268
#define Else 269
#define While 270
#define Println 271
#define ArrayLength 272
#define True 273
#define False 274
#define This 275
#define And 276
#define New 277
#define Id 278
#define Number 279

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
