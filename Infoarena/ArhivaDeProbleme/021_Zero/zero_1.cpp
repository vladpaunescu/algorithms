// Alex Velea

#include <iostream>
#include <fstream>
using namespace std;
 
ifstream in("zero.in");
ofstream out("zero.out");
 
struct BigNumber {
    short cif[30], nr_cif;
    BigNumber() {
        nr_cif = 1;
        for (int i = 0; i < 30; ++i)
            cif[i] = 0;
    }
    BigNumber(int x) {
        for (int i = 0; i < 30; ++i)
            cif[i] = 0;
        if (x < 10) {
            nr_cif = 1;
            cif[0] = x;
        } else {
            nr_cif = 2;
            cif[0] = x % 10;
            cif[1] = x / 10;
        }
    }
    BigNumber operator * (const int &rth) const {
        BigNumber rez;
        rez.nr_cif = nr_cif;
        int i = 0;
        for (; i < nr_cif or rez.cif[i]; ++i) {
            rez.cif[i] += cif[i] * rth;
            if (rez.cif[i] > 9) {
                rez.cif[i + 1] += rez.cif[i] / 10;
                rez.cif[i] %= 10;
            }
        }
        rez.nr_cif = i;
        return rez;
    }
    BigNumber operator - (const BigNumber &rth) const {
        BigNumber rez;
        for (int i = 0; i < 30; ++i)
            rez.cif[i] = cif[i] - rth.cif[i];
        for (int i = 0; i < 30; ++i)
            if (rez.cif[i] < 0) {
                rez.cif[i] += 10;
                rez.cif[i + 1]--;
            }
        rez.nr_cif = 1;
        for (int i = 29; i >= 0; --i)
            if (rez.cif[i] != 0) {
                rez.nr_cif = i + 1;
                break;
            }
        return rez;
    }
    void add(const BigNumber &rth) {
        int i = 0;
        nr_cif = max(nr_cif, rth.nr_cif);
        for (; i < nr_cif or cif[i] != 0; ++i) {
            cif[i] += rth.cif[i];
            if (cif[i] > 9) {
                cif[i + 1] += cif[i] / 10;
                cif[i] %= 10;
            }
        }
        nr_cif = i;
    }
    void show() {
        short zero = 0;
        for (int i = 29; i >= 0; --i) {
            if (cif[i] != 0) {
                zero = true;
                out << int(cif[i]);
            } else if (i == 0 or (cif[i] == 0 and zero)) {
                out << 0;
            }
        }
        out << '\n';
        return ;
    }
} dp[21][21], BigNumberZ;
 
int l, b, p, q;
 
BigNumber solve(int l, int b, int p) {
    for (int i = 0; i <= l; ++i)
        for (int j = 0; j <= p; ++j)
            dp[i][j] = BigNumberZ;
 
    dp[1][0] = BigNumber(b);
    for (int i = 2; i <= l; ++i) {
        for (int k = 0; k <= p; ++k) {
            dp[i][0].add(dp[i - 1][k] * b);
            if (k != 0)
                dp[i][k] = dp[i - 1][k - 1];
        }
    }
    BigNumber rez;
        for (int k = 0; k <= p; ++k)
            rez.add(dp[l][k]);   
    return rez;
}
 
int main() {
    int l, b, p, q;
    in >> l >> b >> p >> q;
    b--;
 
    BigNumber rez = solve(l, b, p);
    rez.show();
 
    rez = BigNumber(b);
    for (int i = 2; i <= l; ++i)
        rez = rez * (b + 1);
    rez = rez - solve(l, b, q - 1);
    rez.show();
    return 0;
}