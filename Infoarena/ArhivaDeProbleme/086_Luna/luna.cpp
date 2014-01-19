/* 
 * File:   luna.cpp
 * Author: Vlad
 *
 * Created on January 17, 2014, 11:54 PM
 */

#include <cstdio>
#include <wchar.h>


using namespace std;
int M, N, K, countryCount;
int a[100][100], d[5001][51], h[5001][51];
bool countryFound[5001] = {false};

// d [ i ][ j ] = inaltimea maxima ce o poate avea o tara de tipul i
// daca are lungimea j;
// h[ i ][ j ] = cat de mult ma pot duce in sus pe coloana j; 
// acum tu te afli la pozitia i,j; 
// ii afli tara si acum presupui cu coltul dreapta jos a dreptunghiului se afla
// in (i,j); acum fixezi lungimea dreptunghiului; pentru fiecare lungime fixata
// raspunsul va fi minimul( h[ i ][ k(indicele lungimii) .. j]);
// si acest minim il actualizezi la fiecare noua lungime.

void compute() {

    // build h
    for (int j = 1; j <= N; ++j) {
        int currentFirm, sequenceLength = 1;
        currentFirm = a[1][j];
        for (int i = 2; i <= M; i++) {
            if (a[i][j] == currentFirm) {
                sequenceLength++;
            } else {
                if (sequenceLength > h[currentFirm][j]) {
                    h[currentFirm][j] = sequenceLength;
                }
                sequenceLength = 1;
                currentFirm = a[i][j];     
            }
        }
        if (sequenceLength > h[currentFirm][j]) {
            h[currentFirm][j] = sequenceLength;
        }
    } 
    // build d
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            int country = a[i][j];
            for(int len = 1; len <= j; len++){
                int minH = M;
                for(int k = j - len + 1; k <= j; k++){
                    if(minH > h[country][k]){
                        minH = h[country][k];
                    }
                }
                if(minH > d[country][len]){
                    d[country][len] = minH;
                }
            }
        }
    }

    
//    for(int i = 1; i <= countryCount; i++){
//        for(int j = 1; j <= N; j++){
//            printf("%d ", d[i][j]);
//        }
//        putchar('\n');
//    }
    
}

int main(int argc, char** argv) {
    freopen("luna.in", "r", stdin);
    freopen("luna.out", "w", stdout);
    scanf("%d %d", &M, &N);
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            scanf("%d", &a[i][j]);
            if (countryCount < a[i][j]) {
                countryCount = a[i][j];
            }
            countryFound[a[i][j]] = true;
        }
    }
    compute();
    
    scanf("%d", &K);
    int countryId, height, width;
    for(int query = 1; query <= K; query++){
        scanf("%d %d %d", &countryId, &height, &width);
        if(countryFound[countryId] == true){
            if(width > N || height > M ){
                if(height > N || width > M){
                     printf("Cererea nu poate fi satisfacuta!\n");
                     continue;
                }
            }
            if(d[countryId][width] >= height){
                printf("Cererea poate fi satisfacuta!\n");
            } else if(d[countryId][height] >= width){
                printf("Cererea poate fi satisfacuta!\n");
            } else {
                printf("Cererea nu poate fi satisfacuta!\n");
            }             
            
        } else{
            printf("Tara de provenienta nu are parcele pe Luna!\n");
        }
    }
    
    return 0;
}

