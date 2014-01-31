/* 
 * File:   trapez.cpp
 * Author: Vlad
 *
 * Created on January 31, 2014, 11:37 PM
 */

#include <fstream>
#include <algorithm>

using namespace std;

typedef struct _point {
    long long x, y;
} Point;

int n;
Point p[1002];
Point slopes[1002 / 2 * 1001];

ifstream in("trapez.in");
ofstream out("trapez.out");

bool egal(Point &a, Point &b) {
    return (a.x * b.y == b.x * a.y);
}

bool comp(const Point &a, const Point &b) {
    if (a.x * b.y == b.x * a.y) return 0;
    bool r = (a.x * b.y < b.x * a.y);
    if (b.y < 0) r = !r;
    if (a.y < 0) r = !r;
    return r;
}

int main(int argc, char** argv) {
    in >> n;
    for (int i = 1; i <= n; i++) in >> p[i].x >> p[i].y;

    // combinari de n luate cate 2

    int m = 0;
    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            //        out << m << " ";
            slopes[m].x = p[i].x - p[j].x;
            slopes[m++].y = p[i].y - p[j].y;
        }

    sort(slopes, slopes + m, comp);

    long long trapeze = 0;
    long long equal = 1;
    for (int i = 1; i < m; ++i) {
        if (egal(slopes[i - 1], slopes[i])) equal++;
        else {
            // combinari de n luate cate 2
            trapeze += (equal * equal - equal) / 2;
            equal = 1;
        }
    }
    trapeze += (equal * equal - equal) / 2;

    out << trapeze << '\n';
    out.close();

    return 0;
}

