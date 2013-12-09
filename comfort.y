%{
#include <stdbool.h>

/* Stores the possible types of nodes. Each type corresponds to one field of
 * the node.contents union. 
 */
typedef enum
{
  BOOLEAN,
  NUMERAL,
  QUOTATION,
  BASIC_OP,
  IDENTIFIER
} nodeType;

typedef enum
{
  PLUS,
  MINUS,
  TIMES,
  DIVIDE,
  EQUAL,
  NOT_EQUAL,
  LESS_THAN,
  LEQ,
  GREATER_THAN,
  GEQ,
  ABS,
  ACOS,
  ALL,
  AND,
  APP1,
  APP11,
  APP12,
  ASIN,
  AT,
  ATAN,
  ATAN2,
  BINARY,
  BINREC,
  BOOLEAN,
  BRANCH,
  CASE,
  CEIL,
  CHOICE,
  CLEAVE,
  COMPARE,
  CONCAT,
  COND,
  CONS,
  CONSTRUCT,
  COS,
  COSH,
  DIP,
  DIV,
  DROP,
  DUP,
  DUPD,
  ENCONCAT,
  EQUAL,
  EXP,
  FALSE,
  FILTER,
  FIRST,
  FLOAT,
  FLOOR,
  FOLD,
  FREXP,
  GENREC,
  HAS,
  I,
  ID,
  IFTE,
  IN,
  INFRA,
  INTEGER,
  LDEXP,
  LINREC,
  LIST,
  LOG,
  LOG10,
  MAP,
  MAX,
  MIN,
  MODF,
  NEG,
  NOT,
  NULL,
  NULLARY,
  OF,
  OR,
  POP,
  POPD,
  PRED,
  POW,
  PRIMREC,
  REM,
  REST,
  ROLLDOWN,
  ROLLDOWND,
  ROLLUP,
  ROLLUPD,
  ROTATE,
  ROTATED,
  SIGN,
  SIN,
  SINH,
  SIZE,
  SMALL,
  SOME,
  SPLIT,
  SQRT,
  STACK,
  SUCC,
  SWAP,
  SWAPD,
  SWONS,
  TAILREC,
  TAKE,
  TAN,
  TANH,
  TERNARY,
  TIMES,
  TREEGENREC,
  TREEREC,
  TREESTEP,
  TRUE,
  TRUNC,
  UNARY,
  UNARY2,
  UNARY3,
  UNARY4,
  UNCONS,
  UNSTACK,
  UNSWONS,
  WHILE,
  X,
  XOR  
} opcode;

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

/* This struct contains the node information used by the quotation and stack
 * structs. This is a linked list that contains either a primitive value,
 * an operation (represented by an integer corresponding to the array index
 * of a function pointer that calls the operation's function), or a quotation.
 */
typedef struct genericNode
{
  nodeType kind;
  union
  {
    bool boolVal;
    double numVal;
    struct genericNode *quotation;
    opcode reservedID;
    int definedID;
  } contents;
  struct genericNode *next;
} *node;

typedef struct nodeStack
{
  node top;
} *stack;

typedef struct quotationList
{
  node first;
} *quotation;


void (*functions[121]) = {plus, minus, times, divide, equal, nequal, less_than, leq, greater_than, geq, abs, acos, all, and, appl, appl1, appl2, asin, at, atan, atan2, binary, binrec, boolean, branch, case, ceil, choice, cleave, compare, concat, cond, cons, construct, cos, cosh, dip, div, drop, dup, dupd, enconcat, equal, exp, false, filter, first, float, floor, fold, frexp, genrec, has, i, id, ifte, in, infra, integer, ldexp,linrec, list, log, log10, map, max, min, modf, neg, not, null, nullary, of, or, pop, popd, pred, pow, primrec, rem, rest, rolldown, rolldownd, rollup, rollupd, rotate, rotated, sign, sin, sinh, size, small, some, split, sqrt, stack, succ, swap, swapd, swons, tailrec, take, tan, tanh, ternary, times, treegenrec, treerec, treestep, true, trunc, unary, unary2, unary3, unary4, uncons, unstack, unswons, while, x, xor}



/* This section is the stuff for the hash tables used for storing definitions. 
 * All of this is heavily based on lexeme-token-hash-tables.c.
 */

/* This struct pairs the function definition (which is just a quotation node)
 * with the name of the function.
 */
typedef struct 
{
  char *name;
  node function;
} name_def_pair;

/* This is the linked-list structure for our chained hash table. */
typedef struct pair_list 
{
  name_def_pair node;
  struct pair_list *next;
} *pair_list;

/* A hash table for storing quotations corresponding to user-defined functions.
 * This is kept very basic to save time; the size is a constant 150. May 
 * change this later, especially if we have time to move bits and pieces to
 * separate header files.
 */
typedef struct definition_hash_table
{  
  pair_list *table;
} def_ht;

/* The global hash table used for all hash purposes. */
def_ht global_def_ht;

/* Allocates a definition hash table with 150 spaces and returns it. */
def_ht make_def_ht()
{
  def_ht out = (def_ht) malloc(sizeof(struct definition_hash_table));
  out->table = (pair_list*) malloc(150 * sizeof(struct pair_list));
  for (unsigned int index = 0; index < 150; index ++)
    out->table[i] = NULL;
  return out;
}

/* This uses the djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html 
 * to hash strings. Since the table size is always 150, this then mods by 150
 * before returning the result.
 */
unsigned long hash(char *str)
{
  unsigned long hash = 5381;
  int c;
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % 150;
}

node def_ht_get(char *def_name)
{
  pair_list match = global_def_ht->table[hash(def_name)];
  while (match)
  {
    if (strcmp(match->node.name, def_name) == 0)
      return match->node;
    match = match->next;
  }
  return (node) NULL;
}

void def_ht_put(char *def_name, node quot)
{
  unsigned int slot = hash(def_name);
  if (global_def_ht->table[slot] == NULL)
  {
    pair_list new_list = (pair_list) malloc(sizeof(struct pair_list));
    new_list->name_def_pair.name = def_name;
    new_list->name_def_pair.function = quot;
    new_list->next = NULL;
    global_def_ht->table[slot] = new_list;
    return;
  }

  pair_list matcher = global_def_ht->table[slot];
  while(matcher && strcmp(matcher->name_def_pair.name, def_name) != 0)
    matcher = matcher->next;
  if(matcher)
    matcher->name_def_pair.function = quot;
  else
  {
    pair_list new_list = (pair_list) malloc(sizeof(struct pair_list));
    new_list->name_def_pair.name = def_name;
    new_list->name_def_pair.function = quot;
    new_list->next = table[slot];
    global_def_ht->table[slot] = new_list;
  }    
}

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

stack globalStack;

/* Adds the given node to the top of the stack, pushing everything else down.
 * This takes no parameters, because we only ever use the global stack.
 */ 
void push(node in)
{
  in->next = globalStack->top;
  globalStack->top = in;
}

/* Removes and returns the top value of the stack. 
 * This takes no parameters, because we only ever use the global stack. 
 */
node pop() 
{
  node out = globalStack->top;
  globalStack->top = top->next;
  return out;
}

/* Creates a copy of the input stack and returns a pointer to it. Starts at the
 * top of the stack and recurses down.
 */
node copyStackHelper(node curNode)
{
  if (curNode)
  {
    node n = malloc(sizeof(struct genericNode));
    n->kind = curNode->kind;
    n->contents.intVal = curNode->contents.intVal;
    n->next = copyStackHelper(curNode->next);
    return n;
  }
  else return NULL;
}

stack copyStack(stack origStack)
{
  stack out = malloc(sizeof(struct nodeStack));
  out->top = copyStackHelper(origStack->top);
  return out;
}


/* This section is memory management functions */

//for mutual recursion
void freeNode(node in);

/* Frees the input node and all following nodes. This is good for clearing
 * the stack or for clearing quotations.
 */
void freeList(node in)
{
  if (in->next)
    freeList(in->next);
  freeNode(in);
}

/* Frees the input node. If it's a quotation, frees the list of nodes in
 * the quotation. 
 */
void freeNode(node in)
{
  if (in->kind == QUOTATION)
    freeList(in->contents.quotation);
  free(in);
}

/* Frees the stack and all nodes in it. */
void freeStack(stack in)
{
  freeList(in->top);
}



//for the mutual recursion again
bool nodeEquals(node a, node b);

/* Compares two quotations. Returns true if every node in quotation a has a
 * corresponding, exactly equal node in b. 
 */
bool quotationEquals(node a, node b)
{ 
  if (a && b) //neither a nor b is NULL
    return (nodeEquals(a, b) && quotationEquals(a->next, b->next));
  else return !(a || b); //true if both a and b are NULL; else false.
}
/* This section contains a few utility functions. */

/* Compares two nodes. Returns true if they are equivalent - that is,
 * their type is the same, and their contents are the same.
 *
 * This expression looks ugly, but all it does is return true if 
 * 1) both a and b are equivalent quotations, or
 * 2) a and b are the same, non-QUOTATION type of node and have the same
 * contents.
 */
bool nodeEquals(node a, node b)
{
  return (a->kind == QUOTATION && b->kind == QUOTATION && 
             quotationEquals(a->contents.quotation, b->contents.quotation)
          || a->kind != QUOTATION && a->kind == b->kind && 
             a->contents.numVal == b->contents.numVal);
}

/* Given a node and a quotation, appends the node to the end of the quotation.
 * Due to the similarities between quotations and stacks, if the second argument
 * is a node on the stack, this will put the node on the bottom of the stack.
 * This works just fine if the first argument is itself a quotation or stack, 
 * in which case it will append the first quotation or stack to the second.
 */
void append(node appendee, node quotation)
{
  while(quotation->next)
    quotation = quotation->next;
  quotation->next = appendee;
}

/* Here begins our long list of built-in Comfort functions. */

void plus()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
    second->contents.numVal += first->contents.numVal;
  else assert(false);
  freeNode(first);
  push(second);
}

void minus()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
    second->contents.numVal -= first->contents.numVal;
  else assert(false);
  freeNode(first);
  push(second);
}

void times()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
    second->contents.numVal *= first->contents.numVal;
  else assert(false);
  freeNode(first);
  push(second);
}

void divide()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
    second->contents.numVal /= first->contents.numVal;
  else assert(false);
  freeNode(first);
  push(second);
}

void equal()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
  {
    second->kind = BOOLEAN;
    second->contents.boolVal = (second->contents.numVal == first->contents.numVal);
  }
  else assert(false);
  freeNode(first);
  push(second); 
}

void nequal()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
  {
    second->kind = BOOLEAN;
    second->contents.boolVal = (second->contents.numVal != first->contents.numVal);
  }
  else assert(false);
  freeNode(first);
  push(second); 
}

void less_than()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
  {
    second->kind = BOOLEAN;
    second->contents.boolVal = (second->contents.numVal < first->contents.numVal);
  }
  else assert(false);
  freeNode(first);
  push(second); 
}

void leq()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
  {
    second->kind = BOOLEAN;
    second->contents.boolVal = (second->contents.numVal <= first->contents.numVal);
  }
  else assert(false);
  freeNode(first);
  push(second);
}

void greater_than()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
  {
    second->kind = BOOLEAN;
    second->contents.boolVal = (second->contents.numVal > first->contents.numVal);
  }
  else assert(false);
  freeNode(first);
  push(second);
}

void geq()
{
  node first = pop();
  node second = pop();
  if (first->kind == NUMERAL && second->kind == NUMERAL)
  {
    second->kind = BOOLEAN;
    second->contents.boolVal = (second->contents.numVal >= first->contents.numVal);
  }
  else assert(false);
  freeNode(first);
  push(second);
}

void abs()
{
  node first = pop();
  assert(first->kind == NUMERAL);
  if (first->contents.numVal < 0)
    first->contents.numVal *= -1;
  push(first);
}

void acos()
{
  node first = pop();
  double val = first->contents.numVal;
  assert(first->kind == NUMERAL && val >= -1 && val <= 1);
  first->contents.numVal = acos(val);
  push(first);
}

void all()
{
  node first = pop();
  node second = pop();
  assert(first->kind == QUOTATION && second->kind == QUOTATION);
  first = first->contents.quotation;
  node temp = first->next;
  bool result = true;
  do
  {
    push(first);
    quotation_exec(second);
    first = pop();
    assert(first->kind = BOOLEAN);
    result = result && first->contents.boolVal;
    freeNode(first);
    first = temp;
    temp = temp->next;
  } while (temp);
  if (result)
  {
    first = (struct genericNode) malloc(sizeof(struct genericNode));
    first->kind = BOOLEAN;
    first->contents.boolVal = result;
    push(first); 
    /* We don't need to initialize first->next, as push sets this before 
     * it can be accessed. */
  }
  //do we do anything if result is false? ask stone
  freeNode(second);
}

void and()
{
  node first = pop();
  node second = pop();
  assert(first->kind == BOOLEAN && second->kind == BOOLEAN);
  second->contents.boolVal = first->contents.boolVal && second->contents.boolVal;
  push(second);
  freeNode(first);
}

void appl()
{
  node first = pop();
  freeNode(pop); //this value is discarded?
  quotation_exec(first);
  freeNode(first);
}

void appl1()
{
  node first = pop();
  freeNode(pop); //this value is discarded?
  freeNode(pop);
  quotation_exec(first);
  freeNode(first);
}

void appl2()
{
  node first = pop();
  freeNode(pop); //this value is discarded?
  freeNode(pop);
  freeNode(pop);
  quotation_exec(first);
  freeNode(first);
}

void asin()
{
  node first = pop();
  double val = first->contents.numVal;
  assert(first->kind == NUMERAL && val >= -1 && val <= 1);
  first->contents.numVal = asin(val);
  push(first);
}

void at()
{
  node first = pop();
  node second = pop();
  assert(first->kind == QUOTATION && second->kind == NUMERAL);
  node temp = second->contents.quotation;
  int index = second->contents.numVal;
  assert(second->contents.numVal == index && index >= 0); //index is a positive integer.
  for (;index > 0; index--)
    temp = temp->next;
  push(temp);
  freeNode(first);
  freeNode(second);
}

void atan()
{
  node first = pop();
  double val = first->contents.numVal;
  assert(first->kind == NUMERAL)
  first->contents.numVal = atan(val);
  push(first);
}

void atan2()
{
  node first = pop();
  node second = pop();
  double val = second->contents.numVal / first->contents.numVal;
  assert(first->kind == NUMERAL && second->kind == NUMERAL);
  first->contents.numVal = atan(val);
  push(first);
  freeNode(second);
}

void binary()
{
  node first = pop();
  assert(first->kind == QUOTATION);
  node second = pop();
  node third = pop();
  stack temp = copyStack(globalStack);
  push(third);
  push(second);
  quotation_exec(first);
  node top = pop();
  freeNode(first);
  freeNode(second);
  freeNode(third);
  globalStack = temp;
  push(top);
}

void binrec()
{
  node first = pop();
  node second = pop();
  node third = pop();
  node fourth = pop();
  quotation_exec(first);
  node fifth = pop();
  assert(fifth->kind == BOOLEAN);
  if (fifth->contents.boolVal)
    quotation_exec(second);
  else
  {
    quotation_exec(third);
    node sixth = pop();
    node seventh = pop();
    stack temp = copyStack(globalStack);
    push(sixth);
    push(fourth);
    push(third);
    push(second);
    push(first);
    binrec();
    sixth = pop();
    freeStack(globalStack);
    globalStack = temp;
    push(seventh);
    push(fourth);
    push(third);
    push(second);
    push(first);
    binrec();
    push(sixth);
    quotation_exec(fourth);
  }
}

void boolean()
{
  node first = pop();
  if (first->kind == BOOLEAN)
    first->contents.boolVal = true;
  else
  {
    first->kind == BOOLEAN;
    first->contents.boolVal = false;
  }
  push(first);
}

void branch()
{
  node first = pop();
  node second = pop();
  node third = pop();
  assert(first->kind == BOOLEAN && second->kind == QUOTATION && third->kind == QUOTATION);
  if (first->contents.boolVal)
    quotation_exec(second);
  else quotation_exec(third);
  freeNode(first);
  freeNode(second);
  freeNode(third);
}

void case()
{
  node first = pop();
  node second = pop();
  assert(second->kind == QUOTATION && second->contents.quotation->kind == QUOTATION);
  node temp = second->contents.quotation;
  do
  {
    assert(temp->kind == QUOTATION);
    if nodeEqual(first, temp->contents.quotation)
      quotation_exec(temp->contents.quotation->next);
    temp = temp->next;
  }
  while (temp);
  freeNode(first);
  freeNode(second);
}

void ceil()
{
  node first = pop();
  assert(first->kind == NUMERAL);
  first->contents.numVal = ceil(first->contents.numVal);
  push(first);
}

void choice()
{
  node first = pop();
  node second = pop();
  node third = pop();
  assert(first->kind == BOOLEAN);
  if (first->contents.boolVal)
  {
    freeNode(third);
    push(second);
  }
  else 
  {
    push(third);
    freeNode(second);
  }
  freeNode(first);
}

void cleave()
{
  node first = pop();
  node second = pop();
  assert(first->kind == QUOTATION && second->kind == QUOTATION);
  stack savedStack = copyStack(globalStack);
  quotation_exec(first);
  freeNode(first);
  first = pop();
  globalStack = copyStack(savedStack);
  quotation_exec(second);
  freeNode(second);
  second = pop();
  globalStack = copyStack(savedStack);
  push(first);
  push(second);
  freeStack(savedStack);
}

void compare()
{
  node first = pop();
  node second = pop();
  assert(first->kind == NUMERAL && second->kind == NUMERAL);
  if (first->contents.numVal > second->contents.numVal)
    second->contents.numVal = -1;
  else if (first->contents.numVal < second->contents.numVal)
    second->contents.numVal = 1;
  else second->contents.numVal = 0;
  freeNode(first);
  push(second);
}

void concat()
{
  node first = pop();
  node second = pop();
  assert(first->kind == QUOTATION && second->kind == QUOTATION);
  append(second->contents.quotation, first->contents.quotation);
  free(second);
}

void cond()
{
  node first = pop();
  assert(first->kind == QUOTATION && first->contents.quotation);
  node temp = first->contents.quotation;
  node temp2 = NULL;
  bool result = false;
  while (temp)
  {
    if (!result)
    {
      assert(temp->kind == QUOTATION && temp->contents.quotation->next
              && !temp->contents.quotation->next->next);
      quotation_exec(temp->contents.quotation);
      temp2 = pop();
      assert(temp2->kind == BOOLEAN);
      result = result || temp2->contents.boolVal; 
    }
    else
    {
      assert(temp->kind == QUOTATION && temp->contents.quotation->next
              && !temp->contents.quotation->next->next);
      quotation_exec(temp->contents.quotation->next);
      temp2 = pop(); //Not sure if we have to pop or not.
    }
    temp = temp->next;
  }
  if (!result)
    quotation_exec(temp);
}

void cons()
{
  node first = pop();
  node second = pop();
  assert(first->kind == QUOTATION);
  second->next = first->contents.quotation;
  first->contents.quotation = second;
  push(first);
}

void construct()
{
  stack tempStack = copyStack(globalStack);
  node first = pop();
  node second = pop();
  assert(first->kind == QUOTATION && second->kind = QUOTATION);
  quotation_exec(first);
  node temp = second->contents.quotation;
  node temp2 = NULL;
  while (temp)
  {
    quotation_exec(temp);
    temp2->next = pop();
    tempStack->top = temp2;
  }
  free(globalStack);
  globalStack = tempStack;
}

%}

%token TRUE FALSE SEMICOLON COMMA FULLSTOP BEGINQUOTE ENDQUOTE EQUALS AT_SIGN NUMERAL DEFINITION BASIC_OP

%%

program: definition_section expression_list '.'
	{
		
	}

definition_section: '@' definition_sequence
		  | /* epsilon */
definition_sequence: definition more_definitions
more_definitions: ';' definition more_definitions
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
	  | '[' expression_list ']'


%%

int main()
{
  globalStack = (stack) malloc(sizeof(struct nodeStack));
  globalStack.top = NULL;
  yyparse();
  return EXIT_SUCCESS;
}
