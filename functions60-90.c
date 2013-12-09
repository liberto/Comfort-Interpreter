/* 
Comfort Compiler Functions 60-90
Patrick Triest, for project in CSC362
*/

#include stdbool.h
#include math.h
#include stdio.h 
#include stdlib.h
#include assert.h


/*
log10: pops the top value, which must be a positive number, from the stack
and pushes its common logarithm onto the stack
*/

void log10()
{
	node first = pop();
	if (first->kind == NUMERAL) {
		first->contents.numVal == log10(first->content.numVal);
	}
	else assert(false);

	push(first);
}

/*
map: pops the top two values V and W, both of which must be quotations; for
        each element X of W, push X onto the stack, execute V, and pop the
        top value Y from the stack and save it; finally, collect the saved
        values of Y into a quotation and push it onto the stack
*/

void map()
{
	node V = pop();//pop the function
	node W = pop();//pop the quotion to be mapped to V
	if (V->kind == QUOTATION && W->kind == QUOTATION) {
		node X = V->contents.quotation;//X is first element of the quotation
		node results = malloc(sizeof(struct genericNode));//the node will store the results of V[X...]
		results->kind = QUOTATION;
		node Y = null;
		results->contents.quotation = Y;//Y store the result of V(X)
		while (X != null){
			push(X);//push the first element of W to the stack
			X = X->next;//move forward X
			quotation_exec(V);//push V(X) to the stack
			node next = Y->next;//save the next node
			Y = pop();//Y = V(X)
			Y->next = next;//point to the correct next node
		}
		push(results);
		freeNode(temp);
		freeNode(X);
		freeNode(Y);
	}
	else assert(false);
}

/*
max: pops the top two values, which must be numbers, from the stack and
        pushes the greater one onto the stack. If they are equal, push the 
        first back to the stack
*/
void max()
{
	node first = pop();
	node second = pop();
	if (first->kind == NUMERAL && second->kind == NUMERAL){
		if (second->contents.numVal > first->contents.numVal){
			push(second);
			freeNode(first);
		}
		else {
			push(first);
			freeNode(second);
		}
	}
	else assert(false);
}

/*
min: pops the top two values, which must be numbers, from the stack and
        pushes the lesser one onto the stack. If they are equal, push the
        first back to the stack.
*/
void min()
{
	node first = pop();
	node second = pop();
	if (first->kind == NUMERAL && second->kind == NUMERAL){
		if (second->contents.numVal < first->contents.numVal){
			push(second);
			freeNode(first);
		}
		else {
			push(first);
			freeNode(second);
		}
	}
	else assert(false);
}

/*
modf: pops the top value, which must be a number, from the stack, and
        pushes its fractional part and its integer part onto the stack
        (leaving the integer part on top and the fractional part in the
        second-from-top position)
*/
void modf()
{
	node first = pop();
	if (first->kind == NUMERAL){
		double value = first->contents.numVal;
		double integer = floor(value);
		double decimal = value - integer;

		node decimal = malloc(sizeof(struct genericNode));
		decimal->kind = NUMERAL;
		decimal->contents.numVal = decimal;
		push(decimal);

		first->contents.numVal = integer;
		push(first);
	}
	else assert(false);
}

/*
neg: pops the top value, which must be a number, from the stack and pushes
        its negative onto the stack
*/
void neg()
{
	node first = pop();
	if (first->kind == NUMERAL){
		double value = first->contents.numVal;
		if (value > 0){
			value = 0 - value;
			first->contents.numVal = value;
		}
		push(first);
	}
	else assert(false);
}

/*
not: pops the top value, which must be Boolean, from the stack and pushes
        its logical negation onto the stack
*/
void not()
{
	node first = pop();
	if (first->kind == BOOLEAN){
		Boolean value = first->contents.boolVal;
		if value
			first->contents.boolVal = false;
		else
			first->contents.boolVal = true;
		push(first);
	}
	else assert(false);
}

/*
null: pops the top value, which must be a quotation, from the stack and
        pushes the true Boolean value onto the stack if the quotation is
        empty and the false Boolean value if it is non-empty
*/
void null()
{
	node first = pop();
	if (first->kind == QUOTATION){
		node empty = malloc(sizeof(struct genericNode));
		empty->kind = BOOLEAN;
		if (first->contents.quotation == null)
			empty->contents.boolVal = true;
		else empty->contents.boolVal = false;
		push(empty);
		freeNode(first);
	}
	else assert(false);
}

/*
nullary: pops the top value V, which must be a quotation; saves a copy of
        the stack; executes V; pushes the top value of the stack onto the
        saved copy of the original stack; empties the stack and replaces it
        with the saved stack
*/
void nullary(){
	node first = pop();
	if (first->kind == QUOTATION){
		stack tempStack = copyStack(globalStack);//copy the stack
		quotation_exec(first);//execute V
		first = pop();
		node tempTop = tempStack->top;//save the prevous top of tempStack
		tempStack->top = first;//push first to top of tempstack
		tempStack->next = tempTop;//connects pointer to rest of tempStack
		globalStack = copyStack(tempStack);
		freeStack(tempStack);
	}
	else assert(false);
}

/*
of: pops the top two values V and W, where V must be a quotation and W must
        be a non-negative integer less than the number of elements of V,
        and pushes the element at zero-based position W in V onto the stack
*/
void of(){
	node V = pop();//V is a quotation
	node W = pop();//W is a non-negative integer < length(V)
	if (V->kind == QUOTATION && W->kind == NUMERAL){
		int elementNum = W->contents.numVal;
		int quoteLength = length(V);   
		if (elementNum < quoteLength {
			int n;
			node elementNode = V->contents.quotation;
			for (n = 0; n < elementNum; n++){
				elementNode = elementNode->next;
			}
			push(elementNode);
			freeNode(V);
			freeNode(W);
		}
		 else assert(false);
	} 
	else assert(false);
}

/*
or: pops the two top values V and W, both of which must be Boolean, from
        the stack and pushes their logical disjunction ("V or W or both")
        onto the stack
*/
void or(){
	node V = pop();
	node W = pop();
	if (V->kind == BOOLEAN && W->kind == BOOLEAN){
		Boolean bool1 = V->contents.boolVal;
		Boolean bool2 = W->contents.boolVal;
		node disjunct = malloc(sizeof(struct genericNode));
		disjunct->kind = BOOLEAN;

		if (bool1 || bool2)
			disjunct->contents.boolVal = true;
		else disjunct->contents.boolVal = false;

		push(disjunct);
		freeNode(V);
		freeNode(W);
	}
	else assert(false);
}

/*
popd: pops the top two values V and W from the stack and pushes V back on,
        discarding W 
*/
void popd(){
	node V = pop();
	node W = pop();
	push(V);
	freeNode(W);
}

/*
pow: pops the two top values V and W (which must be numbers such that
        either V is positive or W is a non-negative integer) and pushes
        the value of V^W back to the stack
*/
void pow(){
	node V = pop();
	node W = pop();
	if (V->kind == NUMERAL && W->kind == NUMERAL){
	 	double base = V->contents.numVal;
		double exponent = W->contents.numVal;
		double result = pow(V , W);
		V->contents.numVal = result;
		push(V);
		freeNode(W);
	}
	else assert(false);
}

/*
pred: pops the top value, which must be an integer, from the stack and
        pushes its predecessor onto the stack
*/
void pred(){
	node num = pop();
	if (num->kind == NUMERAL){
		num->contents.numVal = num->contents.numVal - 1;
		push(num); 
	}
	else assert(false);
}

/*
primrec: pops the top three values U, V, and W, where U must be either a
        non-negative integer or a quotation and V and W must be quotations;
        executes V; if U is a non-negative integer, then for each positive
        integer X from 1 up to and including U, pushes X onto the stack and
        executes W, and if U is a quotation, then for each element Y of U,
        pushes Y onto the stack and executes W
*/
void primrec(){
	node U = pop();//U is an integer or quotation
	node V = pop();//V is a quotation
	node W = pop();//W is a quotation
	if (V->kind == QUOTATION && W->kind == QUOTATION){
		quotation_exec(V);//execute V
		if (U->kind == NUMERAL){//if U is a number
			int numU = U->contents.numVall
			int X;
			node number = malloc(sizeof(struct genericNode));
			number->kind = NUMERAL;
			for (X = 1; X < numU; X++){//n counts up the U
				number->contents.numVal = X;
				push(number);
				quotation_exec(W);
			}
		} else if (U->kind == QUOTATION){//if U is a quotation
			node Y = U->contents.quotation;
			while (Y != null){//for each Y in U
				push(Y);
				quotation_exec(W);
				Y = Y->next;
			}
		} else assert(false);
	} else assert(false);
	freeNode(U);
	freeNode(V);
	freeNode(W);
	freeNode(Y);
}

/*
rem: pops the two top values V and W, both of which must be integers, from
        the stack and pushes  the remainder resulting from the integer
        division of W by V onto the stack
*/
void rem(){
	node V = pop();
	node W = pop();
	if (V->kind == NUMERAL && W->kind == NUMERAL){
		double numerator = W->contents.numVal;
		double denominator = V->contents.numVal;
		double rem = numerator - (denominator * floor(numerator/denominator));
		V->contents.numVal = rem;
		push(V);
		freeNode(Y);
	} else assert(false);
}


/*
rest: pops the top value V, which must be a non-empty quotation, from the
        stack and pushes a quotation containing all but the first element
        of V onto the stack
*/
void rest(){
	node V = pop();
	if (V->kind == QUOTATION){
		if (V->contents.quotation != null){
			V->content.quotation = V-content.quotation->next;
			push(V);
		} else assert(false);
	} else assert(false);
}

/*
rolldown: pops the top three values U, V, and W from the stack and pushes
        them back on again, leaving U in the second-from-top position, V
        in the third-from-top position, and W on top
*/
void rolldown(){
	node U = pop();
	node V = pop();
	node W = pop();
	push(V);
	push(U);
	push(W);
}

/*
rolldownd: pops the top four values U, V, W, and X from the stack and pushes
        them back on again, leaving U on top, V in the third-from-top
        position, W in the fourth-from-top position, and X in the
        second-from-top position 
*/
void rolldownd(){
	node U = pop();
	node V = pop();
	node W = pop();
	node X = pop();
	push(W);
	push(V);
	push(X);
	push(U);
}

/*
rollup: pops the top three values U, V, and W from the stack and pushes
        them back on again, leaving U in the third-from-top position, V on
        top, and W in the second-from-top position 
*/
void rollup(){
	node U = pop();
	node V = pop();
	node W = pop();
	push(U);
	push(W);
	push(V);
}

/*
rollupd: pops the top four values U, V, W, and X from the stack and pushes
        them back on again, leaving U on top, V in the fourth-from-top
        position, W in the second-from-top position, and X in the
        third-from-top position
*/
void rolldownd(){
	node U = pop();
	node V = pop();
	node W = pop();
	node X = pop();
	push(V);
	push(X);
	push(W);
	push(U);
}

/*
rotate: pops the top three values U, V, and W from the stack and pushes
        them back on again, leaving U in the third-from-top position, V in
        the second-from-top position, and W on top
*/
void rotate(){
	node U = pop();
	node V = pop();
	node W = pop();
	push(U);
	push(V);
	push(W);
}

/*
rotated: pops the top four values U, V, W, and X from the stack and pushes
        them back on again, leaving U on top, V in the fourth-from-top
        position, W in the third-from-top position, and X in the
        second-from-top position
*/
void rolldownd(){
	node U = pop();
	node V = pop();
	node W = pop();
	node X = pop();
	push(V);
	push(W);
	push(X);
	push(U);
}

/*
sign: pops the top value V, which must be a number, from the stack and
        pushes -1 onto the stack if V is negative, 0 if V is zero, and 1 if
        V is positive.
*/
void sign(){
	node V = pop();
	if (V->kind ==NUMERAL){
		double value = V->contents.numVal;
		if (value < 0)
			V->contents.numVal = -1;
		else if (value > 0){
			V->contents.numVal = 1;
		}
		else V->contents.numVal = 0;
		push(V);
	} else assert(false);
}

/*
sin: pops the top value, which must be a number, from the stack and pushes
        its sine onto the stack
*/
void sin(){
	node first = pop();
	if (first->kind == NUMERAL){
		first->contents.numVal = sin(first->contents.numVal);
		push(first);
	} else assert(false);
}

/*
sinh: pops the top value, which must be a number, from the stack and pushes
        its hyperbolic sine onto the stack
*/
void sinh(){
	node first = pop();
	if (first->kind == NUMERAL){
		first->contents.numVal = sinh(first->contents.numVal);
		push(first);
	} else assert(false);
}

/*
size: pops the top value V, which must be a quotation, from the stack and
        pushes the number of elements in the quotation onto the stack
*/
void size(){
	node V = pop();
	if (V->kind == QUOTATION){
		int size = 0;
		node temp = V->contents.quotation;
		while (temp != null){
			size++;
			temp = temp->next;
		}
		V->kind = NUMERAL;
		V->contents.numVal = size;
		push(V);
	} else assert(false);
}

/*
small: pops the top value, which must be a quotation, from the stack and
        pushes the true Boolean value onto the stack if the quotation is
        empty or has only one element and the false Boolean value if it has
        two or more elements
*/
void small(){
	node V = pop();
	if (V->kind == QUOTATION){
		if (V->contents.quotation == null && V->contents.quotation->next == null)
				V->contents.boolVal = true;
		else V->contents.boolVal = false;
		V->kind = BOOLEAN;
		push(V);
	} else assert(false);
}

/*
some: pops the top two values V and W, both of which must be quotations,
        from the stack; for each element X of V, pushes X onto the stack,
        executes W, and pops the result, which must be a Boolean, from the
        stack; pushes the true Boolean value onto the stack if at least one
        of the results is true 
*/
void some(){
	node V = pop();
	node W = pop();
	if (V->kind == QUOTATION && W->kind == QUOTATION) {
		node X = V->contents.quotation;//X is first element of the quotation
		node tempNext;
		node result;
		while (X != null){
			tempNext = X->next;
			push(X);
			quotation_exec(W);
			result = pop();
			if (result->kind == BOOLEAN){
				if (result->contents.boolVal){
					push(result);
					X = null;
				}
				else X = tempNext;
			} else assert(false);
		}
	} else assert(false);
}


