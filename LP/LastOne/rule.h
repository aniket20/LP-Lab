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

#ifndef YY_YY_RULE_H_INCLUDED
# define YY_YY_RULE_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    SWITCH = 261,
    CASE = 262,
    DEFAULT = 263,
    INT = 264,
    FLOAT = 265,
    BOOL = 266,
    UNSIGNED = 267,
    SIGNED = 268,
    ASSIGN = 269,
    PLUSEQ = 270,
    MINUSEQ = 271,
    TIMESEQ = 272,
    DIVIDEQ = 273,
    PLUS = 274,
    MINUS = 275,
    TIMES = 276,
    DIVIDE = 277,
    EXP = 278,
    IOR = 279,
    IAND = 280,
    INOT = 281,
    XOR = 282,
    OR = 283,
    AND = 284,
    NOT = 285,
    EQ = 286,
    NEQ = 287,
    LT = 288,
    LEQ = 289,
    GT = 290,
    GEQ = 291,
    LP = 292,
    RP = 293,
    LB = 294,
    RB = 295,
    COMMA = 296,
    SEMICOLON = 297,
    COLON = 298,
    DOUBLENUM = 299,
    INTNUM = 300,
    TRUE = 301,
    FALSE = 302,
    ID = 303,
    PLUSPLUS = 304,
    MINUSMINUS = 305,
    CONTINUE = 306,
    BREAK = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 46 "yaccrule.y" /* yacc.c:1909  */

  int type;
  struct marks{
    int instr;
  }mark;
  struct BackpatchList{
    int ins;
    BackpatchList *next;
  };
  struct info{
    char *addr;
    short  type;
    BackpatchList *tlist;
    BackpatchList *flist;
  }exp;
  struct nextL{
      int instr; /** Instruction number */
      BackpatchList *nextList; /**Linked of BackpatchList*/
  }List;
  /**
    Linked list of switch instruction which have to backpatch
  */
  struct switchL{
    int instr;     /**Instruction number*/
    int lineno;    
    switchL *next; /**Next pointer of switch list*/
    bool stype;     /** default or case statement*/
    char *val;     /**Case value*/
  };
  switchL *switchList;
  char *str;

#line 140 "rule.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_RULE_H_INCLUDED  */
