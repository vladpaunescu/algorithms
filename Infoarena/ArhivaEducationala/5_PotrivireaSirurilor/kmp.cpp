#include <cstdio>
#include <cstring>

# define NMAX 2000003
# define MIN(a,b)  ((a) < (b) ? (a) : (b))

void computePrefixFunction(char *a, int  *pi, int m){
    pi[1] = 0;
    int k  = 0;

    for(int q = 2; q <= m; ++q){
        while (k > 0 && a[k + 1] != a[q]){
            k = pi[k];
        }
        if (a[k + 1] == a[q]){
            ++k;
        }
        pi[q] = k;
    }
}

int pi[NMAX];
int matches[1024];
char a[NMAX], b[NMAX];

int main(){
    freopen("strmatch.in", "r", stdin);
    freopen("strmatch.out", "w", stdout);
   
    int m, n;
    

    fgets(a + 1, NMAX, stdin);
    fgets(b + 1, NMAX, stdin);
    
    a[0] = ' ';
    b[0] = ' ';
    
    // search a substring into b

    m = strlen(a) - 2; // get rid of newline
    n = strlen(b) - 2; // get rid of \n  
    
        int i;
    for(i = 1; i <= m; ++i){
        if(!((a[i] >='a' && a[i] <= 'z') ||
                (a[i] >= 'A' && a[i] <= 'Z') ||
                (a[i] >= '0' && a[i] <= '9')))
                break;
    }
    m = i - 1;
    a[i] = 0;
    
    for(i = 1; i <= n; ++i){
        if(!((b[i] >='a' && b[i] <= 'z') ||
                (b[i] >= 'A' && b[i] <= 'Z') ||
                (b[i] >= '0' && b[i] <= '9')))
                break;
    }
    n = i - 1;
    b[i] = 0;
           
    computePrefixFunction(a, pi, m);

    // kmp
    int matchCount = 0;
    int q = 0; // number of characters matched
    for(int i = 1; i <= n; i++){
        while ( q > 0 && a[q + 1] != b[i]){
            // next character does not match
            q =  pi[q];
        }
        if (a[q + 1] == b[i])
            ++q;
        if (q == m){
            q = pi[q]; // look for next match
            matchCount++;
            if(matchCount <= 1000)
                matches[matchCount] = i - m;            
        }
    }

    // print matches
    printf("%d\n", matchCount);
   
    for(int i = 1; i <= MIN(matchCount, 1000); ++i){
        printf("%d ", matches[i]);
    }
    putchar('\n');

    return 0;
}

