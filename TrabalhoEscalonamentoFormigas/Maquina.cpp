/* 
 * File:   Maquina.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 12:22
 */

#include <iostream>
#include "Maquina.h"
#include "Grafo.h"

using namespace std;

Maquina::Maquina() {
    this->tarefas = NULL;
}

Maquina::Maquina(const Maquina& orig) {
}

Maquina::~Maquina() {
//    if(this->tarefas != NULL){
//        if(this->tarefas->getProxima() != NULL){
//            this->tarefas->setProxima( removerTarefas( this->tarefas->getProxima()));
//        }
//        delete this->tarefas;
//    }
}

void Maquina:: setTarefas(Tarefa *tarefas){
    this->tarefas = tarefas;
}

Tarefa* Maquina:: getTarefas(){
    return this->tarefas;
}

/*
 * Retira uma tarefa da lista encadeada e adiciona na lista de tarefas.
 */
//void Maquina::adicionarTarefaLista(Tarefa* tarefaAnterior, Tarefa* tarefaEscolhida) {
//    if(tarefaAnterior == NULL){
//        Tarefa *t = clonarTarefa(tarefaEscolhida);
//        adicionarTarefa(t);
//    }else{
//        tarefaAnterior->setProxima(tarefaEscolhida->getProxima());
//        tarefaEscolhida->setProxima(NULL);
//        adicionarTarefa(tarefaEscolhida);
//    }
//}

/*
 * Adiciona uma tarefa de tempo avulso na lista.
 */
//void Maquina::adicionarTarefaAvulsa() {
//    Tarefa *t = new Tarefa();
//    t->setIndice(-1);
//    adicionarTarefa(t);
//}

/*
 * Adiciona uma tarefa na lista.
// */
//void Maquina::adicionarTarefa(Tarefa* tarefa) {
//    if(this->tarefas == NULL){
//        this->tarefas = tarefa;
//    }else{
//        Tarefa *t = this->tarefas;
//        while(t->getProxima() != NULL){
//            t = t->getProxima();
//        }
//        t->setProxima(tarefa);
//        t->getProxima()->setAnterior(t);
//    }
//}

/*
 * Adiciona uma tarefa na lista.
 */
void Maquina::adicionarTarefaUltima(Tarefa* tarefa, int indiceMaquina, int **matrizTempoTarefa,int ***arestasSetup){
    if(this->tarefas == NULL){
        this->tarefas = tarefa;
        this->tarefas->setTempoInicio(0);
        this->tarefas->setTempoTermino(matrizTempoTarefa[tarefa->getIndice()][indiceMaquina]);
//        cout << "indice : " << tarefa->getIndice() << " Maq : " << indiceMaquina << " Tempo : " << matrizTempoTarefa[tarefa->getIndice()][indiceMaquina] << endl;
    }else{
        Tarefa *t = this->tarefas;
        t->setAnterior(tarefa);
        tarefa->setProxima(t);
        this->tarefas = tarefa;
        tarefa->setAnterior(NULL);
        
        tarefa->setTempoInicio( tarefa->getProxima()->getTempoTermino());
        tarefa->setTempoTermino( tarefa->getTempoInicio() + matrizTempoTarefa[tarefa->getIndice()][indiceMaquina] 
            + arestasSetup[tarefa->getProxima()->getIndice()][tarefa->getIndice()][indiceMaquina]);
    }
}

/*
 * Clona uma tarefa passada no parâmetro.
 */
Tarefa* Maquina::clonarTarefa(Tarefa* tarefa) {
    Tarefa *t = new Tarefa();
    t->setIndice(tarefa->getIndice());
    t->setProxima(NULL);
    return t;
}

void Maquina::escolherMelhorCaminho(Grafo* grafo, int indiceMaquina, int indiceVetor, int ***matrizFeromonio) {
    Tarefa *t = grafo->getListaTarefaTotal(indiceVetor);
    int indiceAtual = t->getIndice();
    
    while(t->getProxima() != NULL){
        t = t->getProxima();
        
        int indiceProximo = t->getIndice();
//        matrizFeromonio[indiceMaquina][indiceAtual][indiceProximo] 
    }
}

void Maquina::imprimirDados() {
    Tarefa *tarefa = this->tarefas;
    
    if(tarefa != NULL){
        cout << "Tarefa : " << tarefa->getIndice() << " ( " << tarefa->getTempoInicio() << " , " << tarefa->getTempoTermino() << " ) -> ";
        while(tarefa->getProxima() != NULL){
            tarefa = tarefa->getProxima();
            cout << tarefa->getIndice() << " ( " << tarefa->getTempoInicio() << " , " << tarefa->getTempoTermino() << " ) -> ";
        }
    }
}

Tarefa* Maquina::removerTarefas(Tarefa* tarefa) {
    while(tarefa->getProxima() != NULL){
        tarefa->setProxima( removerTarefas( tarefa->getProxima()));
    }
    delete tarefa;
    return NULL;
}