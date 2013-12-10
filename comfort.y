%{
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "nodes.h"
#include "hashtable.h"
#include "functions1-34.h"
#include "functions35-64h"
#include "functions65-94.h"
#include "functions95-121.h"


/* This is our yylval stuff. yylval is a struct with two parts: a union for
 * possible values to carry, and a tag to say what kind of value is being
 * carried. First we define the tags, then we define the struct.
 */
typedef enum 
{
  NUM,
  OPCODE,
  NAME
} tag;

typedef struct 
{
  tag type;
  union
  {
    double numVal;
    opcode opVal;
    char *name;
  } value;
} lexer_return_value; 

void (*functions[121]) = {plus, minus, times, divide, equal, nequal, less_than, leq, greater_than, geq, abs, acos, all, and, appl, appl1, appl2, asin, at, atan, atan2, binary, binrec, boolean, branch, case, ceil, choice, cleave, compare, concat, cond, cons, construct, cos, cosh, dip, div, drop, dup, dupd, enconcat, equal, exp, false, filter, first, float, floor, fold, frexp, genrec, has, i, id, ifte, in, infra, integer, ldexp,linrec, list, log, log10, map, max, min, modf, neg, not, null, nullary, of, or, pop, popd, pred, pow, primrec, rem, rest, rolldown, rolldownd, rollup, rollupd, rotate, rotated, sign, sin, sinh, size, small, some, split, sqrt, stack, succ, swap, swapd, swons, tailrec, take, tan, tanh, ternary, times, treegenrec, treerec, treestep, true, trunc, unary, unary2, unary3, unary4, uncons, unstack, unswons, while, x, xor}

/* Helper procedure for quotation_exec. Recurses through the quotation,
 * executing each element of the quotation in order. Executing a boolean,
 * numeral, or quotation means pushing it onto the stack, while executing
 * an instruction means calling the function associated with that instruction.
 */
void quotexec_helper(node quote)
{
  switch(quote->kind)
  {
    case BASIC_OP:
      instruction_exec(quote->contents.reservedID);
      break;
    case IDENTIFIER:
      /* look up identifier in hash table, do appropriate command */
      break;
    case BOOLEAN:
    case NUMERAL:
    case QUOTATION:
      push(quote);
      break;
    case default:
      printf("big problem error in quotexec_helper, pls to find?\n");
      assert(false);
      break;
    }
  if (quote->next)
    quotexec_helper(quote->next);
}

/* Given a node that contains a quotation, executes the contents of that
 * quotation in order. If the input is not a quotation node, problems
 * will very much occur.
 */
void quotation_exec(node quote)
{
  quotexec_helper(quote->contents.quotation);
}

/* Executes the instruction associated with the opcode given. The function
 * is stored in an array of function pointers. 
 */
void instruction_exec(opcode command)
{
  functions[command]();
}

/* The global stack that stores the inputs and outputs of functions. */
stack globalStack;

/* The global hash table used for all hash purposes. */
def_ht global_def_ht;



%}

%token TRUE FALSE SEMICOLON COMMA FULLSTOP BEGINQUOTE ENDQUOTE EQUALS AT_SIGN NUMERAL DEFINITION BASIC_OP
%YYSTYPE lexer_return_value

%%

program: definition_section expression_list FULLSTOP
	{
		
	}

definition_section: AT_SIGN definition_sequence
		  | /* epsilon */
definition_sequence: definition more_definitions
more_definitions: SEMICOLON definition more_definitions
		| /* epsilon */
definition: identifier EQUALS expression_list
          {
            /* Put the identifier in the hashtable */
          }
expression_list: expression expression_list
		   | /* epsilon */
expression: NUMERAL
          {
            
          }
	  | identifier
          {
            /* call function associated with identifier */
          }
	  | BEGINQUOTE expression_list ENDQUOTE


%%

int main()
{
  global_def_ht = make_def_ht();
  globalStack = (stack) malloc(sizeof(struct nodeStack));
  globalStack.top = NULL;
  yyparse();
  return EXIT_SUCCESS;
}
