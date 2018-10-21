%{

#include <fstream>
/* Implementation of yyFlexScanner */
#include "CScanner.h"
#undef  YY_DECL
#define YY_DECL int Comp::CScanner::yylex( Comp::CParser::semantic_type * const lval, Comp::CParser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = Comp::CParser::token;

%}

%option debug
%option nodefault
%option yyclass="Comp::CScanner"
%option noyywrap
%option c++


LITTER      [A-Za-z]
DIGIT       [0-9]
NUMBER      [-+]?{DIGIT}{DIGIT}*

WS          [ \t\n]+
COMMENT     "//"[^\n]*"\n"|"/*".*"*/"
STRING      \"[^\n"]+\"
SEMI        ";"
COMMA       ","
ASSIGN      "="
EQUAL       "=="
LPAREN      "("
RPAREN      ")"
LBRACE      "{"
RBRACE      "}"
IF          "if"
ELSE        "else"
TRUE        "true"
FALSE       "false"
INT         "int"
BOOL        "boolean"
CLASS       "class"
EXTENDS     "extends"
RETURN      "return"
ID          ({LITTER}|_)({LITTER}|{DIGIT}|_)*


%%

{SEMI}          {
                    std::cout << "SEMI" << std::endl;
                    return( token::SEMI );
                }
{COMMA}         {
                    std::cout << "COMMA" << std::endl;
                    return( token::COMMA );
                }
{INT}           {
                    std::cout << "INT" << std::endl;
                    return( token::INT);
                }
{BOOL}          {
                    std::cout << "BOOL" << std::endl;
                    return( token::BOOL );
                }
{CLASS}         {
                    std::cout << "CLASS" << std::endl;
                    return( token::CLASS );
                }
{EXTENDS}       {
                    std::cout << "EXTENDS" << std::endl;
                    return( token::EXTENDS );
                }
{IF}            {
                    std::cout << "IF" << std::endl;
                    return( token::IF );
                }
{ELSE}          {
                    std::cout << "ELSE" << std::endl;
                    return( token::ELSE );
                }
{EQUAL}         {
                    std::cout << "EQUAL" << std::endl;
                    return( token::EQUAL );
                }
{ASSIGN}        {
                    std::cout << "ASSIGN" << std::endl;
                    return( token::ASSIGN );
                }
{LPAREN}        {
                    std::cout << "LPAREN" << std::endl;
                    return( token::LPAREN );
                }
{RPAREN}        {
                    std::cout << "RPAREN" << std::endl;
                    return( token::RPAREN );
                }
{LBRACE}        {
                    std::cout << "LBRACE" << std::endl;
                    return( token::LBRACE );
                }
{RBRACE}        {
                    std::cout << "RBRACE" << std::endl;
                    return( token::RBRACE );
                }
{TRUE}          {
                    std::cout << "TRUE" << std::endl;
                    return( token::TRUE );
                }
{FALSE}         {
                    std::cout << "FALSE" << std::endl;
                    return( token::FALSE );
                }
{RETURN}        {
                    std::cout << "RETURN" << std::endl;
                    return( token::RETURN );
                }
{ID}            {
                    std::cout << "ID(" << YYText() << ")" << std::endl;
                    return( token::ID );
                }
{NUMBER}        {
                    std::cout << "NUMBER(" << YYText() << ")" << std::endl;
                    return( token::NUMBER );
                }
{STRING}        {
                    std::cout << "STRING(" << YYText() << ")" << std::endl;
                    return( token::STRING );
                }
{WS}            /* skip blanks and tabs newlines*/
{COMMENT}       /* skip all comments */

%%
