#include <cstdio>
#include <vector>
#include <queue>
#define NMAX 50001

using namespace std;

vector<int> kahnTopologicalSort(vector<int> *graph, int *deg, int n){
    // empty list that will contain the sorted elements
    vector<int> sort;
    
    // construct a set of all nodes with no incoming edges
    queue<int> set;
    for(int i = 1; i <= n; ++i){
        if(deg[i] == 0){
            set.push(i);
        }
    }
    
    while(!set.empty()){
        int node = set.front();
        set.pop();
        sort.push_back(node);
        
        // for each edge n->m
        vector<int> neighbours = graph[node];
        for(vector<int>::iterator it = neighbours.begin(); it != neighbours.end(); ++it){
           int m = *it;           
           // remove edge from graph
           --deg[m];
           if(deg[m] == 0){
               // if no incoming edges, push it to the set
               set.push(m);
           }
           
        }
        neighbours.empty(); // remove edges from graph  
    }
    
    return sort;   
}

int main(int argc, char** argv) {
    freopen("sortaret.in", "r", stdin);
    freopen("sortaret.out", "w", stdout);
    
    // n nodes count, m edges count
    int n, m;
    scanf("%d %d", &n, &m);
    
    // read edges
    int i, x, y;
    
    // adjacengy list for graph
    vector<int> graph[NMAX];
    
    // inner degree of each node
    int deg[NMAX] = {0};
    
    for(int i = 0; i < m; ++i){
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        ++deg[y];        
    }
    
    vector<int> sort = kahnTopologicalSort(graph, deg, n);
    
    for(vector<int>::iterator it = sort.begin(); it != sort.end(); ++it){
        printf("%d ", *it);
    }
    return 0;    
}

