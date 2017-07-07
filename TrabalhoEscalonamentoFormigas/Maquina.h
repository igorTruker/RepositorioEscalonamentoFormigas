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
    
    void setTarefas(Tarefa *tarefas);
    Tarefa* getTarefas();
    
    void adicionarTarefaLista(Tarefa *tarefaAnterior, Tarefa *tarefaEscolhida);
    void adicionarTarefaAvulsa();
    void adicionarTarefa(Tarefa *tarefa);
    Tarefa* clonarTarefa(Tarefa *tarefa);
    
    void imprimirDados();
    
    
private:
    Tarefa *tarefas;
    
    Tarefa* removerTarefas(Tarefa *tarefa);
};

#endif /* MAQUINA_H */

