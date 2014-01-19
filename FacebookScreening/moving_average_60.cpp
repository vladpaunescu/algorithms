//The function ma60(int x) is defined in following way:
//
//the first time ma60(x) is called, it returns x;
//the Nth time ma60(a(N)) is called (N <= 60), it returns (a(1)+a(2)+...+a(N))/N
//for any N > 60 ma(a(N)) returns (a(N-59)+a(N-58)+...+a(N))/60
//
//Please note that a(N) is NOT an array, it denotes the sequence of incoming
//parameters you give ma60().

// moving average of window 60

#include <iostream>
#include <queue>

#define WINDOW_SIZE 60

using namespace std;

double ma60_queue(int x){
    static queue<int> q;
    // number of previous calls to function
    static int count = 0;
    
    static int sum = 0;

    // for first time
    if (count == 0) {
        count++; // increase calls
        sum += x; // take into account first el
        q.push(x);
        return (double) x;
    }

    // if nr of previous calls < 60
    if (count < 60) {
        // assign current param
        q.push(x);
        sum += x;
        count++;
        return (double) sum / count;

    }

    // if nr of previus calls >= 60
    if (count >= 60) {
        sum -= q.front();
    //    cout<<"q front "<< q.front()<<endl;
        q.pop();
        q.push(x);
        sum+=x;        
     
       // take into account current call
       return (double) sum / WINDOW_SIZE;

    }
}

double ma60(int x) {
    // number of previous calls to function
    static int count = 0;

    static int params[WINDOW_SIZE];
    static int sum = 0;

    // for first time
    if (count == 0) {       
        sum += x; // take into account first el 
        params[count] = x;      
        count++; // increase calls
        return (double) x;
    }

    // if nr of previous calls < 60
    if (count < 60) {
        // count is nr of previous calls
        // assign current param
        params[count] = x;
        count++;
        sum += x;
                
        return (double) sum / count;

    }

    // if nr of previous calls >= 60
    if (count >= 60) {      
       // sliding window   
       
       // remove from sliding window
       int index = count % WINDOW_SIZE;  
       sum -= params[index];
       
       // increase calls
       count++;       
     
       // add to sliding window
       sum += x;
       params[index] = x;
       
       return (double) sum / WINDOW_SIZE;

    }
}

int main() {

    for (int i = 1; i <= 180 ; i++) {
        double r1 = ma60(i);
        double r2 = ma60_queue(i);
        cout<<r1<<" "<<r2<<endl;
        if(r1 != r2){
            cout<<i<<" different "<<r1<<" "<<r2<<endl;
            break;
        }
    } 
        
    cout<<endl;
    
    return 0;
}



