/* 
 * File:   Grafo.cpp
 * Author: igor
 * 
 * Created on 3 de Julho de 2017, 16:02
 */

#include "Grafo.h"
#include "Tarefa.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Grafo::Grafo() {
    this->grafo = NULL;
    this->tamanho = 0;
    this->funcaoObj = 0;
}

Grafo::Grafo(int tamanho) {
    this->grafo = NULL;
    this->tamanho = tamanho;
    this->funcaoObj = 0;
}

Grafo::Grafo(const Grafo& orig) {
}

Grafo::~Grafo() {
    finalizarGrafo();
    delete [] this->grafo;
}

void Grafo::criarGrafoCompleto(int tamanho) {
    this->grafo = new Tarefa*[tamanho];
    this->tamanho = tamanho;
    
    for(int index = 0; index < tamanho; index++){
        this->grafo[index] = new Tarefa(index);        
        Tarefa *tarefa = this->grafo[index];    
        
        for(int indice = 0; indice < tamanho; indice++){
            if(indice != index){
                tarefa->setProxima(new Tarefa(indice));
                tarefa->getProxima()->setAnterior(tarefa);
                tarefa = tarefa->getProxima();
            }
        }
    }
}

Tarefa* Grafo::removerTarefa(int indiceVetor,int indiceTarefa) {
    Tarefa *tarefa = this->grafo[indiceVetor];
    
    while(tarefa->getIndice() != indiceTarefa){
        tarefa = tarefa->getProxima();
    }
    tarefa->setSelecionada(true);
    this->grafo[indiceVetor]->setSelecionada(true);
    this->grafo[indiceTarefa]->setSelecionada(true);
    return new Tarefa(indiceTarefa);
}

void Grafo::finalizarGrafo() {
    for(int index = 0; index < tamanho; index++){
        this->grafo[index]->setProxima( eliminarTarefa(this->grafo[index]->getProxima()) );
    }
    
}

Tarefa* Grafo::eliminarTarefa(Tarefa* tarefa) {
    if(tarefa->getProxima() != NULL){
        tarefa->setProxima(eliminarTarefa(tarefa->getProxima()));
    }
    delete tarefa;
    return NULL;
}

/**
 *  Imprime o grafo com suas tarefas alocadas.
 */
void Grafo::imprimirGrafo(){   
    for(int index = 0; index < this->tamanho; index++){
        Tarefa *tarefa = this->grafo[index];
        
        cout << "Origem | " << this->grafo[index]->getIndice() << ":: S=" << this->grafo[index]->getSelecionada() << " | -> ";
        
        while(tarefa->getProxima() != NULL){
            tarefa = tarefa->getProxima();
            cout << " # " <<  tarefa->getIndice() << " # -> ";
//                    << " S=" << tarefa->getSelecionada() << " # -> ";
        }
        cout << endl;
    }
}

int Grafo::getNumTarefasMarcadas() {
    int marcadas = 0;
    for(int index = 0; index < this->tamanho; index++){
        if(this->grafo[index]->getSelecionada() == true){
            marcadas += 1;
        }
    }
    return marcadas;
}

int Grafo::getIndiceEnesimaTarefaNaoMarcada(int n) {
    int indice = -1;
    
    if(n >= 0){
        int index = 0;
        while(n > 0 && index < this->tamanho){
            if(this->grafo[index]->getSelecionada() == false){
                indice = this->grafo[index]->getIndice();
            }
            index += 1;
        }
    }
    return indice;
}

void Grafo::resetarSelecaoGrafo() {
    for(int index = 0; index < tamanho; index++){
        Tarefa *tarefa = this->grafo[index];
        
        while(tarefa->getProxima() != NULL){
            tarefa->setSelecionada(false);
            tarefa = tarefa->getProxima();
        }
        tarefa->setSelecionada(false);
    }
}

void Grafo::imprimirVetor() {
    for(int index = 0; index < tamanho; index++){
        cout << " Indice : " << this->grafo[index]->getIndice() << " Marcada: " << this->grafo[index]->getSelecionada() << endl;
    }
}


// MAQUINA
void Grafo::criarGrafoVetor(int tamanho) {
    Tarefa **a = new Tarefa*[tamanho];
//    this->grafo = new Tarefa*[tamanho];
    this->grafo = a;
    this->tamanho = tamanho;
    
    for(int index = 0; index < tamanho; index++){
        this->grafo[index] = new Tarefa(index);        
    }
}

// MAQUINA
void Grafo::setListaSolucao(Tarefa* lista, int indiceVetor) {
    this->grafo[indiceVetor]->setProxima(lista);
}

// MAQUINA
void Grafo::calcularFuncaoObj(int *dataEntrega, int *alfa, int *beta) {
    int penalidade = 0;
    int diferenca = 0;
    
    for(int indice = 0; indice < this->tamanho; indice++){
        Tarefa *t = this->grafo[indice];
        
        while(t->getProxima() != NULL){
            diferenca = dataEntrega[t->getIndice()] - t->getTempoTermino();
            
            if(diferenca > 0){
                penalidade += diferenca * alfa[t->getIndice()];
            }else{
                penalidade += (abs(diferenca))*beta[t->getIndice()];
            }
            t = t->getProxima();
        }
    }
    this->funcaoObj = penalidade;
}

// MAQUINA
int Grafo::getFuncaoObj() {
    return this->funcaoObj;
}

// MAQUINA
void Grafo::setFuncaoObj(int funcaoObj) {
    this->funcaoObj = funcaoObj;
}

bool Grafo::estaVazio() {
    for(int indice = 0; indice < this->tamanho; indice++){
        if(this->grafo[indice]->getProxima() != NULL){
            return false;
        }
    }
    return true;
}

Tarefa* Grafo::getListaTarefa(int indiceVetor) {
    return this->grafo[indiceVetor]->getProxima();
}

Tarefa* Grafo::getListaTarefaTotal(int indiceVetor) {
    return this->grafo[indiceVetor];
}

void Grafo::transferirTarefas(Grafo* grafo) {
    for(int indice = 0; indice < this->tamanho; indice++){
        this->grafo[indice]->setProxima( grafo->getListaTarefa(indice) );
        grafo->setListaSolucao(NULL,indice);
    }
}

bool Grafo::ehViavel() {
    for(int index = 0; index < tamanho; index++){
        if(this->grafo[index]->getSelecionada() == false){
            return false;
        }
    }
    return true;
}
