/* 
 * File:   main.cpp
 * Author: Vlad
 *
 * Created on January 23, 2014, 11:13 PM
 */

#include <fstream>
#include <vector>
#include <queue>

#define GUARD 0
#define WALL -2
#define MAX_INT  9999999

using namespace std;

ifstream fin("muzeu.in");
ofstream fout("muzeu.out");

typedef struct _Point {
    _Point(int ll, int cc) : l(ll), c(cc) {   }
    int l, c;
} Point;

int n;
int map[300][300];
vector<Point> guards;
queue<Point> points;

int dl[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void read() {
    fin >> n;
    char c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            map[i][j] = MAX_INT;
            fin >> c;           
            if (c == '#'){
                map[i][j] = WALL;
            }
            else if (c == 'P') {
                guards.push_back(Point(i, j));
                points.push(Point(i, j));
                map[i][j] = 0;
            }
            
        }
    }
}

void solve() {
    while(!points.empty()){
        Point p = points.front();
        points.pop();
        int dist = map[p.l][p.c];
        for(int i = 0; i < 4; i++){
            Point next = Point(p.l + dl[i], p.c + dc[i]);
            if(p.l >= 1 && p.l <= n && p.c >= 1 && p.c <=n){
                int nextDist  = map[next.l][next.c];
                if (nextDist != WALL)
                    if (nextDist > dist + 1){
                        nextDist = dist + 1;
                        map[next.l][next.c] = dist + 1;
                        points.push(next);
                    }
            }
        }
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(map[i][j] == MAX_INT){
                map[i][j] = -1; // not accessible
            }
        }
    }
}

int main(int argc, char** argv) {
    read();
    solve();
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
           fout<<map[i][j] << ' ';
        }
        fout << endl;
    }
    
    fout.close();
    fin.close();

    return 0;
}

