#ifndef _booleanEvaluation_h
#define _booleanEvaluation_h

#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "booleanWithError.h"
#include "tokenizeString.h"

void printNames( );
char *evaluatePostfix( char *str );
char *postfixToInfix( char *str );
char *stringcat( char *str1, char *str2 );
char *stringcat2( char *str1, char *str2, char *str3 );

#endif
