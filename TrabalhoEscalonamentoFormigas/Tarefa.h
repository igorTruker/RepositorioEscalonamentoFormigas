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
    Tarefa(const Tarefa& orig);
    virtual ~Tarefa();
    
    void setDataEntrega(int dataEntrega);
    void setPenalizacaoAtraso(int penalizacaoAtraso);
    void setPenalizacaoAdiantamento(int penalizacaoAdiantamento);
    void setTempoExecucaoMaquina(int *tempoExecucaoMaquina);
    
    int getDataEntrega();
    int getPenalizacaoAtraso();
    int getPenalizacaoAdiantamento();
    int* getTempoExecucaoMaquina();
    
private:
    int dataEntrega;
    int penalizacaoAtraso;
    int penalizacaoAdiantamento;
    int *tempoExecucaoMaquina;        // diferente para cada máquina
};

#endif /* TAREFA_H */

