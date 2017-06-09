/* 
 * File:   Tarefa.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 12:22
 */

#include <iostream>
#include "Tarefa.h"

using namespace std;

Tarefa::Tarefa() {
    this->indice = 0;
    this->dataEntrega = 0;
    this->penalizacaoAtraso = 0;
    this->penalizacaoAdiantamento = 0;
    this->tempoExecucaoMaquina = NULL;
    this->proxima = NULL;
}

Tarefa::Tarefa(int indice) {
    this->indice = indice;
    this->dataEntrega = 0;
    this->penalizacaoAtraso = 0;
    this->penalizacaoAdiantamento = 0;
    this->tempoExecucaoMaquina = NULL;
    this->proxima = NULL;
}

Tarefa::~Tarefa() {
    this->dataEntrega = 0;
    this->penalizacaoAtraso = 0;
    this->penalizacaoAdiantamento = 0;
    this->tempoExecucaoMaquina = NULL;
    this->proxima = NULL;
    cout << "Tarefa Deletada !" << endl;
}

void Tarefa:: setDataEntrega(int dataEntrega){
    this->dataEntrega = dataEntrega;
}

void Tarefa:: setPenalizacaoAtraso(int penalizacaoAtraso){
    this->penalizacaoAtraso = penalizacaoAtraso;
}

void Tarefa:: setPenalizacaoAdiantamento(int penalizacaoAdiantamento){
    this->penalizacaoAdiantamento = penalizacaoAdiantamento;
}

void Tarefa:: setTempoExecucaoMaquina(int *tempoExecucaoMaquina){
    this->tempoExecucaoMaquina = tempoExecucaoMaquina;
}

void Tarefa:: setProxima(Tarefa *proxima){
    this->proxima = proxima;
}

void Tarefa:: setIndice(int indice){
    this->indice = indice;
}
    
int Tarefa:: getDataEntrega(){
    return this->dataEntrega;
}

int Tarefa:: getPenalizacaoAtraso(){
    return this->penalizacaoAtraso;
}

int Tarefa:: getPenalizacaoAdiantamento(){
    return this->penalizacaoAdiantamento;
}

int* Tarefa:: getTempoExecucaoMaquina(){
    return this->tempoExecucaoMaquina;
}

Tarefa* Tarefa:: getProxima(){
    return this->proxima;
}

int Tarefa:: getIndice(){
    return this->indice;
}

/**
 *  Apagar depois.
 * @param valor
 * @param qntMaquinas
 */
void Tarefa::inicializarVetorTempoExecucaoTeste(int valor, int qntMaquinas) {
    this->tempoExecucaoMaquina =  new int[qntMaquinas];
    
    for(int index = 0; index < qntMaquinas; index++){
        this->tempoExecucaoMaquina[index] = qntMaquinas;
    }
}

/**
 *  Imprime os dados da formiga.
 */
void Tarefa::imprimirDados() {
    cout << "Indice : " << this->indice << endl;
    cout << "Data de entrega : " << this->dataEntrega << endl;
    cout << "Penalizacao Adiantamento : " << this->penalizacaoAdiantamento << endl;
    cout << "Penalizacao Atraso : " << this->penalizacaoAtraso << endl;
    
    cout << "Tempo Execução Maquina : ";
    for(int index = 0; index < (sizeof(this->tempoExecucaoMaquina)/sizeof(this->tempoExecucaoMaquina[0])); index++){
        cout << this->tempoExecucaoMaquina[index] << " ";
    }
    cout << endl;
}
