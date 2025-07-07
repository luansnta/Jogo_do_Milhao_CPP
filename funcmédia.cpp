#include <iostream>

using namespace std;

double media(int vet[], int tamanho){
    double soma;
    for(int i = 0; i < tamanho; i++){
        soma += vet[i];
    }
    return soma / static_cast<double>(tamanho);
}

int main(){
    int vet[3] = {2,4,6};
    cout << media(vet, 3) << endl;

    return 0;
}