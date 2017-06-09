/* 
 * File:   Principal.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 13:35
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Principal.h"
#include "Maquina.h"
#include "Formiga.h"
#include "LerDados.h"

using namespace std;

Principal::Principal() {
    srand (time(NULL));
    this->qntTarefas = 0;
    this->qntMaquinas = 0;
}

Principal::~Principal() {
    desalocarEstruturas();
    this->qntTarefas = 0;
    this->qntMaquinas = 0;
}

void Principal:: setTempoSetup(int ***arestas){
    this->arestasSetup = arestas;
}

void Principal:: setMatrizFeromonio(int **matriz){
    this->matrizFeromonio = matriz;
}

void Principal:: setGrafo(Tarefa *grafo){
    this->grafo = grafo;
}

void Principal:: setQntTarefas(int qntTarefas){
    this->qntTarefas =qntTarefas;
}

void Principal::setQntMaquinas(int qntMaquinas) {
    this->qntMaquinas = qntMaquinas;
}

void Principal::setLimPoluicao(int poluicao) {
    this->limitePoluicao = poluicao;
}

void Principal::setCustoMaquina(int *custoMaquina) {
    this->custoMaquina = custoMaquina;
}

void Principal::setAlfa(int* alfa) {
    this->alfa = alfa;
}

void Principal::setBeta(int* beta) {
    this->beta = beta;
}

void Principal::setDataEntrega(int* dataEntrega) {
    this->dataEntrega = dataEntrega;
}

void Principal::setMatrizTarefas(int** matrizTarefas) {
    this->matrizTarefas = matrizTarefas;
}

int*** Principal:: getTempoSetup(){
    return this->arestasSetup;
}

int** Principal:: getMatrizFeromonio(){
    return this->matrizFeromonio;
}

Tarefa* Principal:: getGrafo(){
    return this->grafo;
}

int Principal::getQntTarefas(){
    return this->qntTarefas;
}

int Principal::getQntMaquinas() {
    return this->qntMaquinas;
}

int Principal::getLimPoluicao() {
    return this->limitePoluicao;
}

int* Principal::getCustoMaquina() {
    return this->custoMaquina;
}

int* Principal::getAlfa() {
    return this->alfa;
}

int* Principal::getBeta() {
    return this->beta;
}

int* Principal::getDataEntrega() {
    return this->dataEntrega;
}

int** Principal::getMatrizTarefas() {
    return this->matrizTarefas;
}

/**
 *  Inicializa a matriz com qntTarefas X qntTarefas.
 * @param qntTarefas
 */
void Principal::inicializarMatrizFeromonio(int qntTarefas) {
    this->matrizFeromonio = new int*[qntTarefas];
    
    for(int index = 0; index < qntTarefas; index++){
        this->matrizFeromonio[index] = new int[qntTarefas];
    }
}

/**
 *  Inicializa as estruturas iniciais do programa.
 */
void Principal::inicializarEstruturas() {
    LerDados *ler = new LerDados();
    ler->lerArquivo("m2n5tau0.3R0.25eta0.25i0.txt");
    
    this->qntMaquinas = ler->getNumMaquinas();
    this->qntTarefas = ler->getNumTarefas();
    this->arestasSetup = ler->getSetupTarefas();
    this->matrizTarefas = ler->getTarefas();
    this->limitePoluicao = ler->getLimitePoluicao();
    this->custoMaquina = ler->getCusto();
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
    bool notEnd = false;
    
    inicializarEstruturas();
    criarGrafo(this->qntTarefas,this->qntMaquinas);
    
    imprimirDados();
    
//    while(!notEnd){
//        
//    }
}

/**
 *  Cria o grafo completo com as tarefas, em que cada posição do vetor 
 * possui todas as tarefas, menos a tarefa indice do vetor.
 */
void Principal :: criarGrafo(int qntTarefas, int qntMaquinas){
    this->grafo = new Tarefa[this->qntTarefas];
    
    for(int index = 0; index < this->qntTarefas; index++){
        this->grafo[index].setIndice(index);
        Tarefa *tarefa = &(this->grafo[index]);    
        
        for(int i = 0; i < this->qntTarefas; i++){
            if(i != index){
                tarefa->setProxima(new Tarefa(i));
                tarefa = tarefa->getProxima();
            }
        }
    }
}

/**
 * Cria um vetor de formigas do tamanho de qntFormigas e inicializa o vetor de 
 * tarefas (caminho) de cada uma.
 */
Formiga* Principal :: criarFormiga(int qntFormigas,int qntTarefas){
    Formiga *formiga = new Formiga[qntFormigas];
    
    for(int index = 0; index < qntFormigas; index++){
        formiga[index] = Formiga();
        formiga[index].criarTarefasCaminho(qntTarefas);
    }
    return formiga;
}

/**
 *  Imprime o grafo com suas tarefas alocadas.
 */
void Principal :: imprimirGrafo(){
    
    for(int index = 0; index < this->qntTarefas; index++){
        Tarefa *tarefa = &(this->grafo[index]);
        
        cout << "Origem | " << this->grafo[index].getIndice() << " | -> ";
        
        while(tarefa->getProxima() != NULL){
            tarefa = tarefa->getProxima();
            cout << tarefa->getIndice() << " -> ";
        }
        cout << endl;
    }
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
    
    for(int index = 0; index < this->qntTarefas; index++){
        this->grafo[index].setProxima( desalocarNos(this->grafo[index].getProxima()));
    }
    delete [] this->grafo;
    desalocarMatriz(this->arestasSetup,this->qntTarefas,this->qntTarefas);
    desalocarMatriz(this->matrizFeromonio,this->qntTarefas,this->qntTarefas);
}

/**
 * 
 */
Tarefa* Principal :: desalocarNos(Tarefa *no){
    if(no->getProxima() != NULL){
        no->setProxima( desalocarNos(no->getProxima()) );
    }
    delete no;
    return NULL;
}

/**
 * 
 */
void Principal :: desalocarMatriz(int *matriz, int linhas, int colunas){
    delete [] matriz;
}

/**
 * 
 */
void Principal :: desalocarMatriz(int **matriz, int linhas, int colunas){
    for(int index = 0; index < colunas; index++){
        delete [] matriz[index];
    }
    delete [] matriz;
}

/**
 * 
 */
void Principal :: desalocarMatriz(int ***matriz, int linhas, int colunas){
    for(int index = 0; index < colunas; index++){
        delete [] matriz[index];
    }
    delete [] matriz;
}

/**
 * 
 */
int Principal :: getRandomNumero(int range, int limSup){
    return (rand() % range + limSup);
}

/**
 * 
 */
void Principal :: imprimirDados(){
    cout << "Numero de maquinas : " << this->qntMaquinas << endl;
    cout << "Numero de tarefas : " << this->qntTarefas << endl;
    cout << "Custo de maquinas : " << endl;
    for(int i = 0; i < this->qntMaquinas; i++){
        cout << this->custoMaquina[i] << " ";
    }
    cout << "\nTempos das tarefas : " << endl;
    for(int i = 0; i < this->qntTarefas; i++){
        for(int k = 0; k < this->qntMaquinas; k++){
            cout << this->matrizTarefas[i][k] << " ";
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