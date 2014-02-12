// Nathan Wildenberg

#include<stdio.h>
#include<string.h>
 
#define NMAX 22
#define LMAX 1000
#define BAZA 10
 
int d[NMAX][NMAX][LMAX];
int aux[LMAX],aux2[LMAX],s[LMAX],sol[LMAX],nr[LMAX];
int b,l,p,q;
 
 
 
 
 
void citeste(int a[])
{
    int i;
    char c;
 
    aux[0]=0;
 
    scanf("%c",&c);
    while(c<'0'||c>'9')
        scanf("%c",&c);
    while(c>='0'&&c<='9')
    {
        aux[++aux[0]]=c-'0';
        scanf("%c",&c);
    }
 
    a[0]=aux[0];
    for(i=1;i<=aux[0];++i)
        a[aux[0]-i+1]=aux[i];
}
 
void afisare(int a[])
{
    int i;
    for(i=a[0];i>=1;--i)
        printf("%d",a[i]);
    printf("\n");
}
 
 
 
void egal(int a[],int x)
{
    if(x==0)
        a[0]=1;
    while(x)
    {
        a[++a[0]]=x%10;
        x/=10;
    }
}
 
void inm(int a[],int x[])
{
    memset(aux,0,sizeof(aux));
    aux[0]=a[0]+x[0]-1;
 
    int i,j,r=0;
 
    for(i=1;i<=a[0];++i)
        for(j=1;j<=x[0];++j)
            aux[i+j-1]+=a[i]*x[j];
    for(i=1;i<=aux[0];++i)
    {
        aux[i]+=r;
        r=aux[i]/10;
        aux[i]=aux[i]%10;
    }
    if(r)
        aux[++aux[0]]=r;
 
    memcpy(a,aux,sizeof(aux));
}
 
void adun(int d[],int x[])
{
    int i,maxi,r=0;
    if(d[0]>x[0])maxi=d[0];
    else maxi=x[0];
 
    for(i=1;i<=maxi || r;++i)
    {
        d[i]=d[i]+x[i]+r;
        r=d[i]/BAZA;
        d[i]=d[i]%BAZA;
    }
    d[0]=i-1;
}
 
void scad(int d[],int x[])
{
    int i,r=0;
    for(i=x[0]+1;i<=d[0];++i)
        x[i]=0;
    for(i=1;i<=d[0];++i)
    {
        d[i]=d[i]-(x[i]+r);
        if(d[i]<0)
            r=1;
        else
            r=0;
        if(r)
            d[i]+=10;
    }
    while(!d[d[0]]&&d[0])
        --d[0];
}
 
void dinamica(int maxi)
{
    int i,j;
 
    memset(s,0,sizeof(s));
    memset(d[1][0],0,sizeof(d[1][0]));
    egal(s,b-1);
    egal(d[1][0],b-1);
 
    for(i=2;i<=l;++i)
    {
        memset(d[i][0],0,sizeof(d[i][0]));
        egal(d[i][0],b-1);
        inm(d[i][0],s);
 
        memcpy(s,d[i][0],sizeof(d[i][0]));
        for(j=1;j<=maxi&&j<i;++j)
        {
            memcpy(d[i][j],d[i-1][j-1],sizeof(d[i-1][j-1]));
            adun(s,d[i][j]);
        }
    }
}
 
 
int main()
{
    freopen("zero.in","r",stdin);
    freopen("zero.out","w",stdout);
    int i;
    scanf("%d%d%d%d",&l,&b,&p,&q);
 
    dinamica(p);
 
    egal(sol,0);
    for(i=0;i<=p;++i)
        adun(sol,d[l][i]);
    afisare(sol);
 
 
    dinamica(q-1);
 
    memset(sol,0,sizeof(sol));
    egal(sol,0);
    for(i=0;i<q;++i)
        adun(sol,d[l][i]);
 
    memset(nr,0,sizeof(nr));
    memset(aux2,0,sizeof(aux2));
    egal(nr,b-1);
    egal(aux2,b);
    for(i=1;i<l;++i)
        inm(nr,aux2);
 
    scad(nr,sol);
 
    afisare(nr);
 
    return 0;
}