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
            this->arquivo << "\n Funcao Obj : " << solucao->getFuncaoObj() << "\n\n";
            this->arquivo << " Tarefas : \n";
            for(int index = 0; index < solucao->getTamanho(); index++){
                Tarefa *tarefa = solucao->getListaTarefaProxima(index);
                
                this->arquivo << "Maq : " << index << " -> ";
                if(tarefa != NULL){
                    this->arquivo << tarefa->getIndice() << " ( " << tarefa->getTempoInicio() << "," << tarefa->getTempoTermino() << ") # ";
                    while(tarefa->getProxima() != NULL){
                        tarefa = tarefa->getProxima();
                        this->arquivo << tarefa->getIndice() << " ( " << tarefa->getTempoInicio() << "," << tarefa->getTempoTermino() << ") # ";
                    }
                }
                this->arquivo << "\n";
            }
        }
    }
}

void EscreverDados::escreverFeromonio(double*** matriz,int qntTarefas,int qntMaquinas) {
    this->arquivo << "\n\n Matriz Feromonio : \n\n";
    for(int index = 0; index < qntMaquinas; index++){
        for(int indexJ = 0; indexJ < qntTarefas; indexJ++){
            for(int indexI = 0; indexI < qntTarefas; indexI++){
                this->arquivo << " " << matriz[index][indexJ][indexI];
            }
            this->arquivo << "\n";
        }
        this->arquivo << "\n\n";
    }
}
