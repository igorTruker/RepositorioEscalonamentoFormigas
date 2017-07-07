/* 
 * File:   Principal.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 13:35
 */

#include <iostream>
#include "Principal.h"
#include "Maquina.h"
#include "Formiga.h"
#include "LerDados.h"
#include "Grafo.h"
#include <stdlib.h>

using namespace std;

Principal::Principal() {
    srand (time(NULL));
    this->qntTarefas = 0;
    this->qntMaquinas = 0;
    this->arestasSetup = NULL;
    this->matrizTempoTarefas = NULL;
    this->limitePoluicao = -1;
    this->custoPoluicaoMaquina = NULL;
    this->alfa = NULL;
    this->beta = NULL;
    this->dataEntrega = NULL;
}

Principal::~Principal() {
    desalocarEstruturas();
    this->qntTarefas = 0;
    this->qntMaquinas = 0;
    this->arestasSetup = NULL;
    this->matrizTempoTarefas = NULL;
    this->limitePoluicao = -1;
    this->custoPoluicaoMaquina = NULL;
    this->alfa = NULL;
    this->beta = NULL;
    this->dataEntrega = NULL;
}

int Principal::getQntTarefas(){
    return this->qntTarefas;
}

/**
 *  Inicializa a matriz com qntTarefas X qntTarefas.
 * @param qntTarefas
 */
void Principal::inicializarMatrizFeromonio(int qntTarefas) {
    this->matrizFeromonio = new int*[qntTarefas];
    
    for(int index = 0; index < qntTarefas; index++){
        this->matrizFeromonio[index] = new int[qntTarefas];
        
        for(int indexJ = 0; indexJ < qntTarefas; indexJ++){
            this->matrizFeromonio[index][indexJ] = 0;
        }
    }
}

/**
 *  Inicializa as estruturas iniciais do programa.
 */
void Principal::inicializarEstruturas() {
    LerDados *ler = new LerDados();
//    ler->lerArquivo("instancias/m2n5tau0.3R0.25eta0.25i0.txt");
//    ler->lerArquivo("instancias/I3-m5n8-A.txt");
    ler->lerArquivo("instancias/m3n50tau0.3R0.25eta0.25i4-I.D.txt");
    
    this->qntMaquinas = ler->getNumMaquinas();
    this->qntTarefas = ler->getNumTarefas();
    this->arestasSetup = ler->getSetupTarefas();
    this->matrizTempoTarefas = ler->getTarefas();
    this->limitePoluicao = ler->getLimitePoluicao();
    this->custoPoluicaoMaquina = ler->getCusto();
    this->alfa = ler->getAlfa();
    this->beta = ler->getBeta();
    this->dataEntrega = ler->getDataEntrega();
    
    delete ler;
    
    inicializarMatrizFeromonio(this->qntTarefas);
}

/**
 *  Executa o procedimento principal do algoritmo.
 */
void Principal::executar(){    
    
    inicializarEstruturas();
    criarGrafo(this->getQntTarefas());
    
    bool notEnd = false;
    double valorNormal = 0.0;
    int *limiteMin = new int[this->qntMaquinas];/* Limite minimo de poluicao para gastar*/
    int *valorAdic = new int[this->qntMaquinas]; /* Valor adicional para cada máquina*/
    int extra = 0;
    
    int cont = 3;
    
    while(!notEnd){
        valorNormal = 0.0;
        calcularLimiteMinimo(limiteMin); 
        extra = calcularExtra(limiteMin);
        calcularValorAdicional(valorAdic,&valorNormal,extra,limiteMin);
        
        this->grafo->resetarSelecaoGrafo(); // reseta a seleção do grafo
        
        int indiceTarefa = getRandomNumero(this->qntTarefas,0);
        
        for(int indexFormiga = 0; indexFormiga < this->qntMaquinas; indexFormiga++){
            Formiga *formigas = new Formiga();
            
            while(limiteMin[indexFormiga] > 0 && indiceTarefa != -1){                        
                limiteMin[indexFormiga] =  limiteMin[indexFormiga]-(this->matrizTempoTarefas[indiceTarefa][indexFormiga] * this->custoPoluicaoMaquina[indexFormiga]);                
//                cout << "Limite Min : " << limiteMin[indexFormiga] << endl;

                if(limiteMin[indexFormiga] > 0){
                    /*
                     FAZER FUNÇÃO PARA ESCOLHER MELHOR CAMINHO  |  |  |
                     *                                          V  V  V
                     */
                    formigas->adicionarTarefa( this->grafo->removerTarefa(indiceTarefa,indiceTarefa)); // alterar indice
                    /* Selecionar proxima tarefa*/
                    indiceTarefa = getProximaTarefaAleatoria();
                }      
            }
            formigas->imprimirDados();
            delete formigas;
            cout <<"\n"<< endl;
        }
        
        if(cont == 0)
            notEnd = true;
        else
            cont -= 1;
        
        delete [] limiteMin;
        delete [] valorAdic;
    }
}

/*
 * Retorna o vetor com o limite minimo de poluição para cada máquina
 */
void Principal::calcularLimiteMinimo(int *vetor) {
    int menorPoluicao = 0;
    int calcPoluicao = 0;
    int maqMenorPoluicao = 0;
    
    for(int index = 0; index < this->qntMaquinas; index++){
        vetor[index]= 0;
    }    
    menorPoluicao = this->custoPoluicaoMaquina[0] * this->matrizTempoTarefas[0][0];
    
    for(int index = 0; index < this->qntTarefas; index++){
        maqMenorPoluicao = 0;
        menorPoluicao = this->custoPoluicaoMaquina[maqMenorPoluicao] * this->matrizTempoTarefas[index][maqMenorPoluicao];
        
        for(int indexMaq = 1; indexMaq < this->qntMaquinas; indexMaq++){
            calcPoluicao = this->custoPoluicaoMaquina[indexMaq] * this->matrizTempoTarefas[index][indexMaq];
            if(menorPoluicao > calcPoluicao){
                menorPoluicao = calcPoluicao;
                maqMenorPoluicao = indexMaq;
            }
        }
        vetor[maqMenorPoluicao] += menorPoluicao;
    }
    
    for(int index = 0; index < this->qntMaquinas; index++){
        cout << " Limite Min [ "<< index <<" ] : " << vetor[index] << endl;
    }    
}

int Principal::calcularExtra(int *limiteMin) {
    int extra = 0;
    for(int index = 0; index < this->qntMaquinas; index++){
        extra += limiteMin[index];
    }
    extra = this->limitePoluicao - extra;
    cout << "Extra : " << extra << endl;
    return extra;
}

void Principal::calcularValorAdicional(int* valorAdic, double *valorNormal, int extra, int* limiteMin) {
    /* Inicializar o vetor da taxa adicional para com os valores aleatorios*/
    for(int indexMaq = 0; indexMaq < this->qntMaquinas; indexMaq++){
        valorAdic[indexMaq] = getRandomNumero(100,0);
        *valorNormal += valorAdic[indexMaq];
    }
    
    for(int indexMaq = 0; indexMaq < this->qntMaquinas; indexMaq++){
        valorAdic[indexMaq] = (valorAdic[indexMaq]/ *valorNormal) * extra;
        cout << " valor Adic : " <<  valorAdic[indexMaq] << endl;
        limiteMin[indexMaq] += valorAdic[indexMaq];
        cout << " Limite Min : " <<  limiteMin[indexMaq] << endl;
    }
}

int Principal::getProximaTarefaAleatoria() {
    int tarefasNaoMarcadas = this->qntTarefas - this->grafo->getNumTarefasMarcadas() ;
    return this->grafo->getIndiceEnesimaTarefaNaoMarcada(tarefasNaoMarcadas);
}

/**
 *  Cria o grafo completo com as tarefas, em que cada posição do vetor 
 * possui todas as tarefas, menos a tarefa indice do vetor.
 */
void Principal :: criarGrafo(int qntTarefas){
    this->grafo = new Grafo(qntTarefas);
    this->grafo->criarGrafoCompleto(qntTarefas);
}

/**
 * Imprime a matriz.
 */
void Principal::imprimirMatrizFeromonio() {
    for(int indexI = 0; indexI < getQntTarefas(); indexI++){
        cout << endl;
        for(int indexJ = 0; indexJ < getQntTarefas(); indexJ++){
            cout << this->matrizFeromonio[indexI][indexJ] << " ";
        }
    }
    cout << endl;
}

/**
 * Desaloca todas as estruturas.
 */
void Principal :: desalocarEstruturas(){
    delete this->grafo;
    desalocarMatriz(this->arestasSetup,this->qntTarefas,this->qntTarefas);
    desalocarMatriz(this->matrizFeromonio,this->qntTarefas,this->qntTarefas);
}

void Principal :: desalocarMatriz(int *matriz, int linhas, int colunas){
    delete [] matriz;
}

void Principal :: desalocarMatriz(int **matriz, int linhas, int colunas){
    for(int index = 0; index < colunas; index++){
        delete [] matriz[index];
    }
    delete [] matriz;
}

void Principal :: desalocarMatriz(int ***matriz, int linhas, int colunas){
    for(int index = 0; index < colunas; index++){
        delete [] matriz[index];
    }
    delete [] matriz;
}

void Principal :: imprimirDados(){
    cout << "Numero de maquinas : " << this->qntMaquinas << endl;
    cout << "Numero de tarefas : " << this->qntTarefas << endl;
    cout << "Custo de maquinas : " << endl;
    for(int i = 0; i < this->qntMaquinas; i++){
        cout << this->custoPoluicaoMaquina[i] << " ";
    }
    cout << "\nTempos das tarefas : " << endl;
    for(int i = 0; i < this->qntTarefas; i++){
        for(int k = 0; k < this->qntMaquinas; k++){
            cout << this->matrizTempoTarefas[i][k] << " ";
        }
        cout << "\n";
    }
    cout << "\nSetup : " << endl;
    for(int k = 0; k < this->qntMaquinas; k++){
        for(int i = 0; i < this->qntTarefas; i++){
            for(int j = 0; j < this->qntTarefas; j++){
                cout << this->arestasSetup[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "\nAlfa : " << endl;
    for(int i = 0; i < this->qntTarefas; i++){
        cout << this->alfa[i] << " ";
    }
    cout << "\nBeta : " << endl;
    for(int i = 0; i < this->qntTarefas; i++){
        cout << this->beta[i] << " ";
    }
    cout << "\nLimite de poluicao : " << this->limitePoluicao << "\n\n" << endl;
}

/*
 * Gera um valor aleatório => rand() % range + limSup.
 * Ex: rand() % 100 + 1 => 1 a 99.
 */
int Principal::getRandomNumero(int range, int limInf) {
    return (rand() % range + limInf);
}