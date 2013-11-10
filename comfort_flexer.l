/* Definitions */
%array

%{
#include <stdio.h>
#include <stdlib.h>

//raises a to the bth power
unsigned long int pow(int a, int b)
{
  int out = 1;
  for (;b > 0;b--)
{
    out *= a;
printf("b:%da:%d",b,out);}
  return out;
}

char *convertToUpperCase (char *str){
char *newstr, *p;
p = newstr = strdup(str);
while (*p++ = toupper(*p));
return newstr;
}

%}


LETTER          [a-zA-Z_]
DIGIT           [0-9]
INT             -?{DIGIT}+((e|E)\+?{DIGIT}+)? 
FLOAT		-?{DIGIT}+(\.{DIGIT}+)?((e|E)[+-]?{DIGIT}+)?
COMMENT	        \(\*(.)*\*\)
IDENTIFIER      ({LETTER}|(-({LETTER}|-)))({LETTER}|{DIGIT}|-)*
WHITESPACE	[\n\t\r ]

%%

	/* Rules */
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
branch     	|
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


{COMMENT} printf("<tag=COMMNENT,%s>\n", yytext);

{INT}   {
	  int i = 0; 
	  long long int num = 0; 
	  int exp = 0;
	  int neg = 0;
          if (yytext[0]=='-')
          {
            i++;
            neg = 1;
          }
	  for (; yytext[i] != 'e' && yytext[i] != 'E' && i < yyleng; i++) 
	    num = (10 * num) + (yytext[i]-'0');
	  i++;
          if (neg)
            num *= -1;
	  printf("neg=%d\n",neg);
	  neg = (yytext[i] == '-');
	  printf("neg=%d\n",neg);
	  if (neg) i++;
	  for (; i < yyleng; i++)
	    exp = 10 * exp + yytext[i] - '0';
	  printf("<tag=NUMERAL,value=%d>\n",num);
	}

{FLOAT} {
	  int i = 0; 
	  long double num = 0.0; 
	  double div = 1.0;
	  int exp = 0;
	  int neg = 0;
          if (yytext[0]=='-')
          {
            i++;
            neg = 1;
          }
	  for (; yytext[i] != '.' && i < yyleng; i++) 
	    num = (10 * num) + (yytext[i]-'0');
	  if (yytext[i] == '.')
    	    for (i++; yytext[i] != 'e' && yytext[i] != 'E' && i < yyleng; i++)
	      num += (yytext[i]-'0') * (div /= 10);
	  i++;
          if (neg)
            num *= -1;
	  if (yytext[i] == '-')
	  {
	    i++;
	    neg = 1;
	  } else neg = 0;
	  for (; i < yyleng; i++)
	    exp = 10 * exp + yytext[i] - '0';
	  if (neg) {printf("beep1\n");num /= pow (10, exp);}
	  else {printf("beep2\n");num *= pow (10, exp);}
	  printf("exp:%d\npow:%d\n",exp,pow(10,exp));
	  printf("<tag=NUMERAL,value=%llf>\n",num);
	}

{WHITESPACE}

{IDENTIFIER}   {printf("<tag=IDENTIFIER, lexeme=%s>\n", yytext);}

.	fprintf(stderr, "invalid character %c\n",yytext[0]); return 1;

<<EOF>>	return 0;

%%


