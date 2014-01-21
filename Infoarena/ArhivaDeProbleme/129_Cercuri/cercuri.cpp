/* 
 * File:   luna.cpp
 * Author: Vlad
 *
 * Created on January 17, 2014, 11:54 PM
 */

#include <cstdio>
#include <cmath>

#define EPS 0.0001

using namespace std;

float dist(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main(int argc, char** argv) {
    freopen("cercuri.in", "r", stdin);
    freopen("cercuri.out", "w", stdout);
    int t, x[2], y[2], r[2];
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        scanf("%d %d %d", &x[0], &y[0], &r[0]);
        scanf("%d %d %d", &x[1], &y[1], &r[1]);

        float d = dist(x[0], y[0], x[1], y[1]);
        float sumR = r[0] + r[1];
        float difR = abs(r[0] - r[1]);
  //     printf("%f %f\n", d, sumR);
        if (x[0] == x[1] && y[0] == y[1]) {
            if (r[0] != r[1]) {
                // circles are concentrical, they don't intersect
                printf("-2\n");
            } else{
                // they coincide
                printf("-1\n");
            }
        }else if (d > sumR) {
            // circles don't intersect
            printf("-2\n");
        } else if (abs(d - sumR) <= EPS || abs(difR - d) < EPS) {
            // if( ((Raza+Raza2)*(Raza+Raza2) == (X-X2)*(X-X2) + (Y-Y2)*(Y-Y2) ||
            // (Raza-Raza2)*(Raza-Raza2) == (X-X2)*(X-X2) + (Y-Y2)*(Y-Y2)) )
            // circles intersect in one point
            printf("-3\n");
        } else {
            // circles intersect in 2 points
            float l = 1.0/d * sqrt((-d + r[0] - r[1]) * 
                           (-d - r[0] + r[1]) *
                           (-d + r[0] + r[1]) *
                           ( d + r[0] + r[1]));
            printf("%.3f\n", l);
        }

    }

    return 0;
}

