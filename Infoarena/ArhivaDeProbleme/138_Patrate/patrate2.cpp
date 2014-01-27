#include <fstream>
 
using namespace std;
 
const int BASE=1000000;
 
ifstream fin("patrate2.in");
 
void mul(int A[], int B)
{
      int i, t = 0;
      for (i = 1; i <= A[0] || t; i++, t /= BASE)
              A[i] = (t += A[i] * B) % BASE;
      A[0] = i - 1;
}
 
int sol[15000];
 
int main()
{
    freopen("patrate2.out", "w", stdout);
    int n, i, j;
    sol[0]=sol[1]=1;
 
    fin>>n;
    for(i=1;i<=n;i++)
    {
        mul(sol, i);
        for(j=1;j<=n;j++)
        {
            mul(sol, 2);
        }
    }

    printf("%d", sol[sol[0]]);
    for(i=sol[0]-1;i;i--) printf("%06d", sol[i]);
    fin.close();
}