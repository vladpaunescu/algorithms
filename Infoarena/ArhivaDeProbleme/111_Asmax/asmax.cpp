/* 
 * File:   main.cpp
 * Author: Vlad
 *
 * Created on January 22, 2014, 11:13 PM
 */

#include <fstream>
#include <vector>
#include <iosfwd>

#define NMAX 16001
#define INF 0x3f3f3f3f

using namespace std;

ifstream fin("asmax.in");
ofstream fout("asmax.out");

int n, values[NMAX], sum[NMAX], smax = -INF;
vector<int> arb[NMAX];
bool visited[NMAX];

void read(){
    fin>>n;
    for(int i = 1; i <= n; i++){
        fin>>values[i];
    }
    for(int i = 1, a, b; i <=n; ++i){
        fin >> a >> b;
        arb[a].push_back(b);
        arb[b].push_back(a);
    }
}

void dfs(int node){
    visited[node] = true;
    sum[node] = values[node];
    for(int neighbour : arb[node]){
        if(!visited[neighbour]){
            dfs(neighbour);
            if(sum[neighbour] > 0){
                sum[node] += sum[neighbour];
            }
        }
    }
    if (sum[node] > smax){
        smax = sum[node];
    }
}

int main(int argc, char** argv) {
    read();
    dfs(1);
    fout<<smax<<endl;
    fout.close();
    fin.close();
    
    return 0;
}

