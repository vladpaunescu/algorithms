/* 
 * File:   copaci.cpp
 * Author: Vlad
 *
 * Created on February 9, 2014, 12:12 AM
 */

#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

typedef struct _point {
    long long x, y;
} Point;

int n;
Point v[100002];

double computeArea() {
    long long x1, x2, y1, y2, S = 0;
    for (int i = 1; i + 1 < n; i++) {
        x1 = v[i].x - v[0].x;
        y1 = v[i].y - v[0].y;
        x2 = v[i + 1].x - v[0].x;
        y2 = v[i + 1].y - v[0].y;
        S += x1 * y2 - x2 * y1;
    }
    S = fabs(S * 0.5);

    return S;
}

long long gcd(long long a, long long b) {
    while (b) {
        long long quot = b;
        b = a % quot;
        a = quot;
    }
    return a;
}

long long myabs(long long a) {
    if (a > 0) return a;
    return -a;
}

int main(int argc, char** argv) {
    freopen("copaci.in", "r", stdin);
    freopen("copaci.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &v[i].x, &v[i].y);
    }

    double area = computeArea();
    long long borderPoints = 0;
    v[n] = v[0];
    for (int i = 0; i + 1 <= n; i++) {
        long long points = gcd(myabs(v[i + 1].x - v[i].x), myabs(v[i + 1].y - v[i].y)) + 1;
        borderPoints += points;
    }

    // we added vertex points 2 times
    borderPoints -= n;

    // pick's theorem  Area = inside + border/2 - 1
    long long insidePoints = area  - borderPoints / 2 + 1;
    printf("%lld\n", insidePoints);

    return 0;
}

