#include <iostream>

using namespace std;

void hanoi(int n, char origem, char auxiliar, char destino){
    if(n == 1){
        cout <<"Mover disco 1 de " << origem << " para " << destino << endl;
    
        return;
    }

    hanoi(n-1, origem, destino, auxiliar);
    cout <<"Mover disco  " << n << " de " << origem << " para " << destino << endl; 
    hanoi(n-1, auxiliar, origem, destino);
}

int main(){
    int n = 3;
    char origem = 'A';
    char auxiliar = 'B';
    char destino = 'C';
    hanoi(n ,origem, auxiliar, destino);


    return 0;
}
