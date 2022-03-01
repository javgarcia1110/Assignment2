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
    printf("<student name #1>\n");
    printf("<student name #2 (if no partner write \"N/A\")>\n");
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
    /* Your variable Declarations: */
	
    int i;
    boolean empty;
    boolean result;
    char *op1, *op2;
    Stack *s = createStack();	
    int tokenCount;
    char** arrTokens = tokenizeString( str, &tokenCount );  /* Currently commented out to prevent a memory leak.  Uncomment to get the tokens from str. 	*/
     
	printf("%d", s->top);	


          for(i = 0; i < tokenCount; i++){
        	printf("%s\n", arrTokens[i]);
	  
	       if(*arrTokens[i] == 'T' || 'F'){
		     /*  printf("X IS T OR F\n");*/
                       push(s, arrTokens[i]);
                                }
	       if(strcmp(arrTokens[i], "NOT") == 0){
			printf("REACHED NOT\n");


                        empty = isEmpty(s);
			
			printf("TEST");
			if(empty == TRUE){
			freeStack(s);
			free(arrTokens);
			return booleanToString( ERROR );  
			}
		      
		      


			op1 = pop(s);
			 printf("%s", op1);
			 
		      if(*op1 == 'F'){
			 *op2 = 'T';
		      result = TRUE;
		      }
		      else{
			  *op2 = 'F';
			  result = FALSE;
		      
		      }
			push(s, op2);
		/*	freeStackElements(s);
			free(arrTokens[i]);
*/














		}

	  }



    /* Your code: */

	free(arrTokens);


    return booleanToString( result  ); /* Replace this with your actual solution to return */
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
    int tokenCount;
    char** arrTokens;/* = tokenizeString( str, &tokenCount ); */  /* Currently commented out to prevent a memory leak.  Uncomment to get the tokens from str. */




    /* Your code: */




    return booleanToString( ERROR ); /* Replace this with your actual solution to return */
}


/* You may want to create some helper functions down here! */
