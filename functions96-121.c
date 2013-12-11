


void split(){
  node first = pop();
  node second = pop();
  
  if(first->kind == QUOTATION && second->kind == QUOTATION){
    tempNode = first->contents.quotation;
    
    stack trueStack;
    trueStack->top = NULL;
    stack falseStack;
    falseStack->top = NULL;
	
    node ture_quot = malloc(sizeof(struct(genericNode)));
    ture_quot->kind = QUOTATION;
    node false_quot = malloc(sizeof(struct(genericNode)));
    false_quot->kind = QUOTATION;

    while(tempNode->next){
      tempNode2 = tempNode->next;
      push(tempNode);
      quotation_exec(second);
      
      node result = pop();
      if(result->kind == BOOLEAN){
        if(result->contents.boolVal){
          tempNode->next = trueStack->top;
          trueStack->top = tempNode;
          
        }else{
          tempNode->next = falseStack->top;
          falseStack->top = tempNode;
          
        }
      }else
        assert(false);

      tempNode = tempNode2;
    }

    ture_quot->contents.quotation = trueStack->top;     
    false_quot->contents.quotation = falseStack->top;
    push(true_quot);
    push(false_quot);    
  }else
    assert(false);

}

void sqrt(){
  node first = pop();

  if (first->kind == NUMERAL &&
      first->contents.numVal >= 0){
    first->contents.numVal = sqrt(first->contents.numVal);
    push(first);    
  }else
    assert(false);      
}

void stack(){
  node quot = malloc(sizeof(struct(genericNode)));
  quot->kind = QUOTATION;
  quot->next = NULL;
  
  tempStack = copyStack(globalStack);

  quot->contents.quotation = tempStack->top;

  push(quot);
  free(tempStack);
}

void succ(){
  node first = pop();

  if (first->kind == NUMERAL && (first->contents.numVal == floor(first->contents.numVal))){
    first->contents.numVal += 1;
    push(first);
  }
  else
    assert(false);
}

void swap(){
  node first = pop();
  node second = pop();
  
  push(first);
  push(second);
}

void swapd(){
  node first = pop();
  node second = pop();
  node third = pop();
  
  push(second);
  push(third);
  push(first);
}

void swons(){
  node first = pop();
  node second = pop();
  
  if(second->kind == QUOTATION){
    first->contents.next = second->contents.quotation;
    second->contents.quotation = first;
    push(second);
  }else
    assert(false);
}

void tailrec(){
  node first = pop();
  node second = pop();
  node third = pop();

  if(first->kind == QUOTATION && second->kind == QUOTATION && third->kind == QUOTATION){
    quotation_exec(first);
    
    node fourth = pop();
    if (fourth->kind == BOOLEAN){
      if(fourth->contents.boolVal){
        quotation_exec(second);
        
      }else{
        quotation_exec(third);

        push(third);
        push(second);
        push(first);     
        
        tailrec();
      }       
    }
    else
      assert(false);    
  }else
    assert(false);
}

void take(){
  node first = pop();
  node second = pop();
  
  if(first->kind == NUMERAL && 
     (first->contents.numVal == floor(first->contents.numVal)) &&  
     (first->contents.numVal >= 0) && 
     second->kind == QUOTATION){
    
    int i = 1;
    node tempNode = second->contents.quotation;

    while(tempNode->next && first->contents.numVal > i){
      i++;
      tempNode = tempNode->next;
    }
    freeNode(first);
    freeList(tempNode->next);
   
    push(second);
  }else
    assert(false);
}

void tan(){
  node first = pop();

  if (first->kind == NUMERAL)
    first->contents.numVal = tan(first->contents.numVal);
  else
    assert(false);
  
  push(first);
}

void tanh(){
  node first = pop();

  if (first->kind == NUMERAL)
    first->contents.numVal = tanh(first->contents.numVal);
  else
    assert(false);

  push(first);
}

void ternary(){

  node first = pop();
  node second = pop();
  node third = pop();
  node fourth = pop();
  
  if(first->kind == QUOTATION){
    tempStack = copyStack(globalStack);

    push(fourth);
    push(third);
    push(second);

    quotation_exec(first);

    node topNode = pop();
    topNode->next = tempStack->top;
    tempStack->top = topNode;
    
    freeStack(globalStack);
    globalStack = tempStack;
  }else
    assert(false);
}

void times(){
  node first = pop();
  node second = pop();
  
  if (first->kind == NUMERAL && 
      (first->contents.numVal == floor(first->contents.numVal)) &&  
      (first->contents.numVal >= 0) && 
      second->kind == QUOTATION){
    
    int i;
    for(i = 0; i < first->contents.numVal; i++){
      quotation_exec(second);
    }
  }else
    assert(false);
}

void treegenrec(){
  node first = pop();
  node second = pop();
  node third = pop();
  node fourth = pop();

  if(second->kind == QUOTATION && third->kind == QUOTATION && fourth->kind == QUOTATION){
    if (first->kind == QUOTATION){
      quotation_exec(third);
      
      node temp = malloc(sizeof(struct(genericNode)));
      
      temp->contents.reservedID = TREEGENREC;
      temp->kind = BASIC_OP;
      temp->next = NULL;
      
      append(temp, fourth->contents.quotation);
      append(fourth->contents.quotation, third->contents.quotation);
      append(third->contents.quotation, second->contents.quotation);

      push(temp);            
      quotation_exec(fourth);
      
    }else
      quotation_exec(second);
  }else
    assert(false);
}


void treerec(){
  node first = pop();
  node second = pop();
  node third = pop();

  if(second->kind == QUOTATION && third->kind == QUOTATION){
    if (first->kind == QUOTATION){
      node temp = malloc(sizeof(struct(genericNode)));
      
      temp->contents.reservedID = TREEREC;
      temp->kind = BASIC_OP;
      temp->next = NULL;
      
      append(temp, third->contents.quotation);
      append(third->contents.quotation, second->contents.quotation);
                          
      push(temp);
      quotation_exec(third);

    }else{
      quotation_exec(second);
    }
  }else
    assert(false);
}


void treestep(){
  node first = pop();
  node second = pop();

  if(second->kind == QUOTATION){
    if (first->kind == QUOTATION){
      
      node tempNode = first->contents.quotation;
      
      while(tempNode->next){
        tempNode2 = tempNode->next;
        push(tempNode);
        push(second);
        treestep();
        tempNode = tempNode2;
      }
    }else{
      push(first);
      quotation_exec(second);
    }
  }else
    assert(false);
}

void true(){
  node temp = malloc(sizeof(struct(genericNode)));
  temp->contents.boolVal = true;
  temp->kind = BOOLEAN; 
  push(temp);
}

void trunc(){
  node first = pop();

  if (first->kind == NUMERAL)
    first->contents.numVal = trunc(first->contents.numVal);
  else
    assert(false);
  
  push(first);
  free(first);
}

void unary(){
  node first = pop();
  node second = pop();
  
  if(first->kind == QUOTATION){

    tempStack = copyStack(globalStack);
    push(second);
    quotation_exec(first);
  
    node topNode = pop();
    topNode->next = tempStack->top;
    tempStack->top = topNode;
    
    freeStack(globalStack);
    globalStack = tempStack;

  }else
    assert(false);
}

void unary2(){
  node first = pop();
  node second = pop();

  if(first->kind == QUOTATION){
    tempStack = copyStack(globalStack);

    push(second);
    quotation_exec(first);
    
    node topNode1 = pop();
    node topNode2 = pop();
    
    topNode1->next = topNode2;
    topNode2->next = tempStack->top;
    tempStack->top = topNode1;
    
    freeStack(globalStack);
    globalStack = tempStack;
  }else
    assert(false);

}

void unary3(){
  node first = pop();
  node second = pop();

  if(first->kind == QUOTATION){
    tempStack = copyStack(globalStack);

    push(second);
    quotation_exec(first);

    node topNode1 = pop();
    node topNode2 = pop();
    node topNode3 = pop();
    
    topNode1->next = topNode2;
    topNode2->next = topNode3;
    topNode3->next = tempStack->top;
    tempStack->top = topNode1;
    
    freeStack(globalStack);
    globalStack = tempStack;

  }else
    assert(false);
}

void unary4(){
  node first = pop();
  node second = pop();

  if(first->kind == QUOTATION){
    tempStack = copyStack(globalStack);

    push(second);
    quotation_exec(first);

    node topNode1 = pop();
    node topNode2 = pop();
    node topNode3 = pop();
    node topNode4 = pop();

    topNode1->next = topNode2;
    topNode2->next = topNode3;
    topNode3->next = topNode4;
    topNode4->next = tempStack->top;
    tempStack->top = topNode1;

    freeStack(globalStack);
    globalStack = tempStack;

  }else
    assert(false);
}

void uncons(){
  node first = pop();
  if (first->kind == QUOTATION && first->contents.quotation != NULL){
    node tempfirst = first->contents.quotation;
    node tempNext = first->contents.quotation->next;

    push(tempfirst);

    first->contents.quotation = tempNext;
    push(first);
    
  }else
    assert(false);
}

void unstack(){
  node first = pop();
  if (first->kind == QUOTATION){
    while(globalStack->top){
      node discard = pop();
      freeNode(discard);
      globalStack->top = globalStack->top->next;
    }

    tempNode = first->contents.quotation;
    
    unstack_helper(tempNode){
      unstack_helper(tempNode->next);
      push(tempNode);
    }
  }else
    assert(false);
}

void unswons(){
  node first = pop();
  if (first->kind == QUOTATION && first->contents.quotation != NULL){
    node tempfirst = first->contents.quotation;
    node tempNext = first->contents.quotation->next;

    first->contents.quotation = tempNext;
    push(first);
    
    push(tempfirst);
  }else
    assert(false);
}

void while(){
  node first = pop();
  node second = pop();
  
  if(first->kind == QUOTATION && second->kind == QUOTATION){
    quotation_exec(first);

    node topNode = pop();
    if (topNode->kind == BOOLEAN){
      while(topNode->contents.boolVal){
        quotation_exec(second);
        quotation_exec(first);
        node topNode = pop();
      }      
    }
    else
      assert(false);
  }else
    assert(false);
 }

void x(){
  if (globalStack->top->kind == QUOTATION){
    quotation_exec(globalStack->top);
  }elseif (globalStack->top->kind == BASIC_OP || globalStack->top->kind == IDENTIFIER){
    instruction_exec(globalStack->top);
  }elseif (globalStack->top->kind == NUMERAL){
    node temp = malloc(sizeof(struct(genericNode)));   
    temp->kind = NUMERAL;
    temp->contents.numVal = globalStack->top->contents.numVal;
    push(temp);
  }elseif (globalStack->top->kind == BOOLEAN){
    node temp = malloc(sizeof(struct(genericNode)));   
    temp->kind = BOOLEAN;
    temp->contents.boolVal = globalStack->top->contents.boolVal;
    push(temp);
  }else
     assert(false);
}

void xor(){
  node first = pop();
  node second = pop();

  if(first->kind == BOOLEAN && second->kind == BOOLEAN){
    second->contents.boolVal = ((first->contents.boolVal && second->contents.boolVal) || (!(first->contents.boolVal) && !(second->contents.boolVal)));
    push(second);
    freeNode(first);
  }else
    assert(false);
}
