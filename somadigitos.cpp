#include <iostream>
#include <cstring>

using namespace std;

void separardigitos(int n, char *digitos){
    sprintf(digitos,"%d",n);
}

int soma(int n){
    if(n == 0) return 0;
    return (n % 10) + soma(n/10);
}
int main (){
    int n = 13;
    char digitos[20];


    separardigitos(n, digitos);

    for(int i = 0; digitos[i]; i++){
        cout << "Digito["<< i <<"] = " << digitos[i] << endl;
    }   
    cout << "Resultado = " << soma(n) << endl;

    return 0;
}