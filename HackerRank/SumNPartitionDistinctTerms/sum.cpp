#include <stdio.h>
#include <cmath>

int table[150][150];
int dTable[150][150];


/* partition with terms repeating i.e.
 * 
 * The seven partitions of 5 are:
 *       5
 *       4 + 1
 *       3 + 2
 *       3 + 1 + 1
 *       2 + 2 + 1
 *       2 + 1 + 1 + 1
 *       1 + 1 + 1 + 1 + 1
 *
 */
int partition(int sum, int largestNumber) {
    int i, j;

    for (i = 1; i <= sum; i++) {
        for (j = 1; j <= largestNumber; j++) {
            if (i - j < 0) {
                table[i][j] = table[i][j - 1];
                continue;
            }
            table[i][j] = table[i][j - 1] + table[i - j][j];
        }
    }

    return table[sum][largestNumber];
}

/* partition with distinct terms i.e.
 * If we count the partitions of 8 with distinct parts, we also obtain 6:
 * 
 * 8
 * 7 + 1
 * 6 + 2
 * 5 + 3
 * 5 + 2 + 1
 * 4 + 3 + 1
 */
int distinctPartition(int sum, int largestNumber) {
    int i, j;

    for (i = 1; i <= sum; i++) {
        for (j = 1; j <= largestNumber; j++) {
            if (i - j < 0) {
                dTable[i][j] = dTable[i][j - 1];
                continue;
            }
            dTable[i][j] = dTable[i][j - 1] + dTable[i - j][j-1];
        }
    }   
   
    return dTable[sum][largestNumber];
}

int getLargestPower(int low, int high, int n, int p){
    int m = (low + high)/2;
    int result = (int) pow(m, p);
    int nextResult = (int) pow(m + 1, p);
    if (result > n){
        return getLargestPower(low, m - 1, n, p);
    } if (result < n && nextResult > n){
        return m;
    }
    return getLargestPower(m+1,  high, n, p);
}

int main() {
    int sum = 5;
    int largestNumber = 5;
    int i;

    /*initialize table with base cases*/
    for (i = 0; i <= sum; i++)
        table[i][0] = 0;
    for (i = 0; i <= largestNumber; i++)
        table[0][i] = 1;
    
    printf("%d\n", partition(sum, largestNumber));
    
    sum = 6;
    largestNumber = 6;

    /*initialize table with base cases*/
    for (i = 0; i <= sum; i++)
        dTable[i][0] = 0;
    for (i = 0; i <= largestNumber; i++)
        dTable[0][i] = 1;
    
    printf("%d\n", distinctPartition(sum, largestNumber));
    
    printf("%d\n", getLargestPower(0,10,10,2));

    return 0;
}