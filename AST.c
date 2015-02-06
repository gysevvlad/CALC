#include "AST.h"
#include "AST_is.h"
#include "AST_create.h"

/*

	char = 'a' | .. | 'z' | 'A' | .. | 'Z'
-	ident = char ident | char
	digit = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
	int = digit int | digit
	float = int '.' int
	number = int | float
	op0 = '+' | '-'
	expr0 = expr1 op0 expr0 | expr1 
	op1 = '*' | '/'
	expr1 = factor op1 exp1 | factor
	args = expr0 ',' args | expr0
-	call = ident '(' args ')'
+/-	factor = ident '(' args ')' | number | '(' expr0 ')'	

*/

node_t* node_create( node_t*, node_t*, node_t*, char* );
void node_destroy( node_t* );

char* str_create( char*, char* );
void tree_to_gv_rec( node_t*, FILE* );
double AST_reduce_rec( node_t* );

size_t AST_init( AST_t *AST, char *name , char *buff ) {
	char *t = buff;
	AST-> root = create_expr0( &t );
	AST-> name = name;
	return t - buff;
} 

int AST_to_gv( AST_t *AST, FILE *	fp ) {
	node_t *root = AST-> root;
	fprintf( fp, "digraph %s {\n", AST-> name );
	if ( root ) {
		fprintf( fp, "\tid%d[label=\"%s\"]\n", root-> id, root-> str );
		if ( root-> left != NULL )
			tree_to_gv_rec( root-> left, fp );
		if ( root-> right != NULL )
			tree_to_gv_rec( root-> right, fp );
	}
	else 
		fprintf( fp, "NULL\n" );
	fprintf( fp, "}\n" );
	return 0;
}

double AST_reduce( AST_t *AST ) {
	if ( !AST-> root ) return 0;
	return AST_reduce_rec( AST-> root );
}

node_t* node_create( node_t *l, node_t *r, node_t *p, char *str) {
	static int id = 0;
	node_t *node = (node_t*) malloc ( sizeof( node_t ));
	node-> parent = p;
	node-> left = l;
	node-> right = r;
	node-> str = str;
	node-> id = id++;
	return node;
}

void node_destroy( node_t *node ) {
	if ( node ) {
		free( node-> str );
		free( node );
	}
}

char* str_create( char *s, char *e ) {
	char *t;
	size_t k;
	k = e - s;
	t = (char*) malloc( k + 1 );
	memcpy( t, s, k );
	t[k] = '\0';
	return t;
}

double AST_reduce_rec( node_t *node ) {
	double l, r;
	switch (node-> str[0]) {
		case '+':
			return AST_reduce_rec( node-> left ) + AST_reduce_rec( node-> right );
		case '-':
			return AST_reduce_rec( node-> left ) - AST_reduce_rec( node-> right );
		case '*':
			return AST_reduce_rec( node-> left ) * AST_reduce_rec( node-> right );
		case '/':
			return AST_reduce_rec( node-> left ) / AST_reduce_rec( node-> right );
		default:
			return atof( node-> str );
	}
}

void tree_to_gv_rec( node_t *root, FILE *fp ) {
	fprintf( fp, "\tid%d[label=\"%s\"]\n", root-> id, root-> str );
	fprintf( fp, "\tid%d -> id%d\n", root-> parent-> id, root-> id );
	if ( root-> left != NULL )
			tree_to_gv_rec( root-> left, fp );
	if ( root-> right != NULL )
		tree_to_gv_rec( root-> right, fp );
}



