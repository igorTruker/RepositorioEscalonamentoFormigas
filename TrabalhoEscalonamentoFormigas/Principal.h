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
    
    void setTempoSetup(int *arestas);
    void setMatrizFeromonio(int **matriz);
    void setNumColArestas(int numColArestas);
    void setNumLinhasArestas(int numLinhasArestas);
    void setNumColMatrizFeromonio(int numColMatrizFeromonio);
    void setNumLinhasMatrizFeromonio(int numLinhasMatrizFeromonio);
    void setGrafo(Tarefa *grafo);
    void setQntTarefas(int qntTarefas);
    
    int* getTempoSetup();
    int** getMatrizFeromonio();
    int getNumColArestas();
    int getNumLinhasArestas();
    int getNumColMatrizFeromonio();
    int getNumLinhasMatrizFeromonio();
    Tarefa* getGrafo();
    int getQntTarefas();
    
    void inicializarMatrizFeromonio(int qntTarefas);
    
    void executar();
    void criarGrafo(int qntTarefas, int qntMaquinas);
    Formiga* criarFormiga(int qntFormigas,int qntTarefas);
    
    void imprimirGrafo();
    void imprimirMatrizFeromonio();
    
    void desalocarEstruturas();
    Tarefa* desalocarNos(Tarefa *no);
    void desalocarMatriz(int *matriz, int linhas, int colunas);
    void desalocarMatriz(int **matriz, int linhas, int colunas);
    
    int getRandomNumero(int range, int limSup);
    
private:
    int *arestasSetup;                 // possui os tempos de setup entre as tarefas
    int **matrizFeromonio;
    Tarefa *grafo;
    int qntTarefas;
    int numColArestas;
    int numLinhasArestas;
    int numColMatrizFeromonio;
    int numLinhasMatrizFeromonio;
};

#endif /* PRINCIPAL_H */

