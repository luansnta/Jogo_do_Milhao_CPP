if(respostaJogador == 'P'){
            if(pulosRestantes > 0){
                pulosRestantes --; //Diminui o valor original
                return PULO; //Pula a questão, sai da função e do loop
            }else{
                cout << "PULO ESGOTADO!!" << endl;
                //O loop continua até o jogador responder a questão
            }