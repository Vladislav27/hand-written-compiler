%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {Comp}
%define parser_class_name {CParser}

%code requires{
   namespace Comp {
      class CDriver;
      class CScanner;
   }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { CScanner  &scanner  }
%parse-param { CDriver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "CDriver.h"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token               END    0     "end of file"
%token               LITTER
%token               DIGIT
%token               NUMBER
%token               WS
%token               COMMENT
%token               STRING
%token               SEMI
%token               COMMA
%token               ASSIGN
%token               EQUAL
%token               LPAREN
%token               RPAREN
%token               LBRACE
%token               RBRACE
%token               IF
%token               ELSE
%token               TRUE
%token               FALSE
%token               INT
%token               BOOL
%token               CLASS
%token               EXTENDS
%token               RETURN
%token               ID

%locations

%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : LITTER   { driver.token(); }
  | DIGIT   { driver.token(); }
  | NUMBER   { driver.token(); }
  | WS   { driver.token(); }
  | COMMENT   { driver.token(); }
  | STRING   { driver.token(); }
  | SEMI   { driver.token(); }
  | COMMA   { driver.token(); }
  | ASSIGN   { driver.token(); }
  | EQUAL   { driver.token(); }
  | LPAREN   { driver.token(); }
  | RPAREN   { driver.token(); }
  | LBRACE   { driver.token(); }
  | RBRACE   { driver.token(); }
  | IF   { driver.token(); }
  | ELSE   { driver.token(); }
  | TRUE   { driver.token(); }
  | FALSE   { driver.token(); }
  | INT   { driver.token(); }
  | BOOL   { driver.token(); }
  | CLASS   { driver.token(); }
  | EXTENDS   { driver.token(); }
  | RETURN   { driver.token(); }
  | ID   { driver.token(); }
  ;

%%


void Comp::CParser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}