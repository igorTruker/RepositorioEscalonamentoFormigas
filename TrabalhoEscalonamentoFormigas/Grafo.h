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
    
    void imprimirGrafo();
    
private:
    Tarefa **grafo;
    int tamanho;
    
    Tarefa* eliminarTarefa(Tarefa *tarefa);
};

#endif /* GRAFO_H */

