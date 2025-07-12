#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype> //usar o topper
#include <windows.h> //Reconhcer caracteres especiais
using namespace std;

struct Questao{
    string pergunta;
    vector<string> alternativas; 
    char respostacerta;
};

enum eResultadodaRodada{
    ACERTO,
    ERRO,
    PULO
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

eResultadodaRodada JogarRodada(const Questao* q_ptr, int& pulosRestantes){
    //Exibir a pergunta
    cout << "PERGUNTA: \n" << q_ptr -> pergunta << endl;
    cout << "ALTERNATIVAS: \n" << endl;
    
    char letra = 'A';
    for(size_t i = 0; i < q_ptr -> alternativas.size(); i++){
        cout << letra << ") " << q_ptr -> alternativas[i] << endl;
        letra ++;
    }

    char respostaJogador;
    while(true){
    if(pulosRestantes > 0){
    cout << "QUAL A ALTERNATIVA CORRETA? (OU [P] PARA PULAR): " << endl;
    }else{
        cout << "QUAL A ALTERNATIVA CORRETA?: " << endl;
    }
    cin >> respostaJogador;
    cout << "Voce respondeu: " << respostaJogador << endl;
    respostaJogador = toupper(respostaJogador);

        if(respostaJogador == 'P'){
            if(pulosRestantes > 0){
                pulosRestantes --; //Diminui o valor original
                return PULO; //Pula a questão, sai da função e do loop
            }else{
                cout << "PULO ESGOTADO!!" << endl;
                //O loop continua até o jogador responder a questão
            }
        }else if(respostaJogador >= 'A' && respostaJogador <= 'D'){
            break; //Sai do loop se a resposta for válida
        }else{
            cout << "RESPOSTA INVÁLIDA, TENTE NOVAMENTE!!!" << endl;
        }
    }
    if(respostaJogador == q_ptr -> respostacerta){
         return ACERTO;
    }else{
         cout << "Resposta correta: " << q_ptr -> respostacerta << endl;
         return ERRO;
    }
    
}

void exibirMensagem(string mensagem){
    cout << "[MENSAGEM] " << mensagem << endl;
}

void exibirMensagem(bool acertou){
    if(acertou){
        cout << "\n[MENSAGEM] PARABÉNS!! VOCÊ PASSOU PARA A PRÓXIMA FASE!!" << endl;
    }else{
        cout << "\n[MENSAGEM] RESPOSTA ERRADA!! FIM DE JOGO!!" << endl;
    }
}

void jogar(const vector<Questao>& bancodequestoes, int indiceAtual, int& pontuacao, const int premio[], int& pulosRestantes){

    if(indiceAtual >= bancodequestoes.size()){
        cout << "VOCÊ VENCEU!!!" << endl;
        pontuacao = premio[bancodequestoes.size() - 1];
        return;
    }

        cout << "PERGUNTA: " <<  indiceAtual + 1 << "VALENDO R$ " << premio[indiceAtual] << endl;
        
        eResultadodaRodada resultado = JogarRodada(&bancodequestoes[indiceAtual], pulosRestantes);

        switch(resultado)
        {
            case ACERTO:
                //Atualiza a pontuação com o prêmio da rodada
                pontuacao = premio[indiceAtual];
                //Mensagem de acerto
                exibirMensagem(true);
                //Exibe a pontuação garantida
                cout << "VOCE GARANTIU: R$ " << pontuacao << endl;

                char opcao;
                //Lógica de para ou continuar
                cout << "VOCÊ QUER PARAR[P] OU CONTINUAR[C]?: " << endl;
                cin >> opcao;
                opcao = toupper(opcao);
                if(opcao == 'P'){
                    return;
                }else{
                    jogar(bancodequestoes, indiceAtual + 1, pontuacao, premio, pulosRestantes);
                }
            break;
        
            case ERRO:
                exibirMensagem(false);
                pontuacao = 0;
            break;// O jogo acaba

            case PULO:
                cout << "[AJUDA] VOCÊ PULOU A PERGUNTA!!!" << endl;
                //Pula a pergunta sem alterar a pontuação e vai para a próxima (ou finaliza o jogo)
                jogar(bancodequestoes, indiceAtual + 1, pontuacao, premio, pulosRestantes);
        }  
}


int main(){
    //permite que o console exiba corretamente os caracteres especiais
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    const int premio[] = {1000, 5000, 20000, 100000, 1000000};
    int pontuacaoFinal = 0; //Variável para gerenicar os pontos
    int pulosRestantes = 1; //Variável para gerenciar os pulos

    exibirMensagem("O JOGO DO MILHÃO COMEÇOU!!!");

    vector<Questao> bancodequestoes = carregarPerguntas("Perguntas.txt");

    if(!bancodequestoes.empty()){

        exibirMensagem("PERGUNTAS CARREGADAS...");
        
        jogar(bancodequestoes, 0, pontuacaoFinal, premio, pulosRestantes);//CHAMADA QUE INICIA O JOGO DO INDICE 0
        
    }else{
         exibirMensagem("\nNENHUMA PERGUNTA CARREGADA!!!");
        }
    exibirMensagem("SUA PONTUAÇÃO FINAL FOI: R$ " + to_string(pontuacaoFinal));
    exibirMensagem("OBRIGADO POR JOGAR!!!");
    return 0;
}