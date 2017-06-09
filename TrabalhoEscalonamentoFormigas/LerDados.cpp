/* 
 * File:   LerDados.cpp
 * Author: igor
 * 
 * Created on 4 de Junho de 2017, 19:29
 */

#include "LerDados.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

LerDados::LerDados(){
    this->limitePoluicao = 0;
    this->numMaquinas = 0;
    this->numTarefas = 0;
    this->custo = NULL;
    this->matrizTarefas = NULL;
    this->setupTarefas = NULL;
}

LerDados::~LerDados(){
    this->limitePoluicao = 0;
    this->numMaquinas = 0;
    this->numTarefas = 0;
    this->alfa = NULL;
    this->beta = NULL;
    this->custo = NULL;
    this->dataEntrega = NULL;
    this->matrizTarefas = NULL;
    this->setupTarefas = NULL;
}

void LerDados :: lerArquivo(string file){
    ifstream arquivo (file.c_str());
    int k = 0,j = 0;
    string informacao = string();
    string s = string();
    string a = string();
    stringstream ss;

    if(arquivo.is_open()){

        /// Ler numero de máquinas
        getline(arquivo,informacao);
        this->numMaquinas = atoi(informacao.substr(0,informacao.size()+1).c_str());

        /// ler numero de tarefas
        getline(arquivo,informacao);
        this->numTarefas = atoi(informacao.substr(0,informacao.size()+1).c_str());

        getline(arquivo,informacao); // vazio

        this->custo = new int[this->numMaquinas];

        /// Ler custo das máquinas
        getline(arquivo,informacao);
        for(int j = 0; j < informacao.size() && k < this->numMaquinas; j++){
            while((informacao[j] != ' ')&&(j < informacao.size())){
                s.insert(s.end(),informacao[j]);
                j += 1;
            }
            this->custo[k] = atoi(s.c_str());
            s.clear();
            k += 1;
        }
        k = 0;

        getline(arquivo,informacao); // vazio

        /// instanciar matriz de tempos de tarefas
        this->matrizTarefas = new int*[this->numTarefas];

        for(int i = 0; i < this->numTarefas;i++){
            this->matrizTarefas[i] = new int[this->numMaquinas];
        }

        /// instanciar cubo de setup de tarefas
        this->setupTarefas = new int**[numTarefas];

        for(int i = 0; i < this->numTarefas;i++){
            this->setupTarefas[i] = new int*[this->numTarefas];

            for(int j = 0; j < this->numTarefas;j++){
                this->setupTarefas[i][j] = new int[this->numMaquinas];
            }
        }

        /// instanciar data de entrega
        this->dataEntrega = new int[numTarefas];

        /// instanciar alfa
        this->alfa = new int[numTarefas];

        /// instanciar beta
        this->beta = new int[numTarefas];

        /// ler tempo das tarefas
        for(int i = 0; i < numTarefas; i++){
            getline(arquivo,informacao); // tarefas

            for(int j=0; j < informacao.size() && k < this->numTarefas;j++){
                while((informacao[j] != ' ')&&(j < informacao.size())){
                    s.insert(s.end(),informacao[j]);
                    j += 1;
                }
                this->matrizTarefas[i][k] = atoi(s.c_str());
                s.clear();
                k += 1;
            }
            k = 0;
        }

        s = string();
        int j = 0;

        /// ler setup
         for(int k = 0; k < numMaquinas; k++){
            for(int i = 0; i < numTarefas; i++){
                getline(arquivo,informacao);

                for(int t = 0; t < informacao.size() && j < this->numTarefas;t++){
                    while((informacao[t] != ' ')&&(t < informacao.size())){
                        s.insert(s.end(),informacao[t]);
                        t += 1;
                    }
                    this->setupTarefas[i][j][k] = atoi(s.c_str());
                    s.clear();
                    j += 1;
                }
                j = 0;
            }
        }

        s = string();

         /// ler data de entrega
        getline(arquivo,informacao);

        s.clear();
        int indice = 0;

        for(int j=0; j < informacao.size() && indice < this->numTarefas;j++){
            while((informacao[j] != ' ')&&(j < informacao.size())){
                s.insert(s.end(),informacao[j]);
                j += 1;
            }
            this->dataEntrega[indice] = atoi(s.c_str());
            s.clear();
            indice += 1;
        }

        s = string();

        /// ler beta
        getline(arquivo,informacao);

        s.clear();
        indice = 0;

        /// atribuir beta
        for(int j=0; j < informacao.size() && indice < this->numTarefas;j++){
            while((informacao[j] != ' ')&&(j < informacao.size())){
                s.insert(s.end(),informacao[j]);
                j += 1;
            }
            this->beta[indice] = atoi(s.c_str());
            s.clear();
            indice += 1;
        }

        s = string();

        /// alfa
        getline(arquivo,informacao);

        s.clear();
        indice = 0;

        /// atribuir alfa
        for(int j=0; j < informacao.size() && indice < this->numTarefas;j++){
            while((informacao[j] != ' ')&&(j < informacao.size())){
                s.insert(s.end(),informacao[j]);
                j += 1;
            }
            this->alfa[indice] = atoi(s.c_str());
            s.clear();
            indice += 1;
        }

        getline(arquivo,informacao); // vazio

        /// Ler limite de poluicao
        getline(arquivo,informacao);
        this->limitePoluicao = atoi(informacao.substr(0,informacao.size()+1).c_str());

    }else{
        cout << "Não foi possível abrir o arquivo !" << endl;
    }

    arquivo.close();
}

int** LerDados :: getTarefas(){
    return this->matrizTarefas;
}

int*** LerDados :: getSetupTarefas(){
    return this->setupTarefas;
}

int* LerDados :: getCusto(){
    return this->custo;
}

int LerDados :: getNumTarefas(){
    return this->numTarefas;
}

int LerDados :: getNumMaquinas(){
    return this->numMaquinas;
}

int LerDados :: getLimitePoluicao(){
    return this->limitePoluicao;
}

int* LerDados :: getDataEntrega(){
    return this->dataEntrega;
}

int* LerDados :: getAlfa(){
    return this->alfa;
}

int* LerDados :: getBeta(){
    return this->beta;
}

void LerDados :: calculaCustoMaquina(){
    this->custo = new int[this->numMaquinas];

    for(int k = 0; k < this->numMaquinas; k++)
        this->custo[k] = aleatorio(100,50);
}

void LerDados :: calculaLimitePoluicao(){
    int limite = 0;
    int menor = 1000000;

    for(int k = 0; k < this->numMaquinas; k++){
        for(int i = 0; i < this->numTarefas; i++){
//            for(int j = 1; j <= this->numTarefas; j++){
//                limite += this->custo[i] * (this->matrizTarefas[k][i] + this->setupTarefas[i][j][k]);
                limite += this->custo[k] * this->matrizTarefas[i][k];
//            }
        }
        if(limite < menor)
            menor = limite;
    }
    this->limitePoluicao = menor;
}

int LerDados :: aleatorio(int limiteSup,int limiteInf){
    return (rand() % limiteSup + limiteInf);
}

void LerDados :: imprimirDados(){
    cout << "Numero de maquinas : " << this->numMaquinas << endl;
    cout << "Numero de tarefas : " << this->numTarefas << endl;

    cout << "Custo de maquinas : " << endl;
    for(int i = 0; i < this->numMaquinas; i++)
        cout << this->custo[i] << " ";

    cout << endl;

    cout << "Tempos das tarefas : " << endl;
    for(int i = 0; i < this->numTarefas; i++){
        for(int k = 0; k < this->numMaquinas; k++){
            cout << this->matrizTarefas[i][k] << " ";
        }
        cout << "\n";
    }

    cout << endl;

    cout << "Setup : " << endl;
    for(int k = 0; k < this->numMaquinas; k++){
        for(int i = 0; i < this->numTarefas; i++){
            for(int j = 0; j < this->numTarefas; j++){
                cout << this->setupTarefas[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << endl;

    cout << "Alfa : " << endl;
    for(int i = 0; i < this->numTarefas; i++)
        cout << this->alfa[i] << " ";

    cout << endl;

    cout << "Beta : " << endl;
    for(int i = 0; i < this->numTarefas; i++)
        cout << this->beta[i] << " ";

    cout << endl;

    cout << "Limite de poluicao : " << this->limitePoluicao << "\n\n" << endl;
}