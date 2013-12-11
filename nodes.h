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

void push(node in);
node pop();
node copyStackHelper(node curNode);
stack copyStack(stack origStack);
void freeList(node in);
void freeNode(node in);
void freeStack(stack in);
bool quotationEquals(node a, node b);
bool nodeEquals(node a, node b);
void append(node appendee, node quotation);
