/* 
 * File:   Maquina.h
 * Author: igor
 *
 * Created on 3 de Junho de 2017, 12:22
 */

#ifndef MAQUINA_H
#define MAQUINA_H

#include "Tarefa.h"

class Maquina {
    
public:
    Maquina();
    Maquina(const Maquina& orig);
    virtual ~Maquina();
    
    void setCustoPoluicao(int custoPoluicao);
    void setTarefas(Tarefa *tarefas);
    
    int getCustoPoluicao();
    Tarefa* getTarefas();
    
private:
    int custoPoluicao;
    Tarefa *tarefas;
};

#endif /* MAQUINA_H */

