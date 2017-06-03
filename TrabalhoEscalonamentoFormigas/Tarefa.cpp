/* 
 * File:   Tarefa.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 12:22
 */

#include "Tarefa.h"

Tarefa::Tarefa() {
}

Tarefa::Tarefa(const Tarefa& orig) {
}

Tarefa::~Tarefa() {
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