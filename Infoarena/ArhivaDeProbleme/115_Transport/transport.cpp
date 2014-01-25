#include <fstream>
#include <climits>


using namespace std;

ifstream fin("transport.in");
ofstream fout("transport.out");

int N, K, vol[16001], sumVol, salteaMax;

// greedy function to return number of trips vor cargo volume vol
int getNoTrips(int cargoVol){
    if (cargoVol < salteaMax){
        return INT_MAX;
    }
    int tripsCount = 1;
    int currentVol = 0;
    for(int i = 1; i <=N; i++){
        if (currentVol + vol[i] > cargoVol){
            tripsCount++;
            currentVol = 0;            
        }
        currentVol += vol[i];
    }
    return tripsCount;
}

int binarySearchVol(int minVol, int maxVol){
    while(minVol <= maxVol){
        int volumeMed = minVol + (maxVol - minVol) / 2;
        int nrDrumuri = getNoTrips(volumeMed);
        if (nrDrumuri <= K && getNoTrips(volumeMed - 1) > K){
            return volumeMed;
        }
        if (nrDrumuri <= K){
            maxVol = volumeMed - 1;
        } else {
            minVol = volumeMed + 1;
        }
    }
    return salteaMax;
}

void solve(){
    salteaMax = vol[1];
    for(int i = 2; i <= N; ++i){
        if(vol[i] > salteaMax){
            salteaMax = vol[i];
        }
    }
    int cargoVol = binarySearchVol(salteaMax, sumVol * 2);
    fout << cargoVol;
    
}

int main(int argc, char** argv) {
    fin >> N >> K;
    for(int i = 1; i <= N; ++i){
        fin>>vol[i];
        sumVol += vol[i];
    }
    
    solve();
    fout.close();
    fin.close();

    return 0;
}

