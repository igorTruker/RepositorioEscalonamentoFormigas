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
    
    int getNumTarefasMarcadas();
    int getIndiceEnesimaTarefaNaoMarcada(int n);
    Tarefa* getListaTarefaProxima(int indiceVetor);
    Tarefa* getListaTarefaTotal(int indiceVetor);
    
    int getTamanho();
    Tarefa** getGrafo();
    
    void setGrafo(Tarefa **grafo);
    void setTamanho(int tamanho);
        
    bool estaVazio();
    bool ehViavel();
    
    void finalizarGrafo();
    void resetarSelecaoGrafo();
    
    void imprimirGrafo();
    void imprimirVetor();
    
private:
    Tarefa **grafo;
    int tamanho;
    
    Tarefa* eliminarTarefa(Tarefa *tarefa);
};

#endif /* GRAFO_H */

