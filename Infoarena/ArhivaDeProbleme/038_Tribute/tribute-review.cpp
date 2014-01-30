#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_N = 50001;
int n, dx, dy;
int x[MAX_N], y[MAX_N];

// Varianta asta de counting sort e ceva mai normala si, dupa parerea mea, mai
// usor de inteles:
// * initializez counts cu 0
// * incrementez counts[a[i]], adica numar de cate ori am dat peste elementul a[i]
// * trec prin tot vectorul counts si pun fiecare i de cate ori zice counts[i] ca
//   a aparut in vectorul initial.
void countSort2(int a[], int n) {
    int *counts = new int[MAX_N], last_elem = 0;
    for(int i = 1; i <= n; ++i)
        ++counts[a[i]];
    for(int i = 0; i < MAX_N; ++i)
        for(int j = 0; i < counts[i]; ++j)
            a[++last_elem] = i;
    delete[] counts;
}

// O problema pe care o ai este si faptul ca declari counts pe stiva si e cam
// nasol, mai ales daca MAX_N era mare sau daca functia s-ar fi apelat recursiv.
// Fie folosesti vector<int>, fie aloci memorie dinamic.
// Optimizarea ta cu for(int i = min; i <= max; i++) e cam inutila pentru ca
// oricum fortezi programul sa iti initializeze tot vectorul cu 0 cand il declari
// asa ca o sa ai oricum theta(N) complexitate (i.e. sigur l-ai parcurs odata cand
// l-ai facut 0 pe tot). Nu zic ca e o idee rea, dar e o optimizare prematura si
// nu face decat sa urateasca nitel codul. Mai mult de atat, vectorul tau are 50k
// elemente, nu dureaza mai mult decat una, doua milisecunde toata afacerea ta cu
// sortarea.
void countSort(int a[], int n) {
    int counts[MAX_N] = {0};
    int sorted[n];
    int min = MAX_N, max = 0;
    for (int i = 1; i <= n; ++i) {
        counts[a[i]]++;
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }

    // cumulate counts
    for (int i = min; i <= max; i++) {
        counts[i] += counts[i - 1];
    }
    // counts[i] now contains the number of elements <= i
    for (int i = 1; i <= n; i++) {
        sorted[counts[a[i]]] = a[i];
        counts[a[i]]--;
    }

    for (int i = 1; i <= n; i++) {
        //    printf("%d " , sorted[i]);
        a[i] = sorted[i];
    }
    // printf("\n");
}

// Pare bine.
int solve(int x[], int d, int n) {
    int sumLeft = 0;
    int sumRight = 0;
    int minSum = INT_MAX;

    if (x[n] - x[1] <= d) return 0;

    // compute distance for line at leftmost point
    int leftIndex = 1; // first left index not covered by the line
    int rightIndex = 0; // first right index that's not covered by the line
    for (int i = 1; i <= n; i++) {
        if (x[i] > d) {
            rightIndex = i;
            break;
        }
    }
    for (int i = rightIndex; i <= n; i++) {
        sumRight += (x[i] - d);
    }
    minSum = sumLeft + sumRight;

    // scan with moving line segment 1 by 1 from left to right
    for (int leftPosition = 1; leftPosition <= x[n] - d; ++leftPosition) {
        sumLeft += leftIndex - 1;
        sumRight -= (n - rightIndex + 1);
        while (leftIndex <= n && x[leftIndex] < leftPosition) {
            sumLeft += (leftPosition - x[leftIndex]);
            leftIndex++;
        }
        while (rightIndex <= n && x[rightIndex] <= leftPosition + d) {
            sumRight -= (x[rightIndex] - (leftPosition + d));
            rightIndex++;
        }

        if (sumLeft + sumRight < minSum) minSum = sumLeft + sumRight;

    }
    return minSum;

}

// Frumos.
int main(int argc, char** argv) {
    freopen("tribute.in", "r", stdin);
    freopen("tribute.out", "w", stdout);

    scanf("%d %d %d", &n, &dx, &dy);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    countSort(x, n);
    countSort(y, n);

    int minDistX, minDistY;
    minDistX = solve(x, dx, n);
    minDistY = solve(y, dy, n);
    // printf("%d %d %d\n", minDistX, minDistY, minDistX + minDistY);
    printf("%d\n", minDistX + minDistY);

    return 0;
}

