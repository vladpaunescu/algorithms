#include <iostream>
#include <fstream>
using namespace std;
int m[260][260];

int main() {
    ifstream in("lacate.in");
    ofstream out("lacate.out");
    int n, a, ok, i, j;
    in >> n;
    out << n * (n - 1) / 2 << " " << n - 1 << '\n';
    a = 1;
    for (j = 1; j <= n - 1; j++) {
        ok = 0;
        for (i = j; i <= n; i++) {
            m[i][j] = a;
            if (ok == 1) a++;
            ok = 1;
        }
    }

//    for (i = 1; i <= n; i++) {
//        for (j = 1; j <= n - 1; j++) out << m[i][j] << " ";
//        out << '\n';
//    }
//    
//    out << '\n';

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n - 1; j++) {
            m[i][j] = m[i][j - 1] + 1;
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n - 1; j++) out << m[i][j] << " ";
        out << '\n';
    }
    return 0;
}