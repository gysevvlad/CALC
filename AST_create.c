#include "AST_create.h"


node_t* create_ident( char **c ) {
	char *s, *e, *t;
	node_t *node;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;
	if ( e = is_ident( s ) )
		return *c = e, node_create( NULL, NULL, NULL, str_create( s, e ) );	
	else
		return NULL;
}

node_t* create_number( char **c ) {
	char *s, *e, *t;
	node_t *node;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;
	if ( e = is_number( s ) )
		return *c = e, node_create( NULL, NULL, NULL, str_create( s, e ));
	else
		return NULL;			
}

node_t* create_op0( char **c ) {
	char *s, *e, t;
	node_t *node;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;
	if ( e = is_op0( s )) 
		return *c = e, node_create( NULL, NULL, NULL, str_create( s, e ));
	return NULL;
}

node_t* create_op1( char **c ) {
	char *s, *e, t;
	node_t *node;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;
	if ( e = is_op1( s )) 
		return *c = e, node_create( NULL, NULL, NULL, str_create( s, e ));
	return NULL;
}

node_t* create_com( char **c ) {
	char *s, *e;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;
	if ( e = is_com( s )) 
		return *c = e, node_create( NULL, NULL, NULL, str_create( s, e ));
	return NULL;
}

node_t* create_expr0( char**c ) {
	node_t *l = NULL, *r = NULL, *p = NULL;
	char *s;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;

	if (( l = create_expr1( &s )) &&
		( p = create_op0( &s )) &&
		( r = create_expr0( &s ))) {
			p-> left = l; l-> parent = p;
			p-> right = r; r-> parent = p;
			*c = s;
			return p;
		}
	else {
		s = *c;
		node_destroy( l ), l = NULL;
		node_destroy( r ), r = NULL;
		node_destroy( p ), p = NULL;
	}

	if ( p = create_expr1( &s ) ) 
		return *c = s, p;
	else 
		s = *c, node_destroy( p ), p = NULL;

	return NULL;
}

node_t* create_expr1( char**c ) {
	char *s, *e, *t;
	node_t *l = NULL, *r = NULL, *p = NULL;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;

	if ( l = create_factor( &s ))
		if (( p = create_op1( &s )) && s != *c )
			if (( r = create_expr1( &s )) && s != *c ) {
				p-> left = l; l-> parent = p;
				p-> right = r; r-> parent = p;
				return *c = s, p; }
	s = *c;
	node_destroy( l ), l = NULL;
	node_destroy( r ), r = NULL;
	node_destroy( p ), p = NULL;

	if ( p = create_factor( &s ) )
		return *c = s, p;
	else 
		s = *c, node_destroy( p ), p = NULL;

	return NULL;
}

node_t* create_args( char**c ) {
	char *s, *e, *t;
	node_t *l = NULL, *r = NULL, *p = NULL;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;

	if (( l = create_expr0( &s )) &&
		( p = create_com( &s )) && s != *c &&
		( r = create_args( &s )) && s != *c ) {
			p-> left = l; l-> parent = p;
			p-> right = r; r-> parent = p;
			*c = s;
			return p;
		}
	else {
		s = *c;
		node_destroy( l ), l = NULL;
		node_destroy( r ), r = NULL;
		node_destroy( p ), p = NULL;
	}

	if ( p = create_expr0( &s ) )
		return *c = s, p;
	else 
		s = *c, node_destroy( p ), p = NULL;

	return NULL;
}

node_t* create_call( char **c ) {
	char *s, *e, *t, *data = "call";
	node_t *l = NULL, *r = NULL, *p = NULL;
	if (c == NULL || *c == NULL || **c == '\0') return NULL;
	s = *c;

	if (( l = create_ident( &s )) &&
		( s = is_lpar( s )) &&
		( r = create_args( &s )) &&
		( s = is_rpar( s ))) {
		p = node_create( l, r, NULL, str_create( data, data + 4 ));
		l-> parent = r-> parent = p;
		return *c = s, p;
	}
	else {
		s = *c;
		node_destroy( l ), l = NULL;
		node_destroy( r ), r = NULL;
	}

	return NULL;
}

node_t* create_factor( char**c ) {
	char *s, *e, *t;
	node_t *l = NULL, *r = NULL, *p = NULL;
	if ( c == NULL || *c == NULL || **c == '\0' ) return NULL;
	s = *c;

	if ( s = is_lpar( s ))
		if ( p = create_expr0( &s ) )
			if ( s = is_rpar( s ) )
				return *c = s, p;
	s = *c, node_destroy( p ), p = NULL;

	/*
	if ( p = create_call( &s )) 
		return *c = s, p;
	*/

	if ( p = create_number( &s ))
		return *c = s, p;

	/*
	if ( p = create_ident( &s ))
		return *c = s, p;
	*/

	return NULL;
}