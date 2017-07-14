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
#include "EstruturaSolucao.h"
#include "EscreverDados.h"
#include <string>

using namespace std;

class Principal {
    
public:
    Principal();
    Principal(const Principal& orig);
    virtual ~Principal();
    
    void inicializarMatrizFeromonio(int qntMaquinas,int qntTarefas);
    bool inicializarEstruturas();
    
    void executar();
    void criarGrafo(int qntTarefas);
    void calcularLimiteMinimo(int *limiteMin);
    void calcularValorAdicional(int *valorAdic, double *valorNormal, int extra, int *limiteMin);
    
    void atualizarFeromonio(EstruturaSolucao *grafo,double taxaSolucao);
    void evaporarFeromonio(EstruturaSolucao *grafo,double taxaEvaporacao,double taxaSolucao);
    void incrementarFeromonio(EstruturaSolucao *grafo,double taxaEvaporacao,double taxaSolucao);
    
    void inserirOciosidade(EstruturaSolucao* estruturaSolucao,int indiceMaquina);
    void moverBloco(EstruturaSolucao* estruturaSolucao,int indiceMaquina, int lastTask, int firstTask);
    
    double calcularTotalFeromonio(Grafo* grafo, int indiceMaquina, int indiceVetor, double ***matrizFeromonio);
    int escolherMelhorCaminho(Grafo* grafo, int indiceTarefaAnterior, double totalFeromonio,int indexMaquina) ;
    
    void atualizarBestSolucaoVazia(EstruturaSolucao *solucaoMaquina, double *taxaSolucao);
    void atualizarBestSolucao(EstruturaSolucao *solucaoMaquina, double *taxaSolucao, int *numGeracoes);
    
    int getProximaTarefaAleatoria();    
    int getRandomNumero(int range, int limInf);
    int getQntTarefas();
    
    EstruturaSolucao* getBestSolutionFormiga();
    void setBestSolutionFormiga(EstruturaSolucao *bestSolutionFormiga);
    
    void imprimirMatrizFeromonio();
    void imprimirDados();
    
    void desalocarEstruturas();
    void desalocarMatriz(int *matriz, int linhas, int colunas);
    void desalocarMatriz(int **matriz, int linhas, int colunas);
    void desalocarMatriz(int ***matriz, int linhas, int colunas);
    void desalocarMatriz(double ***matriz, int linhas, int colunas);
    
    const static int numIteracao = 100;
    const static int numTentativas = 50;
private:
    int ***arestasSetup;                 // possui os tempos de setup entre as tarefas   TAMANHO (TAREFA X TAREFA)
    int **matrizTempoTarefas;
    Grafo *grafo;                      // QNT TAREFAS
    EstruturaSolucao *bestSolutionFormiga;                      
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

