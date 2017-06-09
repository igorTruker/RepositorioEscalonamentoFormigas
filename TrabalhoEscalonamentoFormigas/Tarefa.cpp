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
    this->proxima = NULL;
}

Tarefa::Tarefa(int indice) {
    this->indice = indice;
    this->proxima = NULL;
}

Tarefa::~Tarefa() {
    this->proxima = NULL;
    cout << "Tarefa Deletada !" << endl;
}

void Tarefa:: setProxima(Tarefa *proxima){
    this->proxima = proxima;
}

void Tarefa:: setIndice(int indice){
    this->indice = indice;
}

Tarefa* Tarefa:: getProxima(){
    return this->proxima;
}

int Tarefa:: getIndice(){
    return this->indice;
}

/**
 *  Imprime os dados da formiga.
 */
void Tarefa::imprimir() {
    cout << "Indice : " << this->indice << endl;
}
