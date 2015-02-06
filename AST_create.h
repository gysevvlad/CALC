#ifndef AST_CREATE_H
#define AST_CREATE_H

#include "AST.h"
#include "AST_is.h"

node_t* create_ident( char** );
node_t* create_number( char** );
node_t* create_op1( char** );
node_t* create_op0( char **);
node_t* create_expr0( char** );
node_t* create_expr1( char** );
node_t* create_factor( char** );
node_t* create_com( char** );
node_t* create_args( char** );
node_t* create_call( char** );

#endif AST_CREATE_H
