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
    
    void inicializarMatrizFeromonio(int qntTarefas);
    void inicializarEstruturas();
    
    void executar();
    void criarGrafo(int qntTarefas);
    void calcularLimiteMinimo(int *limiteMin);
    int calcularExtra(int *limiteMin);
    void calcularValorAdicional(int *valorAdic, double *valorNormal, int extra, int *limiteMin);
    
    int getProximaTarefaAleatoria();    
    int getRandomNumero(int range, int limInf);
    
    void imprimirMatrizFeromonio();
    void imprimirDados();
    
    void desalocarEstruturas();
    void desalocarMatriz(int *matriz, int linhas, int colunas);
    void desalocarMatriz(int **matriz, int linhas, int colunas);
    void desalocarMatriz(int ***matriz, int linhas, int colunas);
    
private:
    int ***arestasSetup;                 // possui os tempos de setup entre as tarefas   TAMANHO (TAREFA X TAREFA)
    int **matrizFeromonio;             // TAMANHO (TAREFA X TAREFA)
    int **matrizTempoTarefas;
    Grafo *grafo;                      // QNT TAREFAS
    int qntTarefas;
    int qntMaquinas;
    int limitePoluicao;
    int *custoPoluicaoMaquina;
    int *dataEntrega;
    int *alfa;
    int *beta;
    
};

#endif /* PRINCIPAL_H */

