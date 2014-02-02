/* 
 * File:   secventa.cpp
 * Author: Vlad
 *
 * Created on January 31, 2014, 2:05 AM
 */

#include <fstream>
#include <assert.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_N = 50002;
int n, k;
int a[MAX_N], s[MAX_N], minS[MAX_N];


ifstream f("secv2.in");
ofstream g("secv2.out");

int main(int argc, char** argv) {

    f >> n >> k;
    for (int i = 1; i <= n; i++) {
        f >> a[i];
    }
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i];
    }

    // Si - Min(Sj), j < i.
    // compute min[i], minimum of sum ending in i
    minS[0] = 0;
    minS[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (s[minS[i - 1]] > s[i]) {
            minS[i] = i;
        } else minS[i] = minS[i - 1];
    }
    int maxLeft = 1, maxRight = n, maxSum = s[n];
    for (int i = k; i <= n; i++) {
        if (s[i] - s[minS[i - k]] > maxSum) {
            maxSum = s[i] - s[minS[i - k]];
            maxLeft = minS[i - k];
            maxRight = i;
        }
    }

    int x, y, smin = INF, smax = -INF;
    for (int i = k; i <= n; i++) {
        if (smin > s[i - k]) {
            smin = s[i - k];
            x = i - k;
        }
        if (s[i] - smin > smax) {
            smax = s[i] - smin;
            y = i;
        }
    }
    
    // assert(x+1 <= maxLeft + 1);
    // assert(y == maxRight);
    // assert(smax >= maxSum);

    g << x + 1 << " " << y << " " << smax << "\n";
    // g << maxLeft + 1 << ' ' << maxRight << ' ' << maxSum << '\n';


    return 0;
}

