#include <stddef.h>
#include <stdio.h>

/*
digit -> '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
expr0 -> expr1 '+' expr0 | expr1 '-' expr0 | expr1
expr1 -> factor '*' expr1 | factor '/' expr1 | factor
factor -> digit | '(' expr0 ')'
*/

char* is_digit( char* );
char* is_plus( char* );
char* is_minus( char* );
char* is_mul( char* );
char* is_div( char* );
char* is_lpar( char* );
char* is_rpar( char* );
char* is_expr( char* );
char* is_expr1( char* );
char* is_factor( char* );

char* is_digit( char* c ) {
	if ( c == NULL ) return NULL;
	if ( *c >= '0' && *c <= '9' ) return ++c;
	return NULL;
}

char* is_plus( char* c ) {
	if ( c == NULL ) return NULL;
	if ( *c == '+' ) return ++c;
	return NULL;
}

char* is_minus( char* c ) {
	if ( c == NULL ) return NULL;
	if ( *c == '-' ) return ++c;
	return NULL;
}

char* is_mul( char* c ) {
	if ( c == NULL ) return NULL;
	if ( *c == '*' ) return ++c;
	return NULL;
}

char* is_div( char* c ) {
	if ( c == NULL ) return NULL;
	if ( *c == '/' ) return ++c;
	return NULL;
}

char* is_lpar( char *c ) {
	if ( c == NULL ) return NULL;
	if ( *c == '(' ) return ++c;
	return NULL;
}

char* is_rpar( char *c ) {
	if ( c == NULL ) return NULL;
	if ( *c == ')' ) return ++c;
	return NULL;
}

char* is_expr0( char *c ) {
	char *b;
	if ( c == NULL ) return NULL;
	if ( b = is_expr0( is_plus( is_expr1( c ) ) ) ) return b;
	if ( b = is_expr0( is_minus( is_expr1( c ) ) ) ) return b;
	if ( b = is_expr1( c ) ) return b;
	return NULL;
}

char* is_expr1( char *c ) {
	char *b;
	if ( c == NULL ) return NULL;
	if ( b = is_expr1( is_mul( is_factor( c ) ) ) ) return b;
	if ( b = is_expr1( is_div( is_factor( c ) ) ) ) return b;
	if ( b = is_factor( c ) ) return b;
	return NULL;
}

char* is_factor( char* c ) {
	char *b;
	if ( c == NULL ) return NULL;
	if ( b = is_rpar( is_expr0( is_lpar( c ) ) ) ) return b;
	if ( b = is_digit( c ) ) return b;
	return NULL;
}

char *data = "(2+4/(1-4*(3-(4*2-4)))-1)-(2+2)";

void main( void ) {
	char buff[256], *r;
	if ( fgets( buff, 256, stdin ) ) {
		r = is_expr0( buff );
		if ( !r ) return;
		else {
			*r = '\0';
			puts( buff );
		}
	}
}