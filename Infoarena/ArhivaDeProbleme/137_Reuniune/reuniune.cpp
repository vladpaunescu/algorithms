/* 
 * File:   reuniune.cpp
 * Author: Vlad
 *
 * Created on January 28, 2014, 11:57 PM
 */

#include <fstream>
#include <algorithm>

using namespace std;

typedef struct _rectangle {
    long long x1, x2, y1, y2;
} Rectangle;

Rectangle intersect(Rectangle& r1, Rectangle& r2) {
    Rectangle r;
    r.x1 = max(r1.x1, r2.x1);
    r.y1 = max(r1.y1, r2.y1);

    r.x2 = min(r1.x2, r2.x2);
    r.y2 = min(r1.y2, r2.y2);

    return r;
}

long long arie(Rectangle& r) {
    if (r.x1 > r.x2 || r.y1 > r.y2) return 0;
    return (r.x2 - r.x1) * (r.y2 - r.y1);
}

long long perim(Rectangle& r) {
    if (r.x1 > r.x2 || r.y1 > r.y2) return 0;
    return 2 * (r.x2 - r.x1 + r.y2 - r.y1);
}

int main(int argc, char** argv) {
    ifstream fin("reuniune.in");
    ofstream fout("reuniune.out");

    Rectangle a, b, c, aub, auc, buc, aubuc;

    fin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
    fin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
    fin >> c.x1 >> c.y1 >> c.x2 >> c.y2;
    
    aub = intersect(a, b);
    auc = intersect(a, c);
    buc = intersect(b, c);
    aubuc = intersect(aub, c);

    long long areaIntersection = arie(a) + arie(b) + arie(c) -
            arie(aub) - arie(auc) - arie(buc) +
            arie(aubuc);
    long long perimIntersection = perim(a) + perim(b) + perim(c) -
            perim(aub) - perim(auc) - perim(buc) +
            perim(aubuc);
    
    fout<<areaIntersection<<' '<<perimIntersection<<'\n';
    fin.close();
    fout.close();
    
    return 0;
}

