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
    
    void setDataEntrega(int dataEntrega);
    void setPenalizacaoAtraso(int penalizacaoAtraso);
    void setPenalizacaoAdiantamento(int penalizacaoAdiantamento);
    void setTempoExecucaoMaquina(int *tempoExecucaoMaquina);
    void setProxima(Tarefa *proxima);
    void setIndice(int indice);
    
    int getDataEntrega();
    int getPenalizacaoAtraso();
    int getPenalizacaoAdiantamento();
    int* getTempoExecucaoMaquina();
    Tarefa* getProxima();
    int getIndice();
    
    void inicializarVetorTempoExecucaoTeste(int valor,int qntMaquinas);
    void imprimirDados();
    
private:
    int indice;
    int dataEntrega;
    int penalizacaoAtraso;
    int penalizacaoAdiantamento;
    int *tempoExecucaoMaquina;        // diferente para cada máquina
    Tarefa *proxima;
};

#endif /* TAREFA_H */

