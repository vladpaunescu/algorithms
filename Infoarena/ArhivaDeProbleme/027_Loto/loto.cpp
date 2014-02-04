/* 
 * File:   loto.cpp
 * Author: Vlad
 *
 * Created on February 5, 2014, 12:45 AM
 */

#include <fstream>
#include <algorithm>

using namespace std;

int n, s, a[102], sums[1000000], total;

int binarySearch(int sumRest, int l, int r) {
    int mid;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (sums[mid] == sumRest) return mid;
        if (sums[mid] < sumRest) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int main(int argc, char** argv) {

    ifstream f("loto.in");
    ofstream g("loto.out");

    f >> n >> s;
    for (int i = 1; i <= n; i++) f >> a[i];

    // compute sums of 3 numbers
    int l = 0;

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = j; k <= n; k++) sums[++l] = a[i] + a[j] + a[k];

    total = l;

    sort(sums + 1, sums + total + 1);

    // search for 3 numbers such that sum of them = S - sums[i];
    int index1 = -1, index2 = -1;
    for (int i = 1; i <= total; i++) {
        int index = binarySearch(s - sums[i], 1, total);
        if (index > 0) {
            index1 = i;
            index2 = index;
            break;
        }
    }

    if (index1 == -1) {
        g << index1 << '\n';
        return 0;
    }

    bool found = false;

    for (int i = 1; !found && i <= n; i++)
        for (int j = i; !found && j <= n; j++)
            for (int k = j; k <= n; k++)
                if (sums[index1] == a[i] + a[j] + a[k]) {
                    g << a[i] << " " << a[j] << " " << a[k] << " ";
                    found = true;
                    break;

                }

    found = false;
    for (int i = 1; !found && i <= n; i++)
        for (int j = i; !found && j <= n; j++)
            for (int k = j; !found && k <= n; k++)
                if (sums[index2] == a[i] + a[j] + a[k]) {
                    g << a[i] << " " << a[j] << " " << a[k];
                    found = true;
                    break;
                }

    g << '\n';
    return 0;
}

