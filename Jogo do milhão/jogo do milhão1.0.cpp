#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype> //usar o topper
using namespace std;

struct Questao{
    string pergunta;
    vector<string> alternativas; 
    char respostacerta;
};

vector<Questao> carregarPerguntas(const string& arquivo){
    vector<Questao> bancodequestoes;
    ifstream leitor(arquivo);

    if(!leitor.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return {};
    }

    string linha;

    while(getline(leitor,linha)){
        stringstream ss(linha); 
        string pedaco_questao;
        Questao questao_temp;

        getline(ss,pedaco_questao,';');//Lê a pergunta
        questao_temp.pergunta = pedaco_questao;

        questao_temp.alternativas.clear();
        for(int i = 0; i < 4; i++){ //Lê as alternativas
            getline(ss,pedaco_questao,';');
            questao_temp.alternativas.push_back(pedaco_questao);
        }
        
        getline(ss, pedaco_questao, ';');//Lê as respostas
        questao_temp.respostacerta = pedaco_questao[0];

        bancodequestoes.push_back(questao_temp);
    }
    leitor.close(); 

    return bancodequestoes;
}

void mostrarPergunta(const Questao& q){
    cout << "Pergunta: \n" << q.pergunta << endl;
    cout << "Alternativas: \n" << endl;

    char letra = 'A';
    for(size_t i = 0; i < q.alternativas.size(); i++){
        cout << letra << ") " << q.alternativas[i] << endl;
        letra ++;
    }

    char respostaJogador;
    cout << "Qual a alternativa correta?: " << endl;
    cin >> respostaJogador;
    cout << "Voce respondeu: " << respostaJogador << endl;
    respostaJogador = toupper(respostaJogador);

    if(respostaJogador == q.respostacerta){
        cout << "Resposta Correta!" << endl;
    }else{
        cout << "Resposta errada!" << endl;
        cout << "Resposta correta: " << q.respostacerta << endl;
    }
}

int main(){

    vector<Questao> bancodequestoes = carregarPerguntas("Perguntas.txt");

    if(!bancodequestoes.empty()){
        mostrarPergunta(bancodequestoes[0]);
    }else{
        cout << "Nenhuma pergunta carregada no arquivo!" << endl;
    }
   
    return 0;
}