#ifndef AST_IS_H
#define AST_IS_H

#include <stddef.h>

char* is_char( char* );
char* is_ident( char* );
char* is_digit( char* );
char* is_int( char* );
char* is_float( char* );
char* is_number( char* );
char* is_op0( char* );
char* is_op1( char* );
char* is_com( char* );
char* is_lpar( char* );
char* is_rpar( char* );

#endif AST_IS_H