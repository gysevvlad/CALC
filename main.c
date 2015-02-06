#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "AST.h"

void main( void ) {
	char buff[256];
	AST_t AST;

	gets( buff );
	buff[ AST_init( &AST, "G", buff ) ] = '\0';
	puts( buff );
	printf( "%f\n", AST_reduce( &AST ));
	AST_to_gv( &AST, fopen( "graph.gv", "w" ) );
}


/*
->	char = 'a' | .. | 'z' | 'A' | .. | 'Z'
->	ident = char ident | char
->	digit = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
->	int = digit int | digit
->	float = int '.' int
->	number = int | float
->	op0 = '+' | '-'
->	expr0 = expr1 op0 expr0 | expr1 
->	op1 = '*' | '/'
->	expr1 = factor op1 expr1 | factor
->	args = expr0 ',' args | expr0
->	call = ident '(' args ')'
->	factor = call | number | '(' expr0 ')' | ident
*/
