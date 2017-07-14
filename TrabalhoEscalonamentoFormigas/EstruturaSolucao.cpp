/* 
 * File:   EstruturaSolucao.cpp
 * Author: igor
 * 
 * Created on 13 de Julho de 2017, 11:50
 */

#include "EstruturaSolucao.h"
#include <iostream>
#include <stdlib.h>

EstruturaSolucao::EstruturaSolucao() {
}

EstruturaSolucao::EstruturaSolucao(int tamanho) {
    this->setTamanho(tamanho);
}

EstruturaSolucao::~EstruturaSolucao() {
}

// MAQUINA
void EstruturaSolucao::criarGrafoVetor(int tamanhoMaquina) {
    Tarefa **a = new Tarefa*[tamanhoMaquina];
    this->setGrafo(a);
    this->setTamanho(tamanhoMaquina);
    
    for(int index = 0; index < tamanhoMaquina; index++){
        this->getGrafo()[index] = new Tarefa(index);        
    }
}

// MAQUINA
void EstruturaSolucao::setListaSolucao(Tarefa* lista, int indiceVetor) {
    this->getGrafo()[indiceVetor]->setProxima(lista);
}

// MAQUINA
void EstruturaSolucao::calcularFuncaoObj(int *dataEntrega, int *alfa, int *beta) {
    int penalidade = 0;
    int diferenca = 0;
    
//    this->imprimirGrafo();
    
    for(int indice = 0; indice < this->getTamanho(); indice++){
        Tarefa *t = this->getGrafo()[indice]->getProxima();
        
        while((t != NULL)&&(t->getProxima() != NULL)){
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
int EstruturaSolucao::getFuncaoObj() {
    return this->funcaoObj;
}

// MAQUINA
void EstruturaSolucao::setFuncaoObj(int funcaoObj) {
    this->funcaoObj = funcaoObj;
}

void EstruturaSolucao::transferirTarefas(EstruturaSolucao* solucao) {
    for(int indice = 0; indice < solucao->getTamanho(); indice++){
        this->getGrafo()[indice]->setProxima( solucao->getListaTarefaProxima(indice) );
        solucao->setListaSolucao(NULL,indice);
    }
}