#include <iostream>

using namespace std;

int soma(int n){
    if(n == 1) return 1;
    return n + soma(n - 1);
}

int main(){
    int n = 5;

    cout << "Resultado " << soma(n) << endl;
}