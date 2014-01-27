#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_N = 50001;
int n, dx, dy;
int x[MAX_N], y[MAX_N];

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

