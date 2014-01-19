/*
   Construirea unui arbore de expresie
 
   Ideea de baza a algoritmului este cea urmarita si in JOB ID 185143
 
   Parcurgem expresia tinand cont de nivelurile subexpresiilor
   si de nivelurile de prioritate a operatorilor
*/
#include <cstdio>
#include <cstring>
 
#define LMAX 2
char op[4][4] = { "+-", "*/", "^", "" };
 
#define NX (1<<17)
char S[ NX ], *p;
 
/*
   In fiecare nod al arborelui, vom retine o valoare (in cazul frunzeolor)
   sau un operator (in cazul nodurilor interne), si doi pointeri catre
   fii stang, respectiv drept ai nodului
 
   Constructorul seteaza toti membrii cu valoarea nula
   *A este un pointer catre radacina arborelui
*/
struct node {
    int val;
    char op;
    node *l, *r;
 
    node( int a = 0, char b = 0, node *c = 0, node *d = 0 ) :
        val(a), op(b), l(c), r(d) {}
} *A;
 
/*
   Functia de constructie a unui arbore de expresie
 
   Functionalitatea este similara celei indicate in sursa 185143
*/
 
node *expr( int lev ) {
    node *x, *y;
     
    if( lev == LMAX )
        if( *p == '(' )
            ++p, x = expr(0), ++p;
        else
            for( x = new node(); *p >= '0' && *p <= '9'; ++p )
                x->val = x->val * 10 + *p - '0';
    else
        for( x = expr( lev+1 ); strchr( op[lev], *p ); x = y )
            y = new node( 0, *p++, x, expr( lev+1 ) );
    return x;
}
 
/*
   Functia de evaluare a unui arbore de expresie
   Se executa operatia din nod asupra fiilor, sau
   se intoarce numarul din nod, in cazul unei frunze
*/
 
int eval( node *n ) {
    switch( n->op ) {
        case '+': return eval( n->l ) + eval( n->r );
        case '-': return eval( n->l ) - eval( n->r );
        case '*': return eval( n->l ) * eval( n->r );
        case '/': return eval( n->l ) / eval( n->r );
        default: return n->val;
    }
}
 
int main() {
    freopen( "evaluare.in", "r", stdin );
    freopen( "evaluare.out", "w", stdout );
 
    fgets( S, NX, stdin ), p = S;
    A = expr( 0 );
    printf( "%d\n", eval( A ) );
 
    return 0;
}