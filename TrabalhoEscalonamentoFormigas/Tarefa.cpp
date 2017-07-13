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
    this->anterior = NULL;
    this->selecionada = false;
}

Tarefa::Tarefa(int indice) {
    this->indice = indice;
    this->proxima = NULL;
    this->anterior = NULL;
    this->selecionada = false;
}

Tarefa::~Tarefa() {
    this->proxima = NULL;
    this->anterior = NULL;
//    cout << "Tarefa Deletada !" << endl;
}

void Tarefa:: setProxima(Tarefa *proxima){
    this->proxima = proxima;
}

void Tarefa::setAnterior(Tarefa* anterior) {
    this->anterior = anterior;
}

void Tarefa:: setIndice(int indice){
    this->indice = indice;
}

void Tarefa::setSelecionada(bool selecionada) {
    this->selecionada = selecionada;
}

void Tarefa::setTempoInicio(int tempoInicio) {
    this->tempoInicio = tempoInicio;
}

void Tarefa::setTempoTermino(int tempoTermino) {
    this->tempoTermino = tempoTermino;
}

Tarefa* Tarefa:: getProxima(){
    return this->proxima;
}

Tarefa* Tarefa::getAnterior() {
    return this->anterior;
}

int Tarefa:: getIndice(){
    return this->indice;
}

bool Tarefa::getSelecionada() {
    return this->selecionada;
}

int Tarefa::getTempoInicio() {
    return this->tempoInicio;
}

int Tarefa::getTempoTermino() {
    return this->tempoTermino;
}

/**
 *  Imprime os dados da formiga.
 */
void Tarefa::imprimir() {
    cout << "Indice : " << this->indice << endl;
}
