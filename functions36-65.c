/* 
Comfort Compiler Functions 36-65
Erik Opavsy, for project in CSC362
*/

#include stdbool.h
#include math.h
#include stdio.h 
#include stdlib.h
#include assert.h

/*
cos: pops the top value, which must be a number, from the stack and pushes
        its cosine onto the stack
*/
void cos()
{
  node first = pop();
  if (first->kind == NUMERAL) {
    first->contents.numVal = cos(first->contents.numVal);
  }
  else
    assert(false);

  push(first);
}

/*
cosh: pops the top value, which must be a number, from the stack and pushes
        its hyperbolic cosine onto the stack
*/
void cosh()
{
  node first = pop();
  if (first->kind == NUMERAL) 
    first->contents.numVal = cosh(first->contents.numVal);
  else
    assert(false);

  push(first);
}

/*
dip: pops the top two values, V and W, from the stack, executes W, and
        pushes V back onto the stack
*/
void dip()
{
  node V = pop();
  node W = pop();

  if (W->kind == QUOATATION) {
    quotation_exec(W);
    push(V);

    freeNode(W);
  }
  else
    assert(false);
}

/*
div: pops the two top values V and W, both of which must be integers, from
        the stack and pushes the quotient Q and remainder R resulting from
        the integer division of W by V onto the stack, leaving Q in the
        second-from-top position and R on top
*/
void div()
{
  node V = pop();
  node W = pop();

  if (V->kind == NUMERAL && W->kind == NUMERAL) {
    int Q;
    double R;
    Q = (int) (W / V);
    R = W - V * Q;
    W->contents.numVal = (double) Q;
    V->contents.numVal = R;

    push(W);
    push(V);
  }
  else
    assert(false);
}

/*
drop: pops the two top values V and W, where W is a quotation and V is a
        non-negative integer less than or equal to the number of elements
        from W, from the stack, and pushes a quotation formed by removing
        from W its first V elements onto the stack
*/
void drop()
{
  node V = pop();
  node W = pop();

  if (V->kind == NUMERAL && 
      V->contents.numVal == (int) V->contents.numVal && 
      V->contents.numVal > 0 && 
      W->kind == QUOTATION) {

    int i;
    node n = w->contents.quotation;
    node temp;
    for (i = 0; i < V->contents.numVal; i++) {
      temp = n;
      n = n->next();
      if (temp != NULL)
        freeNode(temp);
      else
        assert(false);
    }

    w->next = n;
  }
  else
    assert(false);
}

/*
dup: pushes a copy of the stack's top value onto the stack
*/
void dup()
{
  node n = pop();
  node new = copyNode(n);

  push(n);
  push(new);
}

/*
dupd: pops the top value V from the stack, pushes a copy of the new top
        value onto the stack, and pushes V onto the stack
*/
void dupd()
{
  node V = pop();
  dup();
  push(V);
}

/*
enconcat: pops the top three values U, V, and W, where V and W must be
        quotations, from the stack and pushes a quotation formed by
        concatenating W with the result of prepending U to V onto the stack
        result is WUV
*/
void enconcat()
{
  node U = pop();
  node V = pop();
  node W = pop();

  if (V->kind == QUOTATION && W->kind == QUOTATION) {
    node temp = w->contents.quotation;

    while (temp != NULL)
      temp = temp->next;
    temp->next = u;

    u->next = V->contents.quotation;

    free(V);

    push(W);
  }
  else
    assert(false);
}

/*
equal: pops the top two values V and W from the stack and pushes the
        Boolean value true on the stack if V and W are both Boolean values
        and are the same Boolean value, or are both numbers and are equal
        as numbers, or are both quotations, have the same length, and have
        equal elements at each position
// do we push false if we don't push true? This implementation doesn't.
*/
void equal()
{
  node V = pop();
  node W = pop();

  if (V->kind == NUMERAL && W->kind == NUMERAL) {
    if (V->numVal == W->numVal)
      true();
  }
  else if (V->kind == BOOLEAN && W->kind == BOOLEAN) {
    if(V->boolVal == W->boolVal)
      true();
  }
  else if (V->kind == QUOTATION && W->kind == QUOTATION) {
    int truthVal = 1;
    node tempV = V->contents.quotation;
    node tempW = W->contents.quotation;

    // go through all of V
    while (tempV != NULL) {
      if (tempV->contents.quotation != tempW->contents.quotation) {
        truthVal = 0;
        break;
      }
      tempV = tempV->next;
      tempW = tempW->next;
    }

    // check to make sure tempW finished too
    if (tempW != NULL)
      truthVal = 0;

    // if all our tests passed, push true onto the stack
    if (truthVal)
      true();
  }

  freeNode(V);
  freeNode(W);
}

/*
exp: pops the top value V, which must be a number, from the stack and pushes
        the result of raising e, the base of natural logarithms, to the
        power of V onto the stack
*/
void exp()
{
  node V = pop();
 
  if (V->kind == NUMERAL) 
    first->contents.numVal = pow(M_E, V->contents.numVal);
  else
    assert(false);

  push(V);
}

/*
false: pushes the false Boolean value onto the stack
*/
void false()
{
  node f = (node) malloc (sizeof (struct genericNode));
  f->kind = BOOLEAN;
  f->contents.boolVal = false;
  f->next = NULL;
  push(f);
}

/******** NOT IMPLEMENTED ***********/
/*
filter: pops the top two values V and W, both of which must be quotations,
        from the stack; for each element X of V, push X onto the stack,
        execute W, and pop the result Y, which must be a Boolean, from the
        stack; collect the elements X that yielded the true Boolean value
        as a result into a quotation and push it onto the stack
*/
void filter()
{
  node V = pop();
  node W = pop();
  
  if (V->kind == QUOTATION && W->kind == QUOTATION) {
    
    
  }
  else
    assert(false);
}

/*
first: pops the top value V, which must be a non-empty quotation, from the
        stack and pushes the first element of V onto the stack
*/
void first()
{
  node V = pop();
  if (V->kind == QUOTATION && V->contents.quotation != null) {
    push(V->contents.quotation);
    freeNode(V);
  }
  else
    assert(false);
}

/******** NOT IMPLEMENTED ***********/
// how do we indicate imaginary numbers?
/*
float: pops the top value V from the stack and pushes the true Boolean
        value onto the stack if V is a real number, the false Boolean value
        if it is not
*/
void float()
{

}

/*
floor: pops the top value V, which must be a number, from the stack, and
        pushes the greatest integer not greater than V onto the stack
*/
void floor()
{
  node V = pop();
  if (V->kind == NUMERAL) {
    int x = (int) floor(V->contents.numVal);
    V->contents.numVal = (double) x;
    push(V);
  }
  else
    assert(false);
}

/*
fold: pops the top three values U, V, and W, where U and W must be
        quotations; push V back onto the stack; for each element X of W in
        push X onto the stack and execute U
*/
void fold()
{
  node U = pop();
  node V = pop();
  node W = pop();

  if (U->kind == QUOTATION && W->kind == QUOTATION) {
    push(V);

    node temp = W->contents.quotation;
    while (temp != NULL) {
      push(temp);
      quotation_exec(U);
      temp = temp->next;
    }

    freeNode(U);
    freeNode(W);
  }
  else
    assert(false);
}

/******** NOT IMPLEMENTED ***********/
/*
frexp: pops the top value V, which must be a number, from the stack, and
        pushes two values M and E onto the stack (with E on top and M in
        the second-to-top position); if V is zero, M and E are both zero,
        and otherwise M has the same sign as V, the absolute value of M
        lies in the range from 0.5 (inclusive) to 1 (exclusive), and the
        ratio of V to M is 2^E (see the man page on C's frexp function)
*/
void frexp()
{
  node V = pop();

}

/******** NOT IMPLEMENTED ***********/
/*
genrec: pops the top four values U, V, W, and X, which must all be
        quotations, from the stack; executes U; pops the top value Y of the
        stack, which must be Boolean; if Y is true, executes V (which
        terminates the operation, and if Y is false, executes W, then
        executes a five-element quotation consisting of the quotation of U,
        the quotation of V, the quotation of W, the quotation of X, and
        genrec, then executes X 
*/
void genrec()
{
 node U = pop();
  node V = pop();
  node W = pop();
  node X = pop();

  if (U->kind == QUOTATION && 
      V->kind == QUOTATION && 
      W->kind == QUOTATION && 
      X->kind == QUOTATION) {
    quotation_exec(U);
    freeNode(U);

    node Y = pop();
    if (Y->kind == BOOLEAN) {
      if (Y->boolVal) {
        quotation_exec(V);
        freeNode(V);
        freeNode(W);
        freeNode(X);
        freeNode(Y);

      } 
      else {
        quotation_exec(W);
        // then executes a five-element quotation 
        //  consisting of U, V, W, X, genrec, X
      }

    }
    else
      assert(false);
  }
  else
    assert(false);
}

/*
has: pops the top two values V and W, where W must be a quotation, from the
        stack, and pushes the true Boolean value onto the stack if V is an
        element of W, the false Boolean value otherwise
        // should this free V and W at the end? It doesn't say to push them
           back onto the stack...
*/
void has()
{
  node V = pop();
  node W = pop();
  node temp = W->contents.quotation;

  if (W->kind == QUOTATION) {
    int state = 0; // whether we're going to return true of false
    while (temp != NULL) {
      if (temp == V) {
        state = 1;
        break;
      }
    }
  }
  else
    assert(false);

  if (state)
    true();
  else
    false();

  freeNode(V);
  freeNode(W);
}

/*
i: pops the top value from the stack and executes it
*/
void i()
{
  node first = pop();

  if (first->kind == QUOTATION) {
    quotation_exec(first);
    freeNode(first);
  }
  else
    assert(false);
}

/*
id: doesn't do anything at all (no computation, no effect on the stack)
*/
void id()
{
  // easy!
}

/*
ifte: pops the top three values U, V, and W, which must all be quotations,
        from the stack; executes U; pops the top value X, which must be
        Boolean, from the stack; executes V if X is true and W if X is false
*/
void ifte()
{
  node U = pop();
  node V = pop();
  node W = pop();
  
  if (U->kind == QUOTATION && 
      V->kind == QUOTATION && 
      W->kind == QUOTATION) {
    quotation_exec(U);
    freeNode(U);

    node X = pop();
    if (X->kind == BOOLEAN) {
      if (X->boolVal)
        quotation_exec(V);
      else
        quotation_exec(W);
      freeNode(X);
    }
    else
      assert(false);
  }
  else
    assert(false);

  freeNode(V);
  freeNode(W);
}

/*
in: pops the top two values V and W, where V must be a quotation, from the
        stack, and pushes the true Boolean value onto the stack if W is an
        element of V, the false Boolean value otherwise
*/
void in()
{
  node V = pop();
  node W = pop();
  int state = 0; // whether we're going to return true of false
  
  if (V->kind == QUOTATION) {
    node temp = V->contents.quotation;
    while (temp != NULL) {
      if (temp == W) {
        state = 1;
        break;
      }
    }
  }
  else
    assert(false);

  if (state)
    true();
  else
    false();

  freeNode(V);
  freeNode(W);
}

/******** NOT IMPLEMENTED ***********/
/*
infra: pops the top two values V and W, both of which must be quotations,
        from the stack; saves a copy of the stack; empties the stack and
        replaces it with a stack containing the elements of V (the first
        element of V at the top); execute W; convert the resulting stack
        into a quotation X (with the top of the stack as the first
        element); replace the stack with the saved copy; push X onto the
        restored stack
*/
void infra()
{
  node V = pop();
  node W = pop();

  if (V->kind == QUOTATION && W->kind == QUOTATION) {

  }
  else
    assert(false);
}

/*
integer: pops the top value V from the stack and pushes the true Boolean
        value onto the stack if V is an integer, the false Boolean value if
        it is not
*/
void integer()
{
  node V = pop();

  if (V->kind == NUMERAL) {
    if (V->contents.numVal == (int) V->contents.numVal)
      true();
    else
      false();

    freeNode(V);
  }
  else
    assert(false);
}

/*
ldexp: pops the two top values V and W, which must be numbers, from the
        stack and pushes the result of multiplying 2^V by W
*/
void ldexp()
{
  node V = pop();
  node W = pop();

  if (V->kind == NUMERAL && W->kind == NUMERAL) {
    V->contents.numVal = W->contents.numVal * exp(2, V->contents.numVal);
    push(V);
    freeNode(W);
  }
  else
    assert(false);
}

/*
linrec: pops the top four values U, V, W, and X, all of which must be
        quotations, from the stack; executes U; pops the top value Y, which
        must be Boolean, from the stack; if Y is true, executes V (which
        completes the operation), and if Y is false, executes W, then push
        U, V, W, and X back onto the stack (restoring their original
        order), then executes linrec, and finally executes X
*/
void linrec()
{
  node U = pop();
  node V = pop();
  node W = pop();
  node X = pop();

  if (U->kind == QUOTATION && 
      V->kind == QUOTATION && 
      W->kind == QUOTATION && 
      X->kind == QUOTATION) {
    quotation_exec(U);

    node Y  = pop();
    if (Y->kind == BOOLEAN) {
      if (Y->boolVal) {
        quotation_exec(V);
        freeNode(U);
        freeNode(V);
        freeNode(W);
        freeNode(Y);
        push(X);
      }
      else {
        quotation_exec(W);
        push(X);
        push(W);
        push(V);
        push(U);
        linrec();
        X = pop();
        quotation_exec(X);
        freeNode(X);
      }
    }
    else
      assert(false);

  }
  else
    assert(false);

}

/*
list: pops the top value V from the stack and pushes the true Boolean
        value onto the stack if V is a quotation, the false Boolean value
        if it is not
*/
void list()
{
  node V = pop();

  if (V->kind == QUOTATION)
    true();
  else
    false();
  
  freeNode(V);
}

/*
log: pops the top value, which must be a positive number, from the stack
        and pushes its natural logarithm onto the stack
*/
void log()
{
  node first = pop();
  if (first->kind == NUMERAL) {
    first->contents.numVal = log(first->contents.numVal);
  }
  else
    assert(false);

  push(first);
}
