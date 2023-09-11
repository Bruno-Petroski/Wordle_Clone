#include <conio.h>
#include <iostream>
#include <locale.h>
#include <time.h>
#include <windows.h>

#include "dicionario.hpp"

using namespace std;

void rand_Palavra(string &Palavra, string lista[],int TAM){
    Palavra = lista[rand() % TAM_LISTA];
}

void verifica_if(string palavraInserida, int &contInvalido) {

    for (int i = 0; i < 5; i++) {
        if (palavraInserida[i] != 'A' && palavraInserida[i] != 'B' &&
            palavraInserida[i] != 'C' && palavraInserida[i] != 'D' &&
            palavraInserida[i] != 'E' && palavraInserida[i] != 'F' &&
            palavraInserida[i] != 'G' && palavraInserida[i] != 'H' &&
            palavraInserida[i] != 'I' && palavraInserida[i] != 'J' &&
            palavraInserida[i] != 'K' && palavraInserida[i] != 'L' &&
            palavraInserida[i] != 'M' && palavraInserida[i] != 'N' &&
            palavraInserida[i] != 'O' && palavraInserida[i] != 'P' &&
            palavraInserida[i] != 'Q' && palavraInserida[i] != 'R' &&
            palavraInserida[i] != 'S' && palavraInserida[i] != 'T' &&
            palavraInserida[i] != 'U' && palavraInserida[i] != 'V' &&
            palavraInserida[i] != 'W' && palavraInserida[i] != 'X' &&
            palavraInserida[i] != 'Y' && palavraInserida[i] != 'Z') {

            contInvalido++;
        }
    }
}

void verifica_P(string palavraInserida, int &Valido) {
    int contInvalido = 0;

    // VERIFICA TAMANHO PALAVRA
    if (palavraInserida.length() != 5) {
        cout << "Palavra deve possuir 5 letras" << endl;
        Valido = 0;
    }

    // VERIFICA LETRA
    verifica_if(palavraInserida, contInvalido);

    // RETORNA VALIDO
    if (contInvalido != 0) {
        cout << "Caracter Invalido" << endl;
        Valido = 0;
        contInvalido = 0;
    }
}


void troca_Cor(string Termo[8][23], int X, string palavraInserida,string palavraCerta, int flag, int &G) {
    string trocaCor;
    int P = 0;
    /// Flag = 1 - Palavra 1 - P = 0
    ///        2 - Palavra 2 - P = 6
    ///        3 - Palavra 3 - P = 12
    ///        4 - Palavra 4 - P = 18

    if(flag == 2){
        P = 6;
    }else if(flag == 3){
        P = 12;
    }else if(flag == 4){
        P = 18;
    }

    for(int i = 0; i < 5; i++){
        /// INSERE PALAVRA NA MATRIZ/
        Termo[X][i + P] = palavraInserida[i];

        /// VERIFICA LETRA CERTA NA POSIÇÃO ERRADA
        for(int L = 0; L < 5; L++){
            if(palavraInserida[i] == palavraCerta[L] && i != L &&palavraInserida[i] != palavraInserida[L]){
                trocaCor = palavraInserida[i]; trocaCor = "\033[33m" + trocaCor + "\033[0m";

                Termo[X][i + P] = trocaCor;
            }
        }

        /// VERIFICA LETRA CERTA NA POSIÇÃO CERTA
        if(palavraCerta[i] == palavraInserida[i]){
            trocaCor = palavraCerta[i];
            trocaCor = "\033[32m" + trocaCor + "\033[0m";

            Termo[X][i + P] = trocaCor;
        }
    }

    if(palavraInserida == palavraCerta){
        G = 1;
    }

    /// Somar X la fora, após todos os troca cor forem utilizados
}

int main() {

    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");
    // DEFININDO OS MENUS
    string Menu, Creditos, Sair, Regras;

  Menu = {
    "\033[32m                                        ######\n"
    "                                        # ## #\n"
    "                                          ##      ####    ######   ####    ####\n"
    "                                          ##     ##  ##    ##  ##  #######  ##  ##\n"
    "                                          ##     ######    ##      ## # ##  ##  ##\n"
    "                                          ##     ##        ##      ##   ##  ##  ##\n"
    "                                         ####     #####   ####     ##   ##   ####\033[0m\n\n\n\n\n"
    "                                                       1 - Termo\n"
    "                                                       2 - Dueto\n"
    "                                                       3 - Trieto\n"
    "                                                       4 - Quarteto\n\n"
    "                                                       5 - Tutorial\n"
    "                                                       6 - Creditos\n"
    "                                                       7 - Sair\n"
  };

  Creditos = {
    "\n\n\n\n\n\n\n\n\n\n\n"
    "\033[32m                                                  @Bruno_Petroski_Enghi\n"
    "                                                  @Gabriel_Santos_Bortoloci\n\n\033[0m"
    "                                            Pressione qualquer tecla para voltar!"
  };

  Sair = {
    "\n\n\n\n\n\n\n\n\n\n\n"
    "                                                     \033[32mObrigado Por Jogar!!\033[0m"
    "\n\n\n\n\n\n\n\n\n\n\n"
    };

  Regras = {"\n\n\n\n\n\n\n\n\n"
            "                                                    Bem-vindo ao Termo\n\n"
            "                                         O seu objetivo é digitar a palavra certa.\n"
            "                                                  A palavra tem 5 letras.\n"
            "\n"
            "                                    A letra ficara \033[32mverde\033[0m caso esteja na posição correta.\n"
            "                      E \033[33mamarela\033[0m caso a letra estiver presente na palavra, mas está na posição errada!\n"
            "\n"
            "                 Ao inserir palavras tenha certeza de que ela tenha 5 letras que estejam em maiusculas apenas!\n\n"
            "                                           Pressione qualquer tecla para continuar!"
            };


    string palavraTermo, palavraDueto, palavraTrio, palavraQuart, palavraInserida, palavraInseridaString[5];
    int Jogar = 1, Escolha, Ganhou, Valido, X, L, P1, P2, P3, P4, flag;


    while (Jogar == 1) {
        system("cls");
        cout << Menu << endl;

        /// ESCOLHA DE MODO
        do {
            /// CIN IGNORE
            while (!(cin >> Escolha)) {
                cout << "Escolha Invalida" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            if (Escolha != 1 && Escolha != 2 && Escolha != 3 && Escolha != 4 && Escolha != 5 && Escolha != 6 && Escolha != 7) {
                cout << "Escolha Invalida a" << endl;
            }
        } while (Escolha != 1 && Escolha != 2 && Escolha != 3 && Escolha != 4 && Escolha != 5 && Escolha != 6 && Escolha != 7);

        switch (Escolha) {
        case 1: {
            // TERMO
            system("cls");
            //                  PALAVRA 1             ---  PALAVRA 2                --- PALAVRA 3                 ---  PALAVRA 4
            string Termo[8][23] = {{"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"}};

            Ganhou = 0;
            X = 0;
            L = 0;


            /// REGRAS
            cout << Regras << endl;
            while (!kbhit()) {}
            system("cls");

            /// Termo
            rand_Palavra(palavraTermo, lista, TAM_LISTA);

            /// CONTROLADOR DE TENTATIVAS - TERMO = 6 TENTATIVAS
            for (int i = 0; i < 6; i++) {
                system("cls");

                /// IMPRIMINDO MATRIZ
                for (int i = 0; i < 6; i++) {
                    cout << "\n\n                                                        ";
                    for (int j = 0; j < 5; j++) {
                        cout << Termo[i][j] << " ";
                    }
                }
                cout<<endl;

                /// VERIFICANDO PALAVRA INSERIDA
                do{
                    cin >> palavraInserida;
                    Valido = 1;

                    /// FUNÇÃO PARA VERIFICAR PALAVRA
                    verifica_P(palavraInserida, Valido);

                }while (Valido == 0);

                /// VERIFICA SE GANHOU
                if (palavraTermo == palavraInserida) {
                    Ganhou = 1;
                    break;
                }

                /// TROCA COR
                // 1 para posicionar na primeira palavra
                troca_Cor(Termo,X,palavraInserida,palavraTermo,1,P1);
                X++;

            }
            /// MENSAGEM DE VITORIA E DERROTA
            system("cls");
            if (Ganhou == 1) {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                   Parabens você ganhou!!!" << endl;
                cout << "                                              As palavras certas eram\033[32m \"" << palavraTermo << "\"\033[0m." << endl;
                cout << "                                             Aperte qualquer tecla para voltar!" << endl;
            } else {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                   \033[31mNão foi desta vez!!!\033[0m" << endl;
                cout << "                                                 A palavra certa era \033[32m\"" << palavraTermo << "\"\033[0m." << endl;
                cout << "                                             Aperte qualquer tecla para voltar!" << endl;
            }

            while (!kbhit()) {}

            break;
            }

        case 2: {
            // Dueto
            system("cls");
            string Termo[8][23] = {{"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"}};


            Ganhou = 0;
            X = 0;
            L = 0;
            P1 = 0;
            P2 = 0;

            /// REGRAS
            cout << Regras << endl;
            while (!kbhit()) {}

            /// DUETO
            // PALAVRA 1
            rand_Palavra(palavraTermo, lista, TAM_LISTA);
            // PALAVRA 2
            do{
              rand_Palavra(palavraDueto, lista, TAM_LISTA);
            }while(palavraDueto == palavraTermo);


            /// CONTROLADOR DE TENTATIVAS - DUETO = 7
            for (int i = 0; i < 7; i++){
                system("cls");
                /// IMPRIMINDO MATRIZ
                for (int i = 0; i < 7; i++) {
                    cout << "\n\n                                             ";
                    for (int j = 0; j < 11; j++) {
                        cout << Termo[i][j] << " ";
                    }
                }
                cout<<endl;

                /// VERIFICA PALAVRA INSERIDA
                do {
                    cin >> palavraInserida;
                    Valido = 1;
                    /// FUNÇÃO PARA VERIFICAR PALAVRA
                    verifica_P(palavraInserida, Valido);
                }while (Valido == 0);

                /// TROCA COR / INSERIR NA MATRIZ
                // 1 - Palavra 1 / 2- Palavra 2
                if(P1 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraTermo,1,P1);
                }
                if(P2 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraDueto,2,P2);
                }

                X++;
                if (P1 != 0 && P2 != 0) {
                    Ganhou = 1;
                    break;
                }
            }
            /// MENSAGEM DE VITORIA E DERROTA
            system("cls");
            if (Ganhou == 1) {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                   Parabens você ganhou!!!" << endl;
                cout << "                                         As palavras certas eram\033[32m \"" << palavraTermo << "\"\033[0m e \033[32m\"" << palavraDueto << "\"\033[0m." << endl;
                cout << "                                             Aperte qualquer tecla para voltar!" << endl;
            } else {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                       \033[31mNão foi desta vez!!!\033[0m" << endl;
                cout << "                                           As palavras certas eram \033[32m\"" << palavraTermo << "\"\033[0m e \033[32m\"" << palavraDueto << "\"\033[0m." << endl;
                cout << "                                               Aperte qualquer tecla para voltar!" << endl;
            }
            while (!kbhit()) {}

            break;
        }
        case 3:{
            // Trieto
            system("cls");
            string Termo[8][23] = {{"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"}};

            Ganhou = 0;
            X = 0;
            L = 0;
            P1 = 0;
            P2 = 0;
            P3 = 0;

            /// REGRAS
            cout << Regras << endl;
            while (!kbhit()) {}

            /// TRIETO
            // PALAVRA 1
            rand_Palavra(palavraTermo, lista, TAM_LISTA);
            // PALAVRA 2
            do{
                rand_Palavra(palavraDueto, lista, TAM_LISTA);
            }while(palavraDueto == palavraTermo);
            // PALAVRA 3
            do{
                rand_Palavra(palavraTrio, lista, TAM_LISTA);
            }while(palavraTrio == palavraTermo || palavraTrio == palavraDueto);


            for (int i = 0; i < 8; i++){
                system("cls");

                /// IMPRIMINDO MATRIZ
                for (int i = 0; i < 8; i++) {
                    cout << "\n\n                                             ";
                    for (int j = 0; j < 17; j++) {
                        cout << Termo[i][j] << " ";
                    }
                }
                cout<<endl;

                /// VERIFICA PALAVRA INSERIDA
                do {
                    cin >> palavraInserida;
                    Valido = 1;
                    /// FUNÇÃO PARA VERIFICAR PALAVRA
                    verifica_P(palavraInserida, Valido);
                }while (Valido == 0);

                /// TROCA COR / INSERIR NA MATRIZ
                // 1 - Palavra 1 / 2- Palavra 2 / 3 - Palavra 3
                if(P1 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraTermo,1,P1);
                }
                if(P2 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraDueto,2,P2);
                }
                if(P3 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraTrio,3,P3);
                }

                X++;
                if (P1 != 0 && P2 != 0 && P3 != 0) {
                    Ganhou = 1;
                    break;
                }
            }

            /// MENSAGEM DE VITORIA E DERROTA
            system("cls");
            if (Ganhou == 1) {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                   Parabens você ganhou!!!" << endl;
                cout << "                                       As palavras certas eram\033[32m \"" << palavraTermo << "\"\033[0m, \033[32m\"" << palavraDueto << "\" \033[0me\033[32m \"" << palavraTrio << "\"\033[0m." << endl;
                cout << "                                             Aperte qualquer tecla para voltar!" << endl;
            } else {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                       \033[31mNão foi desta vez!!!\033[0m" << endl;
                cout << "                                       As palavras certas eram \033[32m\"" << palavraTermo << "\"\033[0m, \033[32m\"" << palavraDueto << "\" \033[0me\033[32m \"" << palavraTrio << "\"\033[0m." << endl;
                cout << "                                               Aperte qualquer tecla para voltar!" << endl;
            }
            while (!kbhit()) {}





            break;
        }
        case 4:{
            // Quarteto
            system("cls");
            string Termo[8][23] = {{"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"},
                                   {"_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_", " ", "_", "_", "_", "_", "_"}};
            Ganhou = 0;
            Valido = 1;
            X = 0;
            L = 0;
            P1 = 0;
            P2 = 0;
            P3 = 0;
            P4 = 0;

            /// REGRAS
            cout << Regras << endl;
            while (!kbhit()) {}

            /// Quarteto
            // PALAVRA 1
            rand_Palavra(palavraTermo, lista, TAM_LISTA);
            // PALAVRA 2
            do{
                rand_Palavra(palavraDueto, lista, TAM_LISTA);
            }while(palavraDueto == palavraTermo);
            // PALAVRA 3
            do{
                rand_Palavra(palavraTrio, lista, TAM_LISTA);
            }while(palavraTrio == palavraTermo || palavraTrio == palavraDueto);
            // PALAVRA 4
            do{
                rand_Palavra(palavraQuart, lista, TAM_LISTA);
            }while(palavraQuart == palavraTermo || palavraQuart == palavraDueto || palavraQuart == palavraTrio);

            /// CONTROLADOR DE TENTATIVAS - QUARTETO = 4
            for (int i = 0; i < 8; i++){
                system("cls");

                /// IMPRIMINDO MATRIZ
                for (int i = 0; i < 8; i++) {
                    cout << "\n\n                                        ";
                    for (int j = 0; j < 23; j++) {
                        cout << Termo[i][j] << " ";
                    }
                }
                cout<<endl;

                /// VERIFICA PALAVRA INSERIDA
                do {
                    cin >> palavraInserida;
                    Valido = 1;
                    /// FUNÇÃO PARA VERIFICAR PALAVRA
                    verifica_P(palavraInserida, Valido);
                }while (Valido == 0);

                /// TROCA COR / INSERIR NA MATRIZ
                // 1 - Palavra 1 / 2 - Palavra 2 / 3 - Palavra 3 / 4 - Palavra 4
                if(P1 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraTermo,1,P1);
                }
                if(P2 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraDueto,2,P2);
                }
                if(P3 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraTrio,3,P3);
                }
                if(P4 == 0){
                    troca_Cor(Termo,X,palavraInserida,palavraQuart,4,P4);
                }

                X++;
                if (P1 != 0 && P2 != 0 && P3 != 0 && P4 != 0) {
                    Ganhou = 1;
                    break;
                }
            }
            /// MENSAGEM DE VITORIA E DERROTA
            system("cls");
            if (Ganhou == 1) {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                   Parabens você ganhou!!!" << endl;
                cout << "                                       As palavras certas eram\033[32m \"" << palavraTermo << "\"\033[0m, \033[32m\"" << palavraDueto << "\"\033[0m,\033[32m \"" << palavraTrio << "\" \033[0me \033[32m" << palavraQuart << "\"\033[0m." << endl;
                cout << "                                             Aperte qualquer tecla para voltar!" << endl;
                } else {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "                                                       \033[31mNão foi desta vez!!!\033[0m" << endl;
                cout << "                                       As palavras certas eram \033[32m\"" << palavraTermo << "\"\033[0m, \033[32m\"" << palavraDueto << "\" \033[0me\033[32m \"" << palavraTrio << "\" \033[0me \033[32m" << palavraQuart << "\"\033[0m." << endl;
                cout << "                                               Aperte qualquer tecla para voltar!" << endl;
            }
            while (!kbhit()) {}

            break;
        }
        case 5:{
            // Tutorial / Regras
            system("cls");
            cout << Regras;
            while (!kbhit()) {}
            break;
        }
        case 6:{
            // Creditos
            system("cls");
            cout << Creditos;
            while (!kbhit()) {}
            break;
        }
        case 7:{
            // Sair
            system("cls");
            cout << Sair << endl;
            Sleep(1000);
            Jogar = 0;
            break;
        }
        }
    }
}
