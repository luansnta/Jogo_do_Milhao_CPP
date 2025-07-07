#include <iostream>
#include <cmath>

using namespace std;

int soma(int a, int b){
    return a + b;
}

double area(double a){
    return pow(a,2);
}

double area(double a, double b){
    return a * b;
}

int main(){
    int x = 3, y = 2;

    cout << "Soma = " << soma(x,y) << endl;

    cout << "Area do quadrado = " << area(x) << endl;

    cout << "Area do retangulo = " << area(x,y) << endl;
    
    return 0;
}

