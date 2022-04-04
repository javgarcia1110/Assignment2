#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "stack.h"
#include "booleanEvaluation.h"
#include "booleanWithError.h"


/* TODO
 * printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("Javier Garcia\n");
    printf("N/A\n");
}

/* TODO
 * evaluatePostfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the string)
 * output: T, F, or E
 *
 * Uses a stack to evaluates the postfix expression and returns the result as a string where "T" denotes true and "F" denotes false.
 * If the postfix expression is invalid it returns "E" to denote an error has occurred.  Be sure to use the helpful functions in booleanEvaluation.
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
 */
char *evaluatePostfix( char *str )
{

   /*  Your variable Declarations: */
	
    int i;
    int tokenCount;
    char *op1, *op2;
    Stack *s = createStack();
    char** arrTokens = tokenizeString( str, &tokenCount);  
	


     for(i = 0; i < tokenCount; i++){	
       	if(strequals(arrTokens[i], "T") || strequals(arrTokens[i], "F")){

                push(s, arrTokens[i]);	
	}

	else if(strequals(arrTokens[i], "NOT")){
		 
	 	op1= pop(s);
			
		if(strequals(op1, "T")){
			strcpy(op1, "F");
		}
		else{
			strcpy(op1, "T");

			push(s, op1);		
	}
	}	
 
	 else if(strequals(arrTokens[i], "AND") ||
		strequals(arrTokens[i], "NAND") ||
		strequals(arrTokens[i], "OR") ||
		strequals(arrTokens[i], "NOR") ||
		strequals(arrTokens[i], "XOR") ||
		strequals(arrTokens[i], "COND") ||
		strequals(arrTokens[i], "BICOND")){

		op2 = pop(s);
		op1 = pop(s);

		if(op1 == NULL && op2 == NULL)
			return booleanToString(ERROR);
			
			
		if(strequals(arrTokens[i], "AND"))
			strcpy(op1, booleanToString(stringToBoolean(op1) && stringToBoolean(op2)));				       		     else if(strequals(arrTokens[i], "NAND"))
			strcpy(op1, booleanToString(!(stringToBoolean(op1) && stringToBoolean(op2))));
		else if(strequals(arrTokens[i], "OR"))
			strcpy(op1, booleanToString(stringToBoolean(op1) || stringToBoolean(op2)));
		else if(strequals(arrTokens[i], "NOR"))
			strcpy(op1, booleanToString(!(stringToBoolean(op1) || stringToBoolean(op2))));
		else if(strequals(arrTokens[i], "XOR"))
			strcpy(op1, booleanToString(stringToBoolean(op1) != stringToBoolean(op2)));
		else if(strequals(arrTokens[i], "COND"))
			strcpy(op1, booleanToString(!(stringToBoolean(op1) || stringToBoolean(op2))));
		else if  (strequals(arrTokens[i], "BICOND"))
			strcpy(op1, booleanToString(stringToBoolean(op1) == stringToBoolean(op2)));		


		push(s, op1);
		free(op2);
		return 0;

	}
     
 	
	op1 = pop(s); 

	if(!isEmpty(s)){
	  return booleanToString(ERROR);

	return op1;
	 /* Replace this with your actual solution to return */

     
} 
	


/* TODO
 * postfixToInfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the string)
 * output: the equivalent infix expression
 *
 * Uses a stack to convert str to its equivalent expression in infix.
 * You can assume that the postfix expression is valid
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
 */
char *postfixToInfix( char *str )
{
    /* Your variable Declarations: */
    int i;
    
    char *op1, *op2, *result;
    int tokenCount;
    Stack *s = createStack(); 
    char** arrTokens = tokenizeString( str, &tokenCount );   /* Currently commented out to prevent a memory leak.  Uncomment to get the tokens from str. */

	for(i = 0; i < tokenCount; i++){
	   if(strequals(arrTokens[i], "T") || strequals(arrTokens[i], "F")){
	
  		   push(s, arrTokens[i]);
			
	   }

	   else if(strequals(arrTokens[i], "NOT")){
		   op1 = pop(s);
		   
		   result = arrTokens[i];
		   strcat(result, op1);
		   push(s, booleanToString(*result));
		   free(op1);
		   free(result);
		  
	   }

	   else if((strequals(arrTokens[i], "AND") ||
		strequals(arrTokens[i], "NAND") ||
		strequals(arrTokens[i], "OR") ||
		strequals(arrTokens[i], "NOR") ||
		strequals(arrTokens[i], "XOR") ||
		strequals(arrTokens[i], "COND") ||
		strequals(arrTokens[i], "BICOND"))){

		op2 = pop(s);
		op1 = pop(s);
		
		   
		push(s, booleanToString(*result));
		
		return 0;
	}

	op1 = pop(s);

	return op1; /* Replace this with your actual solution to return */
}


/* You may want to create some helper functions down here! */

char *concatenate( char *str1, char *str2){
    char *dest;
    dest = malloc(strlen(str1)+strlen(str2)+1);
    dest[0] = '\0';
    strcat(dest, str1);
    strcat(dest, str2);
	
    free(str1);
    free(str2);
    
    return dest;
    
	
}


