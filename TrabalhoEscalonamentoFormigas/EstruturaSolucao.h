/* 
 * File:   EstruturaSolucao.h
 * Author: igor
 *
 * Created on 13 de Julho de 2017, 11:50
 */

#ifndef ESTRUTURASOLUCAO_H
#define ESTRUTURASOLUCAO_H

#include "Grafo.h"

class EstruturaSolucao : public Grafo {
public:
    EstruturaSolucao();
    EstruturaSolucao(int tamanho);
    EstruturaSolucao(const EstruturaSolucao& orig);
    virtual ~EstruturaSolucao();
    
    void criarGrafoVetor(int tamanhoMaquina);
    void calcularFuncaoObj(int *dataEntrega, int *alfa, int *beta);
    
    void setListaSolucao(Tarefa *lista, int indiceVetor);
    void setFuncaoObj(int funcaoObj);
    int getFuncaoObj();
    
    void transferirTarefas(EstruturaSolucao* solucao);
    
private:
    int funcaoObj;
};

#endif /* ESTRUTURASOLUCAO_H */

