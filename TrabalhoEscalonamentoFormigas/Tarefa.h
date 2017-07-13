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
    void setAnterior(Tarefa *anterior);
    void setIndice(int indice);
    void setSelecionada(bool selecionada);
    void setTempoInicio(int tempoInicio);
    void setTempoTermino(int tempoTermino);
    
    Tarefa* getProxima();
    Tarefa* getAnterior();
    int getIndice();
    bool getSelecionada();
    int getTempoInicio();
    int getTempoTermino();
    
    
    void inicializarVetorTempoExecucaoTeste(int valor,int qntMaquinas);
    void imprimir();
    
private:
    int indice;
    bool selecionada;
    Tarefa *proxima;
    Tarefa *anterior;
    int tempoInicio;
    int tempoTermino;
};

#endif /* TAREFA_H */

