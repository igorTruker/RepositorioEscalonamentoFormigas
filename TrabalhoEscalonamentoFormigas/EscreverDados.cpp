/* 
 * File:   EscreverDados.cpp
 * Author: igor
 * 
 * Created on 4 de Junho de 2017, 19:29
 */

#include "EscreverDados.h"

EscreverDados::EscreverDados() {
}

EscreverDados::EscreverDados(const EscreverDados& orig) {
}

EscreverDados::~EscreverDados() {
}

void EscreverDados::abrirArquivo(string arquivo) {
    this->arquivo.open(arquivo.c_str());
}

void EscreverDados::escreverDados(string dados) {
    this->arquivo << dados << "\n";
}

void EscreverDados::fecharArquivo() {
    this->arquivo.close();
}

void EscreverDados::escreverDadosSol(EstruturaSolucao* solucao) {
    if(solucao != NULL){      
        if (this->arquivo.is_open()){
            this->arquivo << " Funcao Obj : " << solucao->getFuncaoObj() << "\n";
            this->arquivo << " Tarefas : \n";
            for(int index = 0; index < solucao->getTamanho(); index++){
                Tarefa *tarefa = solucao->getListaTarefaProxima(index);
                
                this->arquivo << "Maq : " << index << " -> ";
                while((tarefa != NULL)&&(tarefa->getProxima() != NULL)){
                    this->arquivo << tarefa->getIndice() << " ( " << tarefa->getTempoInicio() << "," << tarefa->getTempoTermino() << ") # ";
                    tarefa = tarefa->getProxima();
                }
                this->arquivo << "\n";
            }
        }
    }
}