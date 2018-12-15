%{

#include <fstream>
#include <string.h>
/* Implementation of yyFlexScanner */
#include "CScanner.h"
#include "Symbol.h"
#include "StringInterner.h"
#undef  YY_DECL
#define YY_DECL int Comp::CScanner::yylex( Comp::CParser::semantic_type * const lval, Comp::CParser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = Comp::CParser::token;

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="Comp::CScanner"
%option noyywrap
%option yylineno
%option c++


LITTER      [A-Za-z]
DIGIT       [0-9]
NUMBER      {DIGIT}{DIGIT}*

WS          [ \t]
NEWLINE     \n
COMMENT     "//"[^\n]*"\n"
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
VOID        "void"
STATIC      "static"
ID          ({LITTER}|_)({LITTER}|{DIGIT}|_)*

NOT         "!"
DOT         "."
LENGTH      "length"


%%

{SEMI}          {
                    //std::cout << "SEMI" << std::endl;
                    return( token::SEMI );
                }
{COMMA}         {
                    //std::cout << "COMMA" << std::endl;
                    return( token::COMMA );
                }
{INT}           {
                    //std::cout << "INT" << std::endl;
                    return( token::INT);
                }
{BOOL}          {
                    //std::cout << "BOOL" << std::endl;
                    return( token::BOOL );
                }
{CLASS}         {
                    //std::cout << "CLASS" << std::endl;
                    return( token::CLASS );
                }
{EXTENDS}       {
                    //std::cout << "EXTENDS" << std::endl;
                    return( token::EXTENDS );
                }
{IF}            {
                   // std::cout << "IF" << std::endl;
                    return( token::IF );
                }
{ELSE}          {
                    //std::cout << "ELSE" << std::endl;
                    return( token::ELSE );
                }
{EQUAL}         {
                    //std::cout << "EQUAL" << std::endl;
                    return( token::EQUAL );
                }
{ASSIGN}        {
                    //std::cout << "ASSIGN" << std::endl;
                    return( token::ASSIGN );
                }
{LPAREN}        {
                    //std::cout << "LPAREN" << std::endl;
                    return( token::LPAREN );
                }
{RPAREN}        {
                    //std::cout << "RPAREN" << std::endl;
                    return( token::RPAREN );
                }
{LBRACE}        {
                    //std::cout << "LBRACE" << std::endl;
                    return( token::LBRACE );
                }
{RBRACE}        {
                    //std::cout << "RBRACE" << std::endl;
                    return( token::RBRACE );
                }
{TRUE}          {
                    //std::cout << "TRUE" << std::endl;
                    return( token::TRUE );
                }
{FALSE}         {
                    //std::cout << "FALSE" << std::endl;
                    return( token::FALSE );
                }
{RETURN}        {
                    //std::cout << "RETURN" << std::endl;
                    return( token::RETURN );
                }
{NUMBER}        {
                    //std::cout << "NUMBER(" << YYText() << ")" << std::endl;
                    int value = std::atoi(yytext);
                    lval->build<int>(value);
                    return( token::NUMBER );
                }
{STRING}        {
                    //std::cout << "STRING(" << YYText() << ")" << std::endl;
                    return( token::STRING );
                }
{PLUS}          {
                    //std::cout << "PLUS" << std::endl;
                    return token::PLUS;
                }
{MINUS}         {
                    //std::cout << "MINUS" << std::endl;
                    return token::MINUS;
                }
{MULT}          {
                    //std::cout << "MULT" << std::endl;
                    return token::MULT;
                }
{AND}           {
                    //std::cout << "AND" << std::endl;
                    return token::AND;
                }
{OR}            {
                    //std::cout << "OR" << std::endl;
                    return token::OR;
                }
{LESS}          {
                    //std::cout << "LESS" << std::endl;
                    return token::LESS;
                }
{MOD}           {
                    //std::cout << "MOD" << std::endl;
                    return token::MOD;
                }
{LBRACKET}      {
                    //std::cout << "LBRACKET" << std::endl;
                    return token::LBRACKET;
                }
{RBRACKET}      {
                    //std::cout << "RBRACKET" << std::endl;
                    return token::RBRACKET;
                }
{WHILE}         {
                    //std::cout << "WHILE" << std::endl;
                    return token::WHILE;
                }
{INTARRAY}      {
                    //std::cout << "INTARRAY" << std::endl;
                    return token::INTARRAY;
                }
{TSTRING}       {
                    //std::cout << "TSTRING" << std::endl;
                    return token::TSTRING;
                }
{TSTRINGARRAY}  {
                    //std::cout << "TSTRINGARRAY" << std::endl;
                    return token::TSTRINGARRAY;
                }
{PUBLIC}        {
                    //std::cout << "PUBLIC" << std::endl;
                    return token::PUBLIC;
                }
{PRIVATE}       {
                    ///std::cout << "PRIVATE" << std::endl;
                    return token::PRIVATE;
                }
{THIS}          {
                    //std::cout << "THIS" << std::endl;
                    return token::THIS;
                }
{NEW}           {
                    //std::cout << "NEW" << std::endl;
                    return token::NEW;
                }
{MAIN}          {
                    //std::cout << "MAIN" << std::endl;
                    return token::MAIN;
                }
{PRINT}         {
                    //std::cout << "PRINT" << std::endl;
                    return token::PRINT;
                }
{NOT}           {
                    //std::cout << "NOT" << std::endl;
                    return token::NOT;
                }
{DOT}           {
                    //std::cout << "DOT" << std::endl;
                    return token::DOT;
                }
{LENGTH}        {
                    //std::cout << "LENGTH" << std::endl;
                    return token::LENGTH;
                }
{VOID}           {
                    //std::cout << "VOID" << std::endl;
                    return token::VOID;
                }
{STATIC}           {
                    ///std::cout << "STATIC" << std::endl;
                    return token::STATIC;
                }
{ID}            {
                    //std::cout << "ID(" << YYText() << ")" << std::endl;
                    const NTree::Symbol* str = interner->GetIntern(YYText());
                    lval->build<const NTree::Symbol*>(str);
                    return( token::ID );
                }
{WS}            {
                }
{NEWLINE}       {
                    loc->lines();
                }
{COMMENT}       {
                    loc->lines();
                }

%%
