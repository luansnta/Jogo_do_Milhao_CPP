#include <iostream>

using namespace std;

int fibonacci(int n){
    if(n <= 1) return 0;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int n = 4;

    cout << fibonacci(n) << endl;

    return 0;
}