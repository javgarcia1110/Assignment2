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
void printNames()
{
	/* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
	printf("This solution was completed by:\n");
	printf("<student name #1>\n");
	printf("<student name #2 (if no partner write \"N/A\")>\n");
}

/* 
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
char *evaluatePostfix(char *str)
{
	/* Your variable Declarations: */
	int i;
	boolean result;
	char *x;
	char *op1;
	char *op2;
	Stack *s = createStack();
	int tokenCount;
	char **arrTokens = tokenizeString(str, &tokenCount);

	for (i = 0; i < tokenCount; i++)
	{
		x = arrTokens[i];
		if (*x == 'T' || *x == 'F') {
			push(s, x);
		} else if (strequals(x, "NOT")) { /* check for unary operator */
			free(x);
			if (isEmpty(s)) {
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op1 = pop(s);
			result = !stringToBoolean(op1);
			push(s, booleanToString(result));
			free(op1);
		} else if (strequals(x, "AND")) { /* check for binary operator AND */
			free(x);
			if (s->top < 1) {
				freeStackElements(s);
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op2 = pop(s);
			op1 = pop(s);
			result = stringToBoolean(op1);
			result &= stringToBoolean(op2);
			push(s, booleanToString(result));
			free(op1);
			free(op2);
		} else if (strequals(x, "NAND")) { /* check for binary operator NAND */
			free(x);
			if (s->top < 1) {
				freeStackElements(s);
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op2 = pop(s);
			op1 = pop(s);
			result = !(stringToBoolean(op1) && stringToBoolean(op2));
			push(s, booleanToString(result));
			free(op1);
			free(op2);
		} else if (strequals(x, "OR")) { /* check for binary operator OR */
			free(x);
			if (s->top < 1) {
				freeStackElements(s);
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op2 = pop(s);
			op1 = pop(s);
			result = stringToBoolean(op1) || stringToBoolean(op2);
			push(s, booleanToString(result));
			free(op1);
			free(op2);
		} else if (strequals(x, "XOR")) { /* check for binary operator XOR */
			free(x);
			if (s->top < 1) {
				freeStackElements(s);
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op2 = pop(s);
			op1 = pop(s);
			result = stringToBoolean(op1) != stringToBoolean(op2);
			push(s, booleanToString(result));
			free(op1);
			free(op2);
		} else if (strequals(x, "NOR")) { /* check for binary operator NOR */
			free(x);
			if (s->top < 1) {
				freeStackElements(s);
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op2 = pop(s);
			op1 = pop(s);
			result = !(stringToBoolean(op1) || stringToBoolean(op2));
			push(s, booleanToString(result));
			free(op1);
			free(op2);
		} else if (strequals(x, "COND")) { /* check for binary operator COND */
			free(x);
			if (s->top < 1) {
				freeStackElements(s);
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op2 = pop(s);
			op1 = pop(s);
			result = !stringToBoolean(op1) || stringToBoolean(op2);
			push(s, booleanToString(result));
			free(op1);
			free(op2);
		} else if (strequals(x, "BICOND")) { /* check for binary operator BICOND */
			free(x);
			if (s->top < 1) {
				freeStackElements(s);
				freeStack(s);
				free(arrTokens);
				return booleanToString(ERROR);
			} 
			op2 = pop(s);
			op1 = pop(s);
			result = stringToBoolean(op1) == stringToBoolean(op2);
			push(s, booleanToString(result));
			free(op1);
			free(op2);
		} 
	}
	/* check if stack is empty */
	if (s->top > 0) {
		freeStackElements(s);
		freeStack(s);
		free(arrTokens);
		return booleanToString(ERROR);
	}
	op1 = pop(s);
	result = stringToBoolean(op1);
	free(op1);
	freeStack(s);
	free(arrTokens);
	return booleanToString(result); 
}

/* 
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
char *postfixToInfix(char *str)
{
	/* Your variable Declarations: */
	int tokenCount;
	char **arrTokens = tokenizeString( str, &tokenCount ); 
	int i;
	char *op1;
	char *op2;
	char *x;
	Stack *s = createStack();
	char *tmp;

	/* Your code: */
	for(i = 0; i < tokenCount; i++) {
		x = arrTokens[i];
		if(*x == 'T' || *x == 'F') {
			push(s, x);
		} else if(strequals(x, "NOT")) {
			op1 = pop(s);
			tmp = stringcat(x,op1);
			free(op1);
			free(x);
			push(s, tmp);
		} else if(strequals(x, "AND")) {
			op2 = pop(s);
			op1 = pop(s);
			tmp = stringcat2(op1, x, op2);
			free(op1);
			free(op2);
			free(x);
			push(s, tmp);
		} else if(strequals(x, "NAND")) {
			op2 = pop(s);
			op1 = pop(s);
			tmp = stringcat2(op1, x, op2);
			free(op1);
			free(op2);
			free(x);
			push(s, tmp);
		} else if(strequals(x, "OR")) {
			op2 = pop(s);
			op1 = pop(s);
			tmp = stringcat2(op1, x, op2);
			free(op1);
			free(op2);
			free(x);
			push(s, tmp);
		} else if(strequals(x, "XOR")) {
			op2 = pop(s);
			op1 = pop(s);
			tmp = stringcat2(op1, x, op2);
			free(op1);
			free(op2);
			free(x);
			push(s, tmp);
		} else if(strequals(x, "NOR")) {
			op2 = pop(s);
			op1 = pop(s);
			tmp = stringcat2(op1, x, op2);
			free(op1);
			free(op2);
			free(x);
			push(s, tmp);
		} else if(strequals(x, "COND")) {
			op2 = pop(s);
			op1 = pop(s);
			tmp = stringcat2(op1, x, op2);
			free(op1);
			free(op2);
			free(x);
			push(s, tmp);
		}
	}
	return pop(s); /* Replace this with your actual solution to return */
}

/* You may want to create some helper functions down here! */
/* stringcat
 * input: two strings
 * output: boolean
 *
 */
char *stringcat( char *str1, char *str2 ){
    char * new_str ;
	if((new_str = malloc(strlen(str1)+strlen(str2)+6)) != NULL){
		new_str[0] = '\0';
		strcat(new_str,"( ");
		strcat(new_str,str1);
		strcat(new_str," ");
		strcat(new_str,str2);
		strcat(new_str," )");
	} else {
		fprintf(stderr,"malloc failed!\n");
		exit(-1);
	}
	return new_str;
}
char *stringcat2( char *str1, char *str2, char *str3 ){
	char * new_str ;
	if((new_str = malloc(strlen(str1)+strlen(str2)+strlen(str3)+7)) != NULL){
		new_str[0] = '\0';
		strcat(new_str,"( ");
		strcat(new_str,str1);
		strcat(new_str," ");
		strcat(new_str,str2);
		strcat(new_str," ");
		strcat(new_str,str3);
		strcat(new_str," )");
	} else {
		fprintf(stderr,"malloc failed!\n");
		exit(-1);
	}
	return new_str;
}