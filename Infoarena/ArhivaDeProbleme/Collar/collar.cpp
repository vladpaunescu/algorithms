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
int logs[MAX_L];

inline int min(int a, int b) {
    if (a < b) return a;
    return b;
}

inline int max(int a, int b) {
    if (a > b) return a;
    return b;
}

inline int getMin(int i, int j) {
    int k = logs[j - i + 1];
    if (v[mins[i][k]] <= v[mins[j - (1 << k) + 1][k]])
        return mins[i][k];

    return mins[j - (1 << k) + 1][k];
}

inline int getMax(int i, int j) {
    int k = logs[j - i + 1];
    if (v[maxs[i][k]] >= v[maxs[j - (1 << k) + 1][k]])
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
        for (i = 0; i + (1 << j) - 1 < n; i++) {
            if (v[mins[i][j - 1]] < v[mins[i + (1 << (j - 1))][j - 1]])
                mins[i][j] = mins[i][j - 1];
            else
                mins[i][j] = mins[i + (1 << (j - 1))][j - 1];

            if (v[maxs[i][j - 1]] > v[maxs[i + (1 << (j - 1))][j - 1]])
                maxs[i][j] = maxs[i][j - 1];
            else
                maxs[i][j] = maxs[i + (1 << (j - 1))][j - 1];
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
    
    // compute log2
    for(int i = 1; i < n; i++){
        logs[i] = (int) log2(i);
    }
    
    // printf("%d\n",getMin(4,2));
    int seqMin, seqMax, step;
    long long maxPower = INT_MIN;
    for (int k = 0; k < totalDivs; k++) {
        step = divs[k];
        for (int start = 0; start < step; start++) {
            long long totalPower = 0;
            int i;
            for (i = start; i + step - 1 < n; i += step) {
                seqMin = v[getMin(i, i + step - 1)];
                seqMax = v[getMax(i, i + step - 1)];
                totalPower += seqMax - seqMin;
            }
            if (i < n) {
                int right = i + step - 1 - n;
                seqMin = min(v[getMin(i, n - 1)], v[getMin(0, right)]);
                seqMax = max(v[getMax(i, n - 1)], v[getMax(0, right)]);
                totalPower += seqMax - seqMin;
            }
            if (totalPower > maxPower) {
                maxPower = totalPower;
            }
        }
    }

    printf("%lld\n", maxPower);

    return 0;
}

