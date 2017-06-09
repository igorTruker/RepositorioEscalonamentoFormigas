/* 
 * File:   Tarefa.h
 * Author: igor
 *
 * Created on 3 de Junho de 2017, 12:22
 */

#ifndef TAREFA_H
#define TAREFA_H

class Tarefa {
    
public:
    Tarefa();
    Tarefa(int indice);
    virtual ~Tarefa();
    
    void setProxima(Tarefa *proxima);
    void setIndice(int indice);
    
    Tarefa* getProxima();
    int getIndice();
    
    void inicializarVetorTempoExecucaoTeste(int valor,int qntMaquinas);
    void imprimir();
    
private:
    int indice;
    Tarefa *proxima;
};

#endif /* TAREFA_H */

