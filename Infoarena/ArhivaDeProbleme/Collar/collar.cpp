/* 
 * File:   collar.cpp
 * Author: Vlad
 *
 * Created on February 9, 2014, 2:08 PM
 */

#include <cstdio>
#include <climits>
#include <cmath>

using namespace std;

const int MAX_L = 66000;

int n, v[MAX_L];
int mins[MAX_L][20], maxs[MAX_L][20];
int divs[MAX_L], totalDivs;

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int getMin(int i, int j) {
    if (j < i) j += n;
    int k = floor(log2(j - i + 1));
    if (v[mins[i][k]] <= v[mins[(j - (1 << k) + 1) % n][k]])
        return mins[i][k];

    return mins[j - (1 << k) + 1][k];
}

int getMax(int i, int j) {
    if (j < i) j += n;
    int k = floor(log2(j - i + 1));
    if (v[maxs[i][k]] >= v[maxs[(j - (1 << k) + 1) % n][k]])
        return maxs[i][k];

    return maxs[j - (1 << k) + 1][k];
}

void computeRMQ() {
    int i, j;

    //initialize M for the intervals with length 1
    for (i = 0; i < n; i++)
        mins[i][0] = maxs[i][0] = i;
    //compute values from smaller to bigger intervals
    for (j = 1; 1 << j <= n; j++)
        for (i = 0; i < n; i++) {
            if (v[mins[i][j - 1]] < v[mins[(i + (1 << (j - 1))) % n][j - 1]])
                mins[i][j] = mins[i][j - 1];
            else
                mins[i][j] = mins[(i + (1 << (j - 1))) % n][j - 1];

            if (v[maxs[i][j - 1]] > v[maxs[(i + (1 << (j - 1))) % n][j - 1]])
                maxs[i][j] = maxs[i][j - 1];
            else
                maxs[i][j] = maxs[(i + (1 << (j - 1))) % n][j - 1];
        }
}

int main(int argc, char** argv) {
    freopen("collar.in", "r", stdin);
    freopen("collar.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", v + i);
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) {
            divs[totalDivs++] = i;
        }
    }
    divs[totalDivs++] = n;

    computeRMQ();
   // printf("%d\n",getMin(4,2));
    
    long long maxPower = INT_MIN;
    for (int k = 0; k < totalDivs; k++) {
        int step = divs[k];
        for (int start = 0; start < step; start++) {
            long long totalPower = 0;
            for(int i = start; i < n; i += step){
                int seqMin = v[getMin(i, (i + step - 1) % n)];
                int seqMax = v[getMax(i, (i + step - 1) % n)];
                totalPower += seqMax - seqMin;
   //             printf("%d %d %d %d\n", i,  (i + step - 1) % n,  seqMax, seqMin);
            }
            if (totalPower > maxPower) 
            {
                maxPower = totalPower;
 //               printf("%d %d %d\n\n", step, start, maxPower);
            }
        }
    }
    
    printf("%lld\n", maxPower);

    return 0;
}

