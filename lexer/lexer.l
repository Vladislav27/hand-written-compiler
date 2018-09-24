%{

#include <fstream>

%}

%option c++
%option noyywrap


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
                }
{COMMA}         {
                    std::cout << "COMMA" << std::endl;
                }
{INT}           {
                    std::cout << "INT" << std::endl;
                }
{BOOL}          {
                    std::cout << "BOOL" << std::endl;
                }
{CLASS}         {
                    std::cout << "CLASS" << std::endl;
                }
{EXTENDS}       {
                    std::cout << "EXTENDS" << std::endl;
                }
{IF}            {
                    std::cout << "IF" << std::endl;
                }
{ELSE}          {
                    std::cout << "ELSE" << std::endl;
                }
{EQUAL}         {
                    std::cout << "EQUAL" << std::endl;
                }
{ASSIGN}        {
                    std::cout << "ASSIGN" << std::endl;
                }
{LPAREN}        {
                    std::cout << "LPAREN" << std::endl;
                }
{RPAREN}        {
                    std::cout << "RPAREN" << std::endl;
                }
{LBRACE}        {
                    std::cout << "LBRACE" << std::endl;
                }
{RBRACE}        {
                    std::cout << "RBRACE" << std::endl;
                }
{TRUE}          {
                    std::cout << "TRUE" << std::endl;
                }
{FALSE}         {
                    std::cout << "FALSE" << std::endl;
                }
{RETURN}        {
                    std::cout << "RETURN" << std::endl;
                }
{ID}            {
                    std::cout << "ID(" << YYText() << ")" << std::endl;
                }
{NUMBER}        {
                    std::cout << "NUMBER(" << YYText() << ")" << std::endl;
                }
{STRING}        {
                    std::cout << "STRING(" << YYText() << ")" << std::endl;;
                }
{WS}            /* skip blanks and tabs newlines*/
{COMMENT}       /* skip all comments */

%%
