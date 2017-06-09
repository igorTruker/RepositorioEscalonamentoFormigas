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

using namespace std;

Principal::Principal() {
    srand (time(NULL));
    this->qntTarefas = 0;
    this->numColArestas = 0;
    this->numLinhasArestas = 0;
    this->numColMatrizFeromonio = 0;
    this->numLinhasMatrizFeromonio = 0;
}

Principal::Principal(const Principal& orig) {
}

Principal::~Principal() {
    desalocarEstruturas();
    this->qntTarefas = 0;
    this->numColArestas = 0;
    this->numLinhasArestas = 0;
    this->numColMatrizFeromonio = 0;
    this->numLinhasMatrizFeromonio = 0;
}

void Principal:: setTempoSetup(int *arestas){
    this->arestasSetup = arestas;
}

void Principal:: setMatrizFeromonio(int **matriz){
    this->matrizFeromonio = matriz;
}

void Principal:: setNumColArestas(int numColArestas){
    this->numColArestas = numColArestas;
}

void Principal:: setNumLinhasArestas(int numLinhasArestas){
    this->numLinhasArestas = numLinhasArestas;
}

void Principal:: setNumColMatrizFeromonio(int numColMatrizFeromonio){
    this->numColMatrizFeromonio = numColMatrizFeromonio;
}

void Principal:: setNumLinhasMatrizFeromonio(int numLinhasMatrizFeromonio){
    this->numLinhasMatrizFeromonio = numLinhasMatrizFeromonio;
}

void Principal:: setGrafo(Tarefa *grafo){
    this->grafo = grafo;
}

void Principal:: setQntTarefas(int qntTarefas){
    this->qntTarefas =qntTarefas;
}
    
int* Principal:: getTempoSetup(){
    return this->arestasSetup;
}

int** Principal:: getMatrizFeromonio(){
    return this->matrizFeromonio;
}

int Principal:: getNumColArestas(){
    return this->numColArestas;
}

int Principal:: getNumLinhasArestas(){
    return this->numLinhasArestas;
}

int Principal::getNumColMatrizFeromonio(){
    return this->numColMatrizFeromonio;
}

int Principal:: getNumLinhasMatrizFeromonio(){
    return this->numLinhasMatrizFeromonio;
}

Tarefa* Principal:: getGrafo(){
    return this->grafo;
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
    }
}

/**
 *  Executa o procedimento principal do algoritmo.
 */
void Principal::executar(){
    int qntTarefas = 5;
    int qntMaquinas = 3;
    bool notEnd = false;
    
    criarGrafo(qntTarefas,qntMaquinas);
    inicializarMatrizFeromonio(qntTarefas);   
    
//    imprimirMatrizFeromonio();
//    imprimirGrafo();
    
//    while(!notEnd){
//        
//    }
}

/**
 *  Cria o grafo completo com as tarefas, em que cada posição do vetor 
 * possui todas as tarefas, menos a tarefa indice do vetor.
 */
void Principal :: criarGrafo(int qntTarefas, int qntMaquinas){
    this->qntTarefas = qntTarefas;
    this->grafo = new Tarefa[this->qntTarefas];
    
    for(int index = 0; index < this->qntTarefas; index++){
        this->grafo[index].setIndice(index);
        this->grafo[index].inicializarVetorTempoExecucaoTeste(getRandomNumero(100,1),qntMaquinas);
    }
    for(int index = 0; index < this->qntTarefas; index++){
        Tarefa *tarefa = &(this->grafo[index]);    
        
        for(int i = 0; i < this->qntTarefas; i++){
            if(i != index){
                tarefa->setProxima(new Tarefa(i));
                tarefa = tarefa->getProxima();
                tarefa->inicializarVetorTempoExecucaoTeste(this->grafo[i].getTempoExecucaoMaquina()[0], qntMaquinas);
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
    desalocarMatriz(this->arestasSetup,this->numLinhasArestas,this->numColArestas);
    desalocarMatriz(this->matrizFeromonio,this->numLinhasMatrizFeromonio,this->numColMatrizFeromonio);
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
    cout << "Não implementado ainda !" << endl;
}

/**
 * 
 */
void Principal :: desalocarMatriz(int **matriz, int linhas, int colunas){
    cout << "Não implementado ainda !" << endl;
}

/**
 * 
 */
int Principal :: getRandomNumero(int range, int limSup){
    return (rand() % range + limSup);
}