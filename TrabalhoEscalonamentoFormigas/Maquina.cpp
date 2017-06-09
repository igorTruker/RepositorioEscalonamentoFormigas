/* 
 * File:   Maquina.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 12:22
 */

#include <iostream>
#include "Maquina.h"

using namespace std;

Maquina::Maquina() {
}

Maquina::Maquina(const Maquina& orig) {
}

Maquina::~Maquina() {
}

void Maquina:: setCustoPoluicao(int custoPoluicao){
    this->custoPoluicao = custoPoluicao;
}

void Maquina:: setTarefas(Tarefa *tarefas){
    this->tarefas = tarefas;
}

int Maquina:: getCustoPoluicao(){
    return this->custoPoluicao;
}

Tarefa* Maquina:: getTarefas(){
    return this->tarefas;
}

void Maquina::criarTarefasCaminho(int qntTarefas) {
    this->tarefas = new Tarefa[qntTarefas];
    
    for(int index = 0; index < qntTarefas; index++){
        this->tarefas[index] = 0;
    }
}

void Maquina::imprimirDados() {
    cout << "Custo poluicao : " << this->custoPoluicao << endl;
    
    for(int index = 0; index < (sizeof(this->tarefas)/sizeof(this->tarefas[0])); index++){
        this->tarefas[index].imprimirDados();
    }
}
