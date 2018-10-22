%{

#include <fstream>
#include <string.h>
/* Implementation of yyFlexScanner */
#include "CScanner.h"
#include "LineHandler.h"
#undef  YY_DECL
#define YY_DECL int Comp::CScanner::yylex( Comp::CParser::semantic_type * const lval, Comp::CParser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = Comp::CParser::token;

Comp::LineHandler lineHandler;

%}

%option debug
%option nodefault
%option yyclass="Comp::CScanner"
%option noyywrap
%option c++


LITTER      [A-Za-z]
DIGIT       [0-9]
NUMBER      [-+]?{DIGIT}{DIGIT}*

WS          [ \t]
NEWLINE     \n
COMMENT     "//"[^\n]*"\n"|"/*".*"*/"
STRING      \"[^\n"]+\"
SEMI        ";"
COMMA       ","
ASSIGN      "="
EQUAL       "=="
PLUS        "+"
MINUS       "-"
MULT        "*"
AND         "&&"
OR          "||"
LESS        "<"
MOD         "%"
LPAREN      "("
RPAREN      ")"
LBRACE      "{"
RBRACE      "}"
LBRACKET    "["
RBRACKET    "]"
IF          "if"
WHILE       "while"
ELSE        "else"
TRUE        "true"
FALSE       "false"
INT         "int"
INTARRAY    "int[]"
TSTRING     "String"
TSTRINGARRAY  "String[]"
BOOL        "boolean"
CLASS       "class"
EXTENDS     "extends"
PUBLIC      "public"
PRIVATE     "private"
THIS        "this"
NEW         "new"
RETURN      "return"
MAIN        "main"
PRINT       "System.out.println"
ID          ({LITTER}|_)({LITTER}|{DIGIT}|_)*

NOT         "!"
DOT         "."
LENGTH      "length"


%%

{SEMI}          {
                    std::cout << "SEMI" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return( token::SEMI );
                }
{COMMA}         {
                    std::cout << "COMMA" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return( token::COMMA );
                }
{INT}           {
                    std::cout << "INT" << std::endl;
                    std::cout << lineHandler.getPosition(3) << " " << lineHandler.getLine() << std::endl;
                    return( token::INT);
                }
{BOOL}          {
                    std::cout << "BOOL" << std::endl;
                    std::cout << lineHandler.getPosition(7) << " " << lineHandler.getLine() << std::endl;
                    return( token::BOOL );
                }
{CLASS}         {
                    std::cout << "CLASS" << std::endl;
                    std::cout << lineHandler.getPosition(5) << " " << lineHandler.getLine() << std::endl;
                    return( token::CLASS );
                }
{EXTENDS}       {
                    std::cout << "EXTENDS" << std::endl;
                    std::cout << lineHandler.getPosition(7) << " " << lineHandler.getLine() << std::endl;
                    return( token::EXTENDS );
                }
{IF}            {
                    std::cout << "IF" << std::endl;
                    std::cout << lineHandler.getPosition(2) << " " << lineHandler.getLine() << std::endl;
                    return( token::IF );
                }
{ELSE}          {
                    std::cout << "ELSE" << std::endl;
                    std::cout << lineHandler.getPosition(4) << " " << lineHandler.getLine() << std::endl;
                    return( token::ELSE );
                }
{EQUAL}         {
                    std::cout << "EQUAL" << std::endl;
                    std::cout << lineHandler.getPosition(2) << " " << lineHandler.getLine() << std::endl;
                    return( token::EQUAL );
                }
{ASSIGN}        {
                    std::cout << "ASSIGN" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return( token::ASSIGN );
                }
{LPAREN}        {
                    std::cout << "LPAREN" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return( token::LPAREN );
                }
{RPAREN}        {
                    std::cout << "RPAREN" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return( token::RPAREN );
                }
{LBRACE}        {
                    std::cout << "LBRACE" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return( token::LBRACE );
                }
{RBRACE}        {
                    std::cout << "RBRACE" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return( token::RBRACE );
                }
{TRUE}          {
                    std::cout << "TRUE" << std::endl;
                    std::cout << lineHandler.getPosition(4) << " " << lineHandler.getLine() << std::endl;
                    return( token::TRUE );
                }
{FALSE}         {
                    std::cout << "FALSE" << std::endl;
                    std::cout << lineHandler.getPosition(5) << " " << lineHandler.getLine() << std::endl;
                    return( token::FALSE );
                }
{RETURN}        {
                    std::cout << "RETURN" << std::endl;
                    std::cout << lineHandler.getPosition(6) << " " << lineHandler.getLine() << std::endl;
                    return( token::RETURN );
                }
{NUMBER}        {
                    std::cout << "NUMBER(" << YYText() << ")" << std::endl;
                    std::cout << lineHandler.getPosition(strlen(YYText())) << " " << lineHandler.getLine() << std::endl;
                    return( token::NUMBER );
                }
{STRING}        {
                    std::cout << "STRING(" << YYText() << ")" << std::endl;
                    std::cout << lineHandler.getPosition(strlen(YYText())) << " " << lineHandler.getLine() << std::endl;
                    return( token::STRING );
                }
{PLUS}          {
                    std::cout << "PLUS" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::PLUS;
                }
{MINUS}         {
                    std::cout << "MINUS" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::MINUS;
                }
{MULT}          {
                    std::cout << "MULT" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::MULT;
                }
{AND}           {
                    std::cout << "AND" << std::endl;
                    std::cout << lineHandler.getPosition(2) << " " << lineHandler.getLine() << std::endl;
                    return token::AND;
                }
{OR}            {
                    std::cout << "OR" << std::endl;
                    std::cout << lineHandler.getPosition(2) << " " << lineHandler.getLine() << std::endl;
                    return token::OR;
                }
{LESS}          {
                    std::cout << "LESS" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::LESS;
                }
{MOD}           {
                    std::cout << "MOD" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::MOD;
                }
{LBRACKET}      {
                    std::cout << "LBRACKET" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::LBRACKET;
                }
{RBRACKET}      {
                    std::cout << "RBRACKET" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::RBRACKET;
                }
{WHILE}         {
                    std::cout << "WHILE" << std::endl;
                    std::cout << lineHandler.getPosition(5) << " " << lineHandler.getLine() << std::endl;
                    return token::WHILE;
                }
{INTARRAY}      {
                    std::cout << "INTARRAY" << std::endl;
                    std::cout << lineHandler.getPosition(5) << " " << lineHandler.getLine() << std::endl;
                    return token::INTARRAY;
                }
{TSTRING}       {
                    std::cout << "TSTRING" << std::endl;
                    std::cout << lineHandler.getPosition(6) << " " << lineHandler.getLine() << std::endl;
                    return token::TSTRING;
                }
{TSTRINGARRAY}  {
                    std::cout << "TSTRINGARRAY" << std::endl;
                    std::cout << lineHandler.getPosition(8) << " " << lineHandler.getLine() << std::endl;
                    return token::TSTRINGARRAY;
                }
{PUBLIC}        {
                    std::cout << "PUBLIC" << std::endl;
                    std::cout << lineHandler.getPosition(6) << " " << lineHandler.getLine() << std::endl;
                    return token::PUBLIC;
                }
{PRIVATE}       {
                    std::cout << "PRIVATE" << std::endl;
                    std::cout << lineHandler.getPosition(7) << " " << lineHandler.getLine() << std::endl;
                    return token::PRIVATE;
                }
{THIS}          {
                    std::cout << "THIS" << std::endl;
                    std::cout << lineHandler.getPosition(4) << " " << lineHandler.getLine() << std::endl;
                    return token::THIS;
                }
{NEW}           {
                    std::cout << "NEW" << std::endl;
                    std::cout << lineHandler.getPosition(3) << " " << lineHandler.getLine() << std::endl;
                    return token::NEW;
                }
{MAIN}          {
                    std::cout << "MAIN" << std::endl;
                    std::cout << lineHandler.getPosition(4) << " " << lineHandler.getLine() << std::endl;
                    return token::MAIN;
                }
{PRINT}         {
                    std::cout << "PRINT" << std::endl;
                    std::cout << lineHandler.getPosition(18) << " " << lineHandler.getLine() << std::endl;
                    return token::PRINT;
                }
{NOT}           {
                    std::cout << "NOT" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::NOT;
                }
{DOT}           {
                    std::cout << "DOT" << std::endl;
                    std::cout << lineHandler.getPosition(1) << " " << lineHandler.getLine() << std::endl;
                    return token::DOT;
                }
{LENGTH}        {
                    std::cout << "LENGTH" << std::endl;
                    std::cout << lineHandler.getPosition(6) << " " << lineHandler.getLine() << std::endl;
                    return token::LENGTH;
                }
{ID}            {
                    std::cout << "ID(" << YYText() << ")" << std::endl;
                    std::cout << lineHandler.getPosition(strlen(YYText())) << " " << lineHandler.getLine() << std::endl;
                    return( token::ID );
                }
{WS}            {
                    lineHandler.getPosition(1);
                }
{NEWLINE}       {
                    lineHandler.refreshValues();
                }
{COMMENT}       /* skip all comments */

%%
