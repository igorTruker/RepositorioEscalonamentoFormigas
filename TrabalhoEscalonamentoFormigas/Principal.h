/* 
 * File:   Principal.h
 * Author: igor
 *
 * Created on 3 de Junho de 2017, 13:35
 */

#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <stdlib.h>
#include <time.h>
#include "Formiga.h"
#include "Tarefa.h"
#include "Grafo.h"

class Principal {
    
public:
    Principal();
    Principal(const Principal& orig);
    virtual ~Principal();
    
    int getQntTarefas();
    
    void inicializarMatrizFeromonio(int qntMaquinas,int qntTarefas);
    void inicializarEstruturas();
    
    void executar();
    void criarGrafo(int qntTarefas);
    void calcularLimiteMinimo(int *limiteMin);
    int calcularExtra(int *limiteMin);
    void calcularValorAdicional(int *valorAdic, double *valorNormal, int extra, int *limiteMin);
    
    void atualizarFeromonio(Grafo *grafo,double taxaSolucao);
    void evaporarFeromonio(Grafo *grafo,double taxaEvaporacao,double taxaSolucao);
    void incrementarFeromonio(Grafo *grafo,double taxaEvaporacao,double taxaSolucao);
    
    int getProximaTarefaAleatoria();    
    int getRandomNumero(int range, int limInf);
    
    Grafo* getBestSolutionFormiga();
    void setBestSolutionFormiga(Grafo *bestSolutionFormiga);
    
    void imprimirMatrizFeromonio();
    void imprimirDados();
    
    void desalocarEstruturas();
    void desalocarMatriz(int *matriz, int linhas, int colunas);
    void desalocarMatriz(int **matriz, int linhas, int colunas);
    void desalocarMatriz(int ***matriz, int linhas, int colunas);
    void desalocarMatriz(double ***matriz, int linhas, int colunas);
    
private:
    int ***arestasSetup;                 // possui os tempos de setup entre as tarefas   TAMANHO (TAREFA X TAREFA)
    int **matrizTempoTarefas;
    Grafo *grafo;                      // QNT TAREFAS
    Grafo *bestSolutionFormiga;                      
    int qntTarefas;
    int qntMaquinas;
    int limitePoluicao;
    int *custoPoluicaoMaquina;
    int *dataEntrega;
    int *alfa;
    int *beta;
    
    double ***matrizFeromonio;             // TAMANHO (TAREFA X TAREFA)
};

#endif /* PRINCIPAL_H */

