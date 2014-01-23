/* 
 * File:   granita.cpp
 * Author: vpaunescu
 *
 * Created on January 22, 2014, 5:14 PM
 */

#include <cstdio>
#include <vector>
#include <stdlib.h> 
#include <time.h>       /* time */

using namespace std;

typedef struct _Point {
    int a, b;
} Point;

int N;
vector<Point> points;

int comp(Point& p1, Point& p2){
    if(p1.a != p2.a){
        return p1.a - p2.a;
    }
    else{
        return -(p1.a -p2.a);
    }
}

int partition(vector <Point>& ar, int p, int r) {
    /* Lomuto-Partition(A, p, r)
    x = A[r]
    i = p - 1
    for j = p to r - 1
        if A[j] <= x
            i = i + 1
            swap( A[i], A[j] )
    swap( A[i +1], A[r] )
    return i + 1 */
    
    Point tmp;
    int pivot = p + (rand() % (int) (r - p + 1));
    tmp = ar[pivot];
    ar[pivot] = ar[r];
    ar[r] = tmp;
    Point x = ar[r];
    int i = p - 1;
  
    for (int j = p; j <= r - 1; ++j) {
        if (comp(ar[j], x) < 0) {
            i++;
            tmp = ar[j];
            ar[j] = ar[i];
            ar[i] = tmp;
        }
    }

    tmp = ar[r];
    ar[r] = ar[i + 1];
    ar[i + 1] = tmp;
    return i + 1;
}

void quickSort(vector <Point>& ar, int p, int r) {
    if (p < r) {
        int q = partition(ar, p, r);
        quickSort(ar, p, q - 1);
        quickSort(ar, q + 1, r);
    }
}

int main(int argc, char** argv) {

    freopen("granita.in", "r", stdin);
    freopen("granita.out", "w", stdout);

    /* initialize random seed: */
    srand(time(NULL));

    scanf("%d", &N);
    Point p;
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &p.a, &p.b);
        points.push_back(p);
    }

    quickSort(points, 0, points.size() - 1);
    int remove = 0;  
    Point cover = points[0];   
    for (int i = 1; i < N; ++i) {
        if (cover.b > points[i].b) {
            // remove point i
            remove++;
        } else  if (cover.b < points[i].b) {
            cover.b = points[i].b;
        }
    }
    printf("%d\n", remove);



    return 0;
}

