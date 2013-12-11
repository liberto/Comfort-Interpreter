#include <stdlib.h>
#include "nodes.h"

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

node copyNode(node n)
{
  node new = (node) malloc (sizeof (struct genericNode));
  
  new->kind = n->kind;
  new->next = n->next;

  if (n->kind == QUOTATION)
    new->contents.quotation = n->contents.quotation;
  else if (n->kind == NUMERAL)
    new->contents.numVal = n->contents.numVal;
  else if (n->kind == BOOLEAN)
    new->contents.boolVal = n->contents.boolVal;
  else
    assert(false);

  return new;
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

