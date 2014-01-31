/* 
 * File:   secventa.cpp
 * Author: Vlad
 *
 * Created on January 31, 2014, 2:05 AM
 */

#include <fstream>
#include <deque>

using namespace std;


const int MAX_N = 500001;
const int MIN_VAL = -10000000;
int n, k;
int a[MAX_N];
char str[5000005];

ifstream f("secventa.in");
ofstream g("secventa.out");

void slidingWindowMinimum() {
    deque<int> q;
    for (int i = 1; i <= k; i++) {
        while (!q.empty() && a[q.back()] >= a[i]) {
            q.pop_back();
        }
        q.push_back(i);
    }
    int maxVal = MIN_VAL, leftIdx = 1;

    // minimum element in the window is the first in deque
    for (int i = k + 1; i <= n; ++i) {
        if (maxVal < a[q.front()]) {
            maxVal = a[q.front()];
            leftIdx = q.front();
        }

        while (!q.empty() && a[q.back()] >= a[i]) {
            // pop elements that can't be minimum in the
            // subsequent windows
            q.pop_back();
        }

        while (!q.empty() && q.front() <= i - k) {
            // pop elements that get out of the window
            q.pop_front();
        }

        q.push_back(i);
    }

    if (maxVal < a[q.front()]) {
        maxVal = a[q.front()];
        leftIdx = q.front();
    }

    g << leftIdx << leftIdx + k - 1 << maxVal;
}

int main(int argc, char** argv) {


    f >> n >> k;
    f.getline(str, 3);
    f.getline(str, 5000005);
    int ind = 0, i = 0, number = 0, sign = 1;
    while (str[ind] != '\n') {
        if (str[ind] == ' ') {
            a[++i] = number * sign;
            sign = 1;
            number = 0;
        } else if (str[ind] <= '9' && str[ind] >= '0') {
            number = (number * 10) + (int) (str[ind] - '0');
        } else if (str[ind] == '-') sign = -1;
        ind++;
    }


    int maxVal = -0x3f3f3f3f;
    int rightIdx = 0;
    deque<int> deq;
    for (int i = 1; i <= n; ++i) {
        while (deq.size() && deq.front() <= i - k)
            deq.pop_front();
        while (deq.size() && a[deq.back()] >= a[i])
            deq.pop_back();
        deq.push_back(i);
        int val = a[deq.front()];
        if (i >= k && maxVal < val) {
            rightIdx = i;
            maxVal = val;
        }
    }
    g << rightIdx - k + 1 << ' ' << rightIdx << ' ' << maxVal << '\n';

    return 0;
}

