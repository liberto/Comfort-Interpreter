/* Definitions */
%array

%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

%}

DELIM           [ \t\n]
WHITESPACE      {DELIM}+
LETTER          [a-zA-Z_]
DIGIT           [0-9]
NUMERAL         -?{DIGIT}+(\.{DIGIT}+)?(e[+-]?{DIGIT}+)?
IDENTIFIER      ({LETTER}|(-({LETTER}|-)))({LETTER}|{DIGIT}|-)*
COMMENT	        \(\*(.)*\*\)

%%

	/* Rules */

{NUMERAL} {
            yylval.type = NUM;
            yylval.value.numVal = atof (yytext);
            return NUMERAL;
          }

{COMMENT}                

false   return FALSE;
true    return TRUE;
\.      return FULLSTOP;
\@      return AT_SIGN;
"=="    return EQUALS;
\;      return SEMICOLON;
\,      return COMMA;
\[      return BEGINQUOTE;
\]      return ENDQUOTE;

\+
{
  yylval.type = OPCODE;
  yylval.value.opVal = PLUS;
  return BASIC_OP;
}

\-
{
  yylval.type = OPCODE;
  yylval.value.opVal = MINUS;
  return BASIC_OP;
}

\*
{
  yylval.type = OPCODE;
  yylval.value.opVal = TIMES;
  return BASIC_OP;
}

\/
{
  yylval.type = OPCODE;
  yylval.value.opVal = DIVIDE;
  return BASIC_OP;
}

\=
{
  yylval.type = OPCODE;
  yylval.value.opVal = EQUAL;
  return BASIC_OP;
}

"!="
{
  yylval.type = OPCODE;
  yylval.value.opVal = NOT_EQUAL;
  return BASIC_OP;
}

\<
{
  yylval.type = OPCODE;
  yylval.value.opVal = LESS_THAN;
  return BASIC_OP;
}

"<="
{
  yylval.type = OPCODE;
  yylval.value.opVal = LEQ;
  return BASIC_OP;
}

\>
{
  yylval.type = OPCODE;
  yylval.value.opVal = GREATER_THAN;
  return BASIC_OP;
}

">="
{
  yylval.type = OPCODE;
  yylval.value.opVal = GEQ;
  return BASIC_OP;
}

abs
{
  yylval.type = OPCODE;
  yylval.value.opVal = ABS;
  return BASIC_OP;
}

acos
{
  yylval.type = OPCODE;
  yylval.value.opVal = ACOS;
  return BASIC_OP;
}

all
{
  yylval.type = OPCODE;
  yylval.value.opVal = ALL;
  return BASIC_OP;
}

and
{
  yylval.type = OPCODE;
  yylval.value.opVal = AND;
  return BASIC_OP;
}

app1
{
  yylval.type = OPCODE;
  yylval.value.opVal = APP1;
  return BASIC_OP;
}

app11
{
  yylval.type = OPCODE;
  yylval.value.opVal = APP11;
  return BASIC_OP;
}

app12
{
  yylval.type = OPCODE;
  yylval.value.opVal = APP12;
  return BASIC_OP;
}

asin
{
  yylval.type = OPCODE;
  yylval.value.opVal = ASIN;
  return BASIC_OP;
}

at
{
  yylval.type = OPCODE;
  yylval.value.opVal = AT;
  return BASIC_OP;
}

atan
{
  yylval.type = OPCODE;
  yylval.value.opVal = ATAN;
  return BASIC_OP;
}

atan2
{
  yylval.type = OPCODE;
  yylval.value.opVal = ATAN2;
  return BASIC_OP;
}

binary
{
  yylval.type = OPCODE;
  yylval.value.opVal = BINARY;
  return BASIC_OP;
}

binrec
{
  yylval.type = OPCODE;
  yylval.value.opVal = BINREC;
  return BASIC_OP;
}

boolean
{
  yylval.type = OPCODE;
  yylval.value.opVal = BOOLEAN;
  return BASIC_OP;
}

branch
{
  yylval.type = OPCODE;
  yylval.value.opVal = BRANCH;
  return BASIC_OP;
}

case
{
  yylval.type = OPCODE;
  yylval.value.opVal = CASE;
  return BASIC_OP;
}

ceil
{
  yylval.type = OPCODE;
  yylval.value.opVal = CEIL;
  return BASIC_OP;
}

choice
{
  yylval.type = OPCODE;
  yylval.value.opVal = CHOICE;
  return BASIC_OP;
}

cleave
{
  yylval.type = OPCODE;
  yylval.value.opVal = CLEAVE;
  return BASIC_OP;
}

compare
{
  yylval.type = OPCODE;
  yylval.value.opVal = COMPARE;
  return BASIC_OP;
}

concat
{
  yylval.type = OPCODE;
  yylval.value.opVal = CONCAT;
  return BASIC_OP;
}

cond
{
  yylval.type = OPCODE;
  yylval.value.opVal = COND;
  return BASIC_OP;
}

cons
{
  yylval.type = OPCODE;
  yylval.value.opVal = CONS;
  return BASIC_OP;
}

construct
{
  yylval.type = OPCODE;
  yylval.value.opVal = CONSTRUCT;
  return BASIC_OP;
}

cos
{
  yylval.type = OPCODE;
  yylval.value.opVal = COS;
  return BASIC_OP;
}

cosh
{
  yylval.type = OPCODE;
  yylval.value.opVal = COSH;
  return BASIC_OP;
}

dip   
{
  yylval.type = OPCODE;
  yylval.value.opVal = DIP;
  return BASIC_OP;
}

div
{
  yylval.type = OPCODE;
  yylval.value.opVal = DIV;
  return BASIC_OP;
}

drop
{
  yylval.type = OPCODE;
  yylval.value.opVal = DROP;
  return BASIC_OP;
}

dup
{
  yylval.type = OPCODE;
  yylval.value.opVal = DUP;
  return BASIC_OP;
}

dupd
{
  yylval.type = OPCODE;
  yylval.value.opVal = DUPD;
  return BASIC_OP;
}

enconcat
{
  yylval.type = OPCODE;
  yylval.value.opVal = ENCONCAT;
  return BASIC_OP;
}

false
{
  yylval.type = OPCODE;
  yylval.value.opVal = FALSE;
  return BASIC_OP;
}

i
{
  yylval.type = OPCODE;
  yylval.value.opVal = I;
  return BASIC_OP;
}

id
{
  yylval.type = OPCODE;
  yylval.value.opVal = ID;
  return BASIC_OP;
}

ifte
{
  yylval.type = OPCODE;
  yylval.value.opVal = IFTE;
  return BASIC_OP;
}

in
{
  yylval.type = OPCODE;
  yylval.value.opVal = IN;
  return BASIC_OP;
}

infra
{
  yylval.type = OPCODE;
  yylval.value.opVal = INFRA;
  return BASIC_OP;
}

integer
{
  yylval.type = OPCODE;
  yylval.value.opVal = INTEGER;
  return BASIC_OP;
}

ldexp
{
  yylval.type = OPCODE;
  yylval.value.opVal = LDEXP;
  return BASIC_OP;
}

linrec
{
  yylval.type = OPCODE;
  yylval.value.opVal = LINREC;
  return BASIC_OP;
}

list
{
  yylval.type = OPCODE;
  yylval.value.opVal = LIST;
  return BASIC_OP;
}

log
{
  yylval.type = OPCODE;
  yylval.value.opVal = LOG;
  return BASIC_OP;
}

log10 
{
  yylval.type = OPCODE;
  yylval.value.opVal = LOG10;
  return BASIC_OP;
}

map
{
  yylval.type = OPCODE;
  yylval.value.opVal = MAP;
  return BASIC_OP;
}

max
{
  yylval.type = OPCODE;
  yylval.value.opVal = MAX;
  return BASIC_OP;
}

min
{
  yylval.type = OPCODE;
  yylval.value.opVal = MIN;
  return BASIC_OP;
}

modf
{
  yylval.type = OPCODE;
  yylval.value.opVal = MODF;
  return BASIC_OP;
}

neg
{
  yylval.type = OPCODE;
  yylval.value.opVal = NEG;
  return BASIC_OP;
}

not
{
  yylval.type = OPCODE;
  yylval.value.opVal = NOT;
  return BASIC_OP;
}

null
{
  yylval.type = OPCODE;
  yylval.value.opVal = NULL;
  return BASIC_OP;
}

nullary
{
  yylval.type = OPCODE;
  yylval.value.opVal = NULLARY;
  return BASIC_OP;
}

of
{
  yylval.type = OPCODE;
  yylval.value.opVal = OF;
  return BASIC_OP;
}

or
{
  yylval.type = OPCODE;
  yylval.value.opVal = OR;
  return BASIC_OP;
}

pop
{
  yylval.type = OPCODE;
  yylval.value.opVal = POP;
  return BASIC_OP;
}

popd
{
  yylval.type = OPCODE;
  yylval.value.opVal = POPD;
  return BASIC_OP;
}

pred
{
  yylval.type = OPCODE;
  yylval.value.opVal = PRED;
  return BASIC_OP;
}

pow
{
  yylval.type = OPCODE;
  yylval.value.opVal = POW;
  return BASIC_OP;
}

primrec
{
  yylval.type = OPCODE;
  yylval.value.opVal = PRIMREC;
  return BASIC_OP;
}

rem
{
  yylval.type = OPCODE;
  yylval.value.opVal = REM;
  return BASIC_OP;
}

rest 
{
  yylval.type = OPCODE;
  yylval.value.opVal = REST;
  return BASIC_OP;
}

rolldown
{
  yylval.type = OPCODE;
  yylval.value.opVal = ROLLDOWN;
  return BASIC_OP;
}

rolldownd
{
  yylval.type = OPCODE;
  yylval.value.opVal = ROLLDOWND;
  return BASIC_OP;
}

rollup
{
  yylval.type = OPCODE;
  yylval.value.opVal = ROLLUP;
  return BASIC_OP;
}

rollupd
{
  yylval.type = OPCODE;
  yylval.value.opVal = ROLLUPD;
  return BASIC_OP;
}

rotate
{
  yylval.type = OPCODE;
  yylval.value.opVal = ROTATE;
  return BASIC_OP;
}

rotated
{
  yylval.type = OPCODE;
  yylval.value.opVal = ROTATED;
  return BASIC_OP;
}

sign
{
  yylval.type = OPCODE;
  yylval.value.opVal = SIGN;
  return BASIC_OP;
}

sin
{
  yylval.type = OPCODE;
  yylval.value.opVal = SIN;
  return BASIC_OP;
}

sinh
{
  yylval.type = OPCODE;
  yylval.value.opVal = SINH;
  return BASIC_OP;
}

size
{
  yylval.type = OPCODE;
  yylval.value.opVal = SIZE;
  return BASIC_OP;
}

small
{
  yylval.type = OPCODE;
  yylval.value.opVal = SMALL;
  return BASIC_OP;
}

some 
{
  yylval.type = OPCODE;
  yylval.value.opVal = SOME;
  return BASIC_OP;
}

split
{
  yylval.type = OPCODE;
  yylval.value.opVal = SPLIT;
  return BASIC_OP;
}

sqrt
{
  yylval.type = OPCODE;
  yylval.value.opVal = SQRT;
  return BASIC_OP;
}

stack
{
  yylval.type = OPCODE;
  yylval.value.opVal = STACK;
  return BASIC_OP;
}

succ
{
  yylval.type = OPCODE;
  yylval.value.opVal = SUCC;
  return BASIC_OP;
}

swap
{
  yylval.type = OPCODE;
  yylval.value.opVal = SWAP;
  return BASIC_OP;
}

swapd
{
  yylval.type = OPCODE;
  yylval.value.opVal = SWAPD;
  return BASIC_OP;
}

swons
{
  yylval.type = OPCODE;
  yylval.value.opVal = SWONS;
  return BASIC_OP;
}

tailrec
{
  yylval.type = OPCODE;
  yylval.value.opVal = TAILREC;
  return BASIC_OP;
}

take
{
  yylval.type = OPCODE;
  yylval.value.opVal = TAKE;
  return BASIC_OP;
}

tan
{
  yylval.type = OPCODE;
  yylval.value.opVal = TAN;
  return BASIC_OP;
}

tanh
{
  yylval.type = OPCODE;
  yylval.value.opVal = TANH;
  return BASIC_OP;
}

ternary
{
  yylval.type = OPCODE;
  yylval.value.opVal = TERNARY;
  return BASIC_OP;
}

times
{
  yylval.type = OPCODE;
  yylval.value.opVal = TIMES;
  return BASIC_OP;
}

treegenrec
{
  yylval.type = OPCODE;
  yylval.value.opVal = TREEGENREC;
  return BASIC_OP;
}

treerec
{
  yylval.type = OPCODE;
  yylval.value.opVal = TREEREC;
  return BASIC_OP;
}

treestep
{
  yylval.type = OPCODE;
  yylval.value.opVal = TREESTEP;
  return BASIC_OP;
}

true
{
  yylval.type = OPCODE;
  yylval.value.opVal = TRUE;
  return BASIC_OP;
}

trunc
{
  yylval.type = OPCODE;
  yylval.value.opVal = TRUNC;
  return BASIC_OP;
}

unary
{
  yylval.type = OPCODE;
  yylval.value.opVal = UNARY;
  return BASIC_OP;
}

unary2
{
  yylval.type = OPCODE;
  yylval.value.opVal = UNARY2;
  return BASIC_OP;
}

unary3
{
  yylval.type = OPCODE;
  yylval.value.opVal = UNARY3;
  return BASIC_OP;
}

unary4
{
  yylval.type = OPCODE;
  yylval.value.opVal = UNARY4;
  return BASIC_OP;
}

uncons
{
  yylval.type = OPCODE;
  yylval.value.opVal = UNCONS;
  return BASIC_OP;
}

unstack
{
  yylval.type = OPCODE;
  yylval.value.opVal = UNSTACK;
  return BASIC_OP;
}

unswons
{
  yylval.type = OPCODE;
  yylval.value.opVal = UNSWONS;
  return BASIC_OP;
}

while
{
  yylval.type = OPCODE;
  yylval.value.opVal = WHILE;
  return BASIC_OP;
}

x
{
  yylval.type = OPCODE;
  yylval.value.opVal = X;
  return BASIC_OP;
}

xor   
{
  yylval.type = OPCODE;
  yylval.value.opVal = XOR;
  return BASIC_OP;
}

{IDENTIFIER}   
{
  yylval.type = NAME;
  yylval.value.name = yytext;
  return DEFINITON;
}

{WHITESPACE}

<<EOF>>	return 0;

%%

int main(int argc, char **argv){
++argv, --argc; /* skip over program name */
if (argc > 0)
yyin = fopen( argv[0], "r");
else
yyin = stdin;

yylex();
}
