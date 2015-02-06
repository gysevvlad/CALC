#include "AST_is.h"

char* is_char( char* c ) {
	char t;
	if ( c == NULL ) return NULL;
	if ( t = *c, t >= 'a' && t <= 'z' ||
		t >= 'A' && t <= 'Z' ) 
		return ++c;
	return NULL;	
}

char* is_ident( char *c ) {
	char *t;
	if ( c == NULL ) return NULL;
	if ( t = is_ident( is_char( c )))
		return t;
	if ( t = is_char( c ) )
		return t;
	return NULL;
}

char* is_digit( char* c ) {
	if ( c == NULL ) return NULL;
	if ( *c >= '0' && *c <= '9' ) return ++c;
	return NULL;
}

char* is_int( char* c ) {
	char *t;
	if ( c == NULL ) return NULL;
	if ( t = is_int( is_digit( c ))) 
		return t;
	if ( t = is_digit( c ))
		return t;
	return NULL;
}

char* is_float( char* c ) {
	char *t;
	if ( c == NULL ) return NULL;
	if (( t = is_int( c )) && 
		( *t  == '.') && 
		( t = is_int( t + 1 )))
		return t;
	return NULL;
}

char* is_number( char* c ) {
	char *t;
	if ( c == NULL ) return NULL;
	if ( t = is_float( c ) )
		return t;
	if ( t = is_int( c ) ) 
		return t;
	return NULL;
}

char* is_op0( char* c ) {
	char t;
	if ( c == NULL ) return NULL;
	if ( t = *c, t == '-' || t == '+' )
		return ++c;
	return NULL;
}

char* is_op1( char* c ) {
	char t;
	if ( c == NULL ) return NULL;
	if ( t = *c, t == '*' || t == '/' )
		return ++c;
	return NULL;
}

char* is_com( char* c ) {
	if ( c == NULL ) return NULL;
	if ( *c == ',' )
		return ++c;
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