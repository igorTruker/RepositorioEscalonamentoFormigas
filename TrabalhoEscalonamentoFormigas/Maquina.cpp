/* 
 * File:   Maquina.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 12:22
 */

#include "Maquina.h"

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