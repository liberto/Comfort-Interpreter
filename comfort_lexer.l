/* Definitions */
%array

%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *convertToUpperCase (char *str){
char *newstr, *p;
p = newstr = strdup(str);
while (*p++ = toupper(*p));
return newstr;
}

%}

DELIN           [ \t\n]
WHITESPACE      {DELIN}+
LETTER          [a-zA-Z_]
DIGIT           [0-9]
NUMERAL         {DIGIT}+(\.{DIGIT}+)?((e|E)[+-]?{DIGIT}+)?
IDENTIFIER      ({LETTER}|(-({LETTER}|-)))({LETTER}|{DIGIT}|-)*
COMMENT	        \(\*(.)*\*\)
QUOTATION       \[(.)*\]

%%

	/* Rules */

{DIGIT}+                 printf("<tag=NUMERAL, value = %g>\n", atof (yytext));
{DIGIT}+"."{DIGIT}*      printf("<tag=NUMERAL, value = %g>\n", atof (yytext));
"."{NUMERAL}+  	         printf("<tag=NUMERAL, value = %g>\n", atof (yytext));
{NUMERAL}+               printf("<tag=NUMERAL, value = %g>\n", atof (yytext));
{COMMENT}                printf("<tag=COMMNENT,%s>\n", yytext);
{QUOTATION}              printf("<tag=QUOTATION,%s>\n", yytext);

\@      printf("<tag=AT_SIGN>\n");
"=="    printf("<tag=EQUAL_RELATION>\n");
\;      printf("<tag=SEMICOLON>\n");
\,      printf("<tag=COMMA>\n");
\[      printf("<tag=LEFT_SQUARE_BRACKET>\n");
\]      printf("<tag=RIGHT_SQUARE_BRACKET>\n");

\+      printf("<tag=IDENTIFIER,lexeme=PLUS_SIGN>\n");
\-      printf("<tag=IDENTIFIER,lexeme=HYPHEN-MINUS>\n");
\*      printf("<tag=IDENTIFIER,lexeme=ASTERISK>\n");
\/      printf("<tag=IDENTIFIER,lexeme=SOLIDUS>\n");
\=      printf("<tag=IDENTIFIER,lexeme=EQUALS_SIGN>\n");
"!="    printf("<tag=IDENTIFIER,lexeme=INEQUALITY_RELATION>\n"); 
\<      printf("<tag=IDENTIFIER,lexeme=LESS_THAN_SIGN>\n");
"<="    printf("<tag=IDENTIFIER,lexeme=LESS_OR_EQUAL_RELATION>\n");
\>      printf("<tag=IDENTIFIER,lexeme=GREATER_THAN_SIGN>\n");
">="    printf("<tag=IDENTIFIER,lexeme=GREATER_OR_EQUAL_RELATION>\n");  


abs	|
acos	|
all	|
and	|
app1	|
app11	|
app12	|
asin	|
at	|
atan	|
atan2	|
binary	|
binrec	|
boolean	|
branch  |
case	|
ceil	|
chocie	|
cleave	|
compare	|
concat	|
cond	|
cons	|
construct	|
cos	|
cosh	|
dip   	|
div	|
drop	|
dup	|
dupd	|
enconcat	|
false	|
i	|
id	|
ifte	|
in	|
infra	|
integer	|
ldexp	|
linrec	|
list	|
log	|
log10 	|
map	|
max	|
min	|
modf	|
neg	|
not	|
null	|
nullary	|
of	|
or	|
pop	|
popd	|
pred	|
pow	|
primrec	|
rem	|
rest 	|
rolldown	|
rolldownd	|
rollup	|
rollupd	|
rotate	|
rotated	|
sign	|
sin	|
sinh	|
size	|
small	|
some 	|
split	|
sqrt	|
stack	|
succ	|
swap	|
swapd	|
swons	|
tailrec	|
take	|
tan	|
tanh	|
ternary	|
times	|
treegenrec	|
treerec	|
treestep	|
true	|
trunc	|
unary	|
unary2	|
unary3	|
unary4	|
uncons	|
unstack	|
unswons	|
while	|
x	|
xor   printf("<tag=IDENTIFIER,lexeme=%s_KEYWORD>\n",convertToUpperCase(yytext));


{IDENTIFIER}   {printf("<tag=IDENTIFIER, lexeme=%s>\n", yytext);}

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
