#include <iostream>

using namespace std;

int retornaomaior(int a, int b){
    if(a == b){
        cout << "Sao iguais" << endl;
        return 0;
    }else if(a > b){
        cout << "Maior = " << a << endl;    
        return a;
    }else{
        cout << "Maior = " << b << endl;
        return b;
    }
}

int main(){
    int a = 2, b = 3;
    retornaomaior(a,b);
    return 0;
}