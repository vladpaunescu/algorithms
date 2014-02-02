/* 
 * File:   bool.cpp
 * Author: Vlad
 *
 * Created on February 1, 2014, 6:23 PM
 */

#include <cstdio>

using namespace std;

const int MAX_SIR = 1003;

char sir[MAX_SIR + 1];
int variable[26];
int n;

inline bool isVar(char &c) {
    return c >= 'A' && c <= 'Z';
}

bool evalExpr(char *&exp);
bool evalOr(char *& expr);
bool evalAnd(char *& expr);


bool evalExpr(char * &expr) {

    bool result = evalOr(expr);
    while (expr[1] == 'O' && expr[2] == 'R') {
        expr += 4; // " OR "
        bool right = evalOr(expr);
        result = result || right;
    }
    return result;
}

bool evalOr(char *&expr) {
    bool result = evalAnd(expr);
    while (expr[1] == 'A' && expr[2] == 'N') {
        // AND
        expr += 5; // " AND "
        bool right = evalAnd(expr);
        result = result && right;
    }
    return result;
}

bool evalAnd(char *&expr) {
    bool result = false;
    if (expr[0] == 'T' && expr[1] == 'R') {
        // TRUE
        result = true;
        expr += 4; // "TRUE"
    } else if (expr[0] == 'F' && expr[1] == 'A') {
        // TRUE
        result = false;
        expr += 5; // "FALSE"
    } else if (expr[0] == '(') {
        // (exp)
        expr++; // skip (
        result = evalExpr(expr);
        expr++; // skip )
        return result;
    } else if (expr[0] == 'N' && expr[1] == 'O') {
        // NOT
        expr += 4; // "NOT "
        result = !evalAnd(expr);
    } else if (isVar(expr[0])) {
        result = variable[expr[0] - 'A'];
        expr += 1;
    }
    return result;
}

int main(int argc, char** argv) {

    freopen("bool.in", "r", stdin);
    freopen("bool.out", "w", stdout);

    // citirea datelor
    gets(sir);
    scanf("%d\n", &n);

    char var;
    bool result = false;
    char *position;
    for (int i = 0; i < n; ++i) {
        scanf("%c", &var);
        variable[var - 'A'] = !variable[var - 'A'];
        position = sir;
        // if (var =='U')
        result = evalExpr(position);
        printf("%d", result);
    }
    printf("\n");
    return 0;
}

