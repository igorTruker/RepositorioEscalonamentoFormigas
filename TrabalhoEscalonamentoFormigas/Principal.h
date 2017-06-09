/* 
 * File:   Principal.h
 * Author: igor
 *
 * Created on 3 de Junho de 2017, 13:35
 */

#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "Formiga.h"
#include "Tarefa.h"

class Principal {
    
public:
    Principal();
    Principal(const Principal& orig);
    virtual ~Principal();
    
    void setTempoSetup(int ***arestas);
    void setMatrizFeromonio(int **matriz);
    void setGrafo(Tarefa *grafo);
    void setQntMaquinas(int qntMaquinas);
    void setQntTarefas(int qntTarefas);
    void setLimPoluicao(int poluicao);
    void setCustoMaquina(int *custoMaquina);
    void setDataEntrega(int *dataEntrega);
    void setAlfa(int *alfa);
    void setBeta(int *beta);
    void setMatrizTarefas(int **matrizTarefas);
    
    int*** getTempoSetup();
    int** getMatrizFeromonio();
    Tarefa* getGrafo();
    int getQntTarefas();
    int getQntMaquinas();
    int getLimPoluicao();
    int* getCustoMaquina();
    int* getDataEntrega();
    int* getAlfa();
    int* getBeta();
    int** getMatrizTarefas();
    
    void inicializarMatrizFeromonio(int qntTarefas);
    void inicializarEstruturas();
    
    void executar();
    void criarGrafo(int qntTarefas, int qntMaquinas);
    Formiga* criarFormiga(int qntFormigas,int qntTarefas);
    
    void imprimirGrafo();
    void imprimirMatrizFeromonio();
    void imprimirDados();
    
    void desalocarEstruturas();
    Tarefa* desalocarNos(Tarefa *no);
    void desalocarMatriz(int *matriz, int linhas, int colunas);
    void desalocarMatriz(int **matriz, int linhas, int colunas);
    void desalocarMatriz(int ***matriz, int linhas, int colunas);
    
    int getRandomNumero(int range, int limSup);
    
private:
    int ***arestasSetup;                 // possui os tempos de setup entre as tarefas   TAMANHO (TAREFA X TAREFA)
    int **matrizFeromonio;             // TAMANHO (TAREFA X TAREFA)
    int **matrizTarefas;
    Tarefa *grafo;                      // QNT TAREFAS
    int qntTarefas;
    int qntMaquinas;
    int limitePoluicao;
    int *custoMaquina;
    int *dataEntrega;
    int *alfa;
    int *beta;
    
};

#endif /* PRINCIPAL_H */

