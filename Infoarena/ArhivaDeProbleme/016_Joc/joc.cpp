/* 
 * File:   joc.cpp
 * Author: Vlad
 *
 * Created on February 1, 2014, 2:09 AM
 */


#include <fstream>
#include <algorithm>

using namespace std;

int n, m;
int a[1002][1002];
int sol[1002][1002];

ifstream in("joc.in");
ofstream out("joc.out");

int main(int argc, char** argv) {
    in >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            in >> a[i][j];
    in.close();

    // sol[ i ][ j ] - maximul  pana la (i,j) 
    // (desigur memorez undeva solutia ca sa fie pe lina si coloana potrivita). 
    // sol[ i ][ j ]=max(sol[ i-1 ][ j ],sol[ i ][ j-1 ],
    //                   a[ i ][ j ] - max (sol[ i ][ j-1 ],sol[ i-1 ][ j ]).

    sol[1][1] = a[1][1];
    int lmax = 1, colmax = 1, solmax = a[1][1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i != 1 || j != 1) {
                sol[i][j] = sol[i - 1][j];
                if (sol[i][j] < sol[i][j - 1]) sol[i][j] = sol[i][j - 1];

                if (i > 1 && j > 1) {
                    int opMax = sol[i][j - 1];
                    if (opMax < sol[i - 1][j]) opMax = sol[i - 1][j];
                    if (sol[i][j] < a[i][j] - opMax) sol[i][j] = a[i][j] - opMax;
                } else if (i > 1 && sol[i][j] < a[i][j] - sol[i - 1][j]) {
                    sol[i][j] = a[i][j] - sol[i - 1][j];
                } else if (j > 1 && sol[i][j] < a[i][j] - sol[i][j - 1]) {
                    sol[i][j] = a[i][j] - sol[i][j - 1];
                }

                if (solmax < sol[i][j]) {
                    solmax = sol[i][j];
                    lmax = i;
                    colmax = j;
                }

            }
        }
    }

//    for (int i = 1; i <= n; ++i) {
//        for (int j = 1; j <= m; ++j)
//            out << sol[i][j] << ' ';
//        out << '\n';
//    }

    out << sol[n][m] << ' ' << lmax << ' ' << colmax << '\n';
    out.close();

    return 0;
}

