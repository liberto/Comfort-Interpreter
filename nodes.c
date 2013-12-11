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
    struct genericNode *definedID;
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

/* The global stack that stores the inputs and outputs of functions. */
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

