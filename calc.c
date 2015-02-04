#include <stdio.h>

char* is_digit( char *c ) {
	if ( c == NULL ) return NULL;
	switch ( *c ) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return ++c;
		default:
			return NULL;
	}
}

char* is_skip_char( char *c ) {
	if ( c == NULL ) return NULL;
	switch ( *c ) {
		case '\n':
		case '\t':
		case ' ':
			return ++c;
		default:
			return NULL;
	}
}

char* is_separator( char *c ) { 
	if ( c == NULL ) return NULL;
	switch ( *c ) {		
		case ',':
		case '.':
			return ++c;
		default:
			return NULL;
	}
}

char* is_act1( char *c ) {
	if ( c == NULL ) return NULL;
	switch ( *c ) {
		case '+':
		case '-':
			return ++c;
		default:
			return NULL;
	}
}

char* is_int( char *c ) {
	if ( ( c = is_digit( c ) ) == NULL )
		return NULL;
	else 
		if ( is_digit( c ) == NULL )
			return c;
		else
			return is_int( c );
}

char* is_float( char *c ) { 
	return is_int( is_separator( is_int( c ))); 
}

char* is_number( char *c ) {
	char *t;
	if ( ( t = is_float( c ) ) != NULL ) 
		return t;
	else 
		if ( ( t = is_int( c ) ) != NULL )
			return t;
		else 
			return NULL;
}

char* is_skip( char *c ) {
	if ( ( c = is_skip_char( c ) ) == NULL )
		return NULL;
	else
		if ( is_skip_char( c ) == NULL )
			return c;
		else
			return is_skip( c );
}

char* is_expr1( char *c ) {
	return is_number( is_skip ( is_act1( is_skip( is_number( c ) ) ) ) );
}

char *str = "134 + 32.323t";

int main() {
	char *c = str;
	printf( "%c\n", *is_expr1( str ));
}