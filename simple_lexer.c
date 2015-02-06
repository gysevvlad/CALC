#include <stddef.h>
#include <malloc.h>
#include <stdio.h>

/*
	digit = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
	expr = digit '-' expr | digit '+' expr | digit
*/

typedef struct node_st {
	struct node_st *parent, *left, *right;
	char c;
	int id;
} node_t;

node_t* node_create( node_t *l, node_t *r, node_t *p, char c) {
	static int id = 0;
	node_t *node = (node_t*) malloc ( sizeof( node_t ));
	node-> parent = p;
	node-> left = l;
	node-> right = r;
	node-> c = c;
	node-> id = id++;
	return node;
}

void node_destroy( node_t *node ) {
	free( node );
}

char* is_digit( char *c ) {
	char t;
	if ( c == NULL ) return NULL;
	if ( t = *c, t <= '9' && t >= '0' ) 
		return ++c;
	else
		return NULL;
}

char* is_plus( char *c ) {
	char t;
	if ( c == NULL ) return NULL;
	if ( t = *c, t == '+' ) 
		return ++c;
	else
		return NULL;
}

char* is_minus( char *c ) {
	char t;
	if ( c == NULL ) return NULL;
	if ( t = *c, t == '-' ) 
		return ++c;
	else
		return NULL;
}


char* is_expr( char *c ) {
	char *b;
	if ( c == NULL ) return NULL;
	if ( b = is_expr( is_plus( is_digit( c )))) return b;
	if ( b = is_expr( is_minus( is_digit( c )))) return b;
	if ( b = is_digit( c ))
		return b;
	return NULL;
}

node_t* create_digit( char **c ) {
	char t;
	if ( c == NULL  || *c == NULL ) return NULL;
	if ( t = **c, t <= '9' && t >= '0' )
		return (*c)++, node_create( NULL, NULL, NULL, t );
	else 
		return NULL;
	
}

node_t* create_minus( char **c ) {
	char t;
	if ( c == NULL  || *c == NULL ) return NULL;
	if ( t = **c, t == '-' )
		return (*c)++, node_create( NULL, NULL, NULL, t );
	else 
		return NULL;
}

node_t* create_plus( char **c ) {
	char t;
	if ( c == NULL  || *c == NULL ) return NULL;
	if ( t = **c, t == '+' )
		return (*c)++, node_create( NULL, NULL, NULL, t );
	else 
		return NULL;
	
}

node_t* create_expr( char **c ) {
	node_t *p = NULL, *l = NULL, *r = NULL;
	char *b;
	if ( c == NULL || *c == NULL ) return NULL;
	b = *c;

	if (( l = create_digit( &b ) ) && 
		( p = create_plus( &b ) ) && 
		( r = create_expr( &b ) )) {
		*c = b;
		p-> parent = NULL; p-> left = l; p-> right = r;
		p-> left-> parent = p-> right-> parent = p;
		return p;
	}
	else 
		node_destroy( l ), node_destroy( r ), node_destroy( p ), b = *c;

	if (( l = create_digit( &b ) ) && 
		( p = create_minus ( &b ) ) && 
		( r = create_expr( &b ) )) {
		*c = b;
		p-> parent = NULL; p-> left = l; p-> right = r;
		p-> left-> parent = p-> right-> parent = p;
		return p;
	}
	else 
		node_destroy( l ), node_destroy( r ), node_destroy( p ), b = *c;

	if ( p = create_digit( &b ) ) 
		return *c = b, p;
	else 
		node_destroy( p ), b = *c;

	return NULL;
}

void tree_to_gv_rec( node_t *root, FILE *fp ) {
	fprintf( fp, "\tid%d[label=\"%c\"]\n", root-> id, root-> c );
	fprintf( fp, "\tid%d -> id%d\n", root-> parent-> id, root-> id );
	if ( root-> left != NULL )
			tree_to_gv_rec( root-> left, fp );
	if ( root-> right != NULL )
		tree_to_gv_rec( root-> right, fp );
}

int tree_to_gv( char *name, node_t *root, FILE *fp ) {
	fprintf( fp, "digraph %s {\n", name );
	if ( root ) {
		fprintf( fp, "\tid%d[label=\"%c\"]\n", root-> id, root-> c );
		if ( root-> left != NULL )
			tree_to_gv_rec( root-> left, fp );
		if ( root-> right != NULL )
			tree_to_gv_rec( root-> right, fp );
	}
	fprintf( fp, "}\n" );
	return 0;
}

void rec( node_t *node, int t ) {
	int i;
	for( i = 0; i < t; printf("\t"), i++ );
	printf("%c\n", node-> c ), t++;
	if ( node-> left ) rec( node-> left, t);
	if ( node-> right ) rec( node-> right, t );
}

void main( void ) {
	char *data = "1+2-3+4-5+6-7+8-9+0", *t = data;
	node_t *node;
	rec( create_expr( &t ), 0 );
	t = data;
	tree_to_gv( "G", create_expr( &t ), fopen( "graph1.gv", "w" ));
}
