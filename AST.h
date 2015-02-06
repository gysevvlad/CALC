#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct node {
	struct node *left, *right, *parent;
	char *str;
	int id;
} node_t;

typedef struct {
	node_t *root;
	char *name;
} AST_t;

size_t AST_init( AST_t*, char*, char* );

int AST_to_gv( AST_t*, FILE* );

double AST_reduce( AST_t* );

node_t* node_create( node_t*, node_t*, node_t*, char* );

void node_destroy( node_t* );

char* str_create( char*, char* );

#endif AST_H