#include <iostream>

using namespace std;

int fatorial(int n){
    if(n <= 1) return 1;
    return n * fatorial(n-1);
}

int main(){
    int n = 5;
    
    cout << "Fatorial de " << n << " = " << fatorial(n); 

    return 0;
}
