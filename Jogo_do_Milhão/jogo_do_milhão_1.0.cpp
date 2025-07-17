#include <iostream>
#include <string>//Permite manipular strings
#include <vector>//Permite usar um array de tamanho dinâmico
#include <fstream>//Manipular arquivos
#include <sstream>//Permite manipular a função getline separando as linhas através do ";"
#include <cctype> //usar o topper
#include <windows.h> //Reconhcer caracteres especiais
#include <random> //Usada pra gerar números aleatórios
#include <cstdlib>//Usar a função system()
#include <limits>// Usar a função cin.ignore()


using namespace std;

struct Questao{
    string pergunta;
    vector<string> alternativas;
    char respostacerta;
};

enum eResultadodaRodada{
    ACERTO, ERRO, PULO

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

eResultadodaRodada JogarRodada(const Questao* q_ptr, int& pulosRestantes, int& metadeRestantes){
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
        cout << "QUAL A SUA ESCOLHA?";
        if(pulosRestantes > 0) cout << "[P] PULAR";
        if(metadeRestantes > 0) cout << "[M] ELIMINAR DUAS ALTERNATIVAS 50/50";
        cout << ":";
        cin >> respostaJogador;
        cout << "Voce respondeu: " << respostaJogador << endl;
        respostaJogador = toupper(respostaJogador);

        if(respostaJogador == 'M'){
            if(metadeRestantes > 0){
                metadeRestantes --;//Diminui o valor original

                int idc_correto = q_ptr -> respostacerta - 'A';
                //Vetor para guardar os índices incorretos
                vector<int> idc_incorreto;
                for(int i = 0; i < 4; ++i){
                    if(i != idc_correto){
                        idc_incorreto.push_back(i);
                    }
                }
                //Gerador de números aleatórios
                random_device rd;
                mt19937 gen(rd());
                //Cria uma distribuição para gerar um número entre 0 e o tamanho do vetor - 1
                uniform_int_distribution<> distribuicao(0, idc_incorreto.size() - 1);
                //Sorteia uma posição dentro do vetor de incorreto
                int idc_incorreto_a_manter = idc_incorreto[distribuicao(gen)];
                //Mostra o resultado do 50/50
                for(int i = 0; i < 4; ++i){
                    if(i == idc_correto || i == idc_incorreto_a_manter){
                        char letra = 'A' + i;
                        cout << letra << ")" << q_ptr->alternativas[i] << endl;
                    }
                }

                continue; //Volta ao início do loop para pedir uma nova resposta do jogador

            }else{
                cout << "AJUDA ESGOSTADA!!!" << endl;
            }

        }else if(respostaJogador == 'P'){
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
    //Verificação de acerto/acerto fora do loop
    if(respostaJogador == q_ptr -> respostacerta){
         return ACERTO;
    }else{
         cout << "RESPOSTA CORRETA: " << q_ptr -> respostacerta << endl;
         return ERRO;
    }

}

void exibirMensagem(string mensagem){
    cout << "[MENSAGEM] " << mensagem << endl;
}

void exibirMensagem(bool acertou){
    if(acertou){
        cout << "\n[MENSAGEM] PARABÉNS!! VOCÊ PASSOU PARA A PRÓXIMA FASE!!\n" << endl;
    }else{
        cout << "\n[MENSAGEM] RESPOSTA ERRADA!! FIM DE JOGO!!\n" << endl;
    }
}

void jogar(const vector<Questao>& bancodequestoes, int indiceAtual, int& pontuacao, const int premio[], int& pulosRestantes,int& metadeRestantes){

    //Função para a limpar a tela
    system("cls");

    if(indiceAtual >= bancodequestoes.size()){
        cout << "[MENSAGEM] PARABÉNS VOCÊ VENCEU!!!\n" << endl;
        pontuacao = premio[bancodequestoes.size() - 1];
        return;
    }

        cout << "PERGUNTA " <<  indiceAtual + 1 << " VALENDO R$ " << premio[indiceAtual] << endl;

        eResultadodaRodada resultado = JogarRodada(&bancodequestoes[indiceAtual], pulosRestantes,metadeRestantes);

        switch(resultado)
        {
            case ACERTO:
                //Atualiza a pontuação com o prêmio da rodada
                pontuacao = premio[indiceAtual];

                //Exibe a pontuação garantida
                cout << "\nVOCE GARANTIU: R$ " << pontuacao << endl;

                //Verifica se era a última pergunta da lista
                if(indiceAtual == bancodequestoes.size() - 1){
                    /*Se era a última pergunta, chama a recursão mais um vez para que entre na condição de vitória
                    (indiceAtual >= bancodequestoes.size())*/
                    jogar(bancodequestoes, indiceAtual + 1, pontuacao, premio, pulosRestantes, metadeRestantes);

                }else{
                    //E não for a última pergunta, mostra a mensagem de próxima fase
                    exibirMensagem(true);

                    //Se não era a última pergunta, aparece a opção de parar ou continuar
                    char opcao;
                    //Lógica de parar ou continuar
                    cout << "VOCÊ QUER PARAR[P] OU CONTINUAR[C]?: " << endl;
                    cin >> opcao;
                    opcao = toupper(opcao);
                    if(opcao == 'P'){
                        return;
                    }else{
                        jogar(bancodequestoes, indiceAtual + 1, pontuacao, premio, pulosRestantes, metadeRestantes);
                    }
                }
            break;

            case ERRO:
                exibirMensagem(false);
                //verifica em qual etapa o jogador errou
                if(indiceAtual >= 4){//Se o jogador errou na pergunta do milhão (indice 4)
                    pontuacao = premio[3];//O jogador ganha o prêmio anterior (porto seguro)
                }else{
                    pontuacao = 0; //Se errou antes do porto seguro, o jogador perde tudo
                }

            break;// O jogo acaba

            case PULO:
                cout << "\n[AJUDA] VOCÊ PULOU A PERGUNTA!!!" << endl;
                //Pula a pergunta sem alterar a pontuação e vai para a próxima (ou finaliza o jogo)
                jogar(bancodequestoes, indiceAtual + 1, pontuacao, premio, pulosRestantes,metadeRestantes);

        }
}

void salvarPontuacao(const string& nomeJogador,int pontuacao){

    ofstream arquivo_pontuacao("Historico_de_Pontuacao.txt", ios::app);

    if(!arquivo_pontuacao.is_open()){
        cout << "[ERRO] NÃO FOI POSSÍVEL ABRIR O ARQUIVO!!!" << endl;
    }else{
        arquivo_pontuacao << nomeJogador << ";" << pontuacao << endl;
        arquivo_pontuacao.close();

        cout << "\n[MENSAGEM] PONTUAÇÃO SALVA COM SUCESSO!!!" << endl;
    }
}

void exibirPontuacao(){

    system("cls");

    //Exibe a tabela de pontos
        cout << "========================================" << endl;
        cout << "           HISTÓRICO DE PONTOS" << endl;
        cout << "========================================" << endl;

    ifstream arquivo_pontos("Historico_de_Pontuacao.txt");

    if(!arquivo_pontos.is_open()){

        cout << "[ERRO] NÃO FOI POSSÍVEL ABRIR O ARQUIVO!!!" << endl;

        system("pause");
        return;
    }else{

        string linha;
        bool verificarLinhas;

        //Loop para ler o arquivo linha por linha
        while(getline(arquivo_pontos, linha)){
            verificarLinhas = true; //Afirma que encontrou pelo menos uma linha
            stringstream ss(linha);
            string nome, pontos;

            //A linha é fatiada usando o ; como delimitador
            if(getline(ss, nome, ';') && getline(ss, pontos)){
            //Acessa o array usando ponteiros
            cout <<"\nJOGADOR(A): " << nome << " - PRÊMIO: R$ " << pontos << endl;
            }
        }

        arquivo_pontos.close();

        if(!verificarLinhas){
            cout << "\nNÃO HÁ PONTOS REGISTRADOS!!!" << endl;
        }
    }
    system("pause");
}

void exibirRegras(){

    system("cls");
    //Cria uma leitor para o arquivo "Regras.txt"
    ifstream arquivo_regras("Regras.txt");
    //Verificar se o arquivo abriu
    if(!arquivo_regras.is_open()){
        cout << "[ERRO] NÃO FOI POSSÍVEL ABRIR O ARQUIVO!!!" << endl;
    }else{
        string linha;
        //Loop para ler todas as linhas do arquivo
        while(getline(arquivo_regras, linha)){
            //Exibe cada linha na tela
            cout << linha << endl;
        }
        //Fecha o arquivo
        arquivo_regras.close();
    }

    system("pause");

}

void menuPrincipal(){

    system("cls");
    cout << "========================================" << endl;
    cout << "         JOGO DO MILHAO" << endl;
    cout << "========================================" << endl;
    cout << "\n   [1] INICIAR" << endl;
    cout << "   [2] REGRAS DO JOGO" << endl;
    cout << "   [3] HISTÓRICO DE PONTUAÇÕES" << endl;
    cout << "   [4] SAIR" << endl;
    cout << "\nESCOLHA UMA OPÇÃO: " << endl;
}

int main(){
    //permite que o console exiba corretamente os caracteres especiais
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int op;
    //Loop infinito para exibir o menu
    while(true){
        menuPrincipal();
        cin >> op;

        switch (op){
            case 1:
            {
                //Limpa o buffer de entrada para remover o "\n" deixado pelo cin >> op;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string nomeJogador;
                cout << "BEM VINDO(A) AO JOGO DO MILHÃO!!! QUAL O SEU NOME?" << endl;
                //getline permite nome com espaços
                getline(cin,nomeJogador);


                const int premio[] = {1000, 5000, 20000, 100000, 1000000};
                int pontuacaoFinal = 0; //Variável para gerenicar os pontos
                int pulosRestantes = 1; //Variável para gerenciar os pulos
                int metadeRestantes = 1; //Variável para gerenciar cartas

                system("cls");//Limpa a tela

                cout << "O JOGO DO MILHÃO COMEÇOU, "+ nomeJogador + "!!!" << endl;

                system("pause");

                vector<Questao> bancodequestoes = carregarPerguntas("Perguntas.txt");

                if(!bancodequestoes.empty()){

                    exibirMensagem("PERGUNTAS CARREGADAS...");

                    jogar(bancodequestoes, 0, pontuacaoFinal, premio, pulosRestantes,metadeRestantes);//CHAMADA QUE INICIA O JOGO DO INDICE 0

                }else{
                    exibirMensagem("\nNENHUMA PERGUNTA CARREGADA!!!");
                }

                exibirMensagem("SUA PONTUAÇÃO FINAL FOI: R$ " + to_string(pontuacaoFinal));

                salvarPontuacao(nomeJogador,pontuacaoFinal);

                cout << "[MENSAGEM] OBRIGADO POR JOGAR!!!" << endl;

                system("pause");

            break;
            }
            case 2:

                exibirRegras();

            break;

            case 3:

                exibirPontuacao();


            break;
            case 4:

                cout << "[MENSAGEM] OBRIGADO POR JOGAR!!!" << endl;

                system("pause");

                return 0;

            break;

            default:

                cout << "OPÇÃO INVÁLIDA!!! TENTE NOVAMENTE..." << endl;

            break;
        }
    }

    return 0;
}
