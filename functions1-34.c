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
