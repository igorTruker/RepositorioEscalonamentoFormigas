/* 
 * File:   Grafo.h
 * Author: igor
 *
 * Created on 3 de Julho de 2017, 16:02
 */

#ifndef GRAFO_H
#define GRAFO_H

#include "Tarefa.h"

class Grafo {
public:
    Grafo();
    Grafo(int tamanho);
    Grafo(const Grafo& orig);
    virtual ~Grafo();
    
    void criarGrafoCompleto(int tamanho);
    Tarefa* removerTarefa(int indiceVet,int indiceTar);
    void finalizarGrafo();
    void resetarSelecaoGrafo();
    
    int getNumTarefasMarcadas();
    int getIndiceEnesimaTarefaNaoMarcada(int n);
    int getFuncaoObj();
    Tarefa* getListaTarefa(int indiceVetor);
    Tarefa* getListaTarefaTotal(int indiceVetor);
    
    void criarGrafoVetor(int tamanho);
    void setListaSolucao(Tarefa *lista, int indiceVetor);
    void setFuncaoObj(int funcaoObj);
    void calcularFuncaoObj(int *dataEntrega, int *alfa, int *beta);
    
    bool estaVazio();
    bool ehViavel();
    void transferirTarefas(Grafo *grafo);
    
    void imprimirGrafo();
    void imprimirVetor();
    
private:
    Tarefa **grafo;
    int tamanho;
    int funcaoObj;
    
    Tarefa* eliminarTarefa(Tarefa *tarefa);
};

#endif /* GRAFO_H */

