/* 
 * File:   Principal.cpp
 * Author: igor
 * 
 * Created on 3 de Junho de 2017, 13:35
 */

#include <iostream>
#include "Principal.h"
#include "Maquina.h"
#include "Formiga.h"
#include "LerDados.h"
#include "Grafo.h"
#include <stdlib.h>

using namespace std;

Principal::Principal(string nomeArquivo) {
    srand (time(NULL));
    this->qntTarefas = 0;
    this->qntMaquinas = 0;
    this->arestasSetup = NULL;
    this->matrizTempoTarefas = NULL;
    this->limitePoluicao = -1;
    this->custoPoluicaoMaquina = NULL;
    this->alfa = NULL;
    this->beta = NULL;
    this->dataEntrega = NULL;
    this->nomeArquivo = nomeArquivo;
}

Principal::~Principal() {
    desalocarEstruturas();
    this->qntTarefas = 0;
    this->qntMaquinas = 0;
    this->arestasSetup = NULL;
    this->matrizTempoTarefas = NULL;
    this->limitePoluicao = -1;
    this->custoPoluicaoMaquina = NULL;
    this->alfa = NULL;
    this->beta = NULL;
    this->dataEntrega = NULL;
}

int Principal::getQntTarefas(){
    return this->qntTarefas;
}

/**
 *  Inicializa a matriz com qntTarefas X qntTarefas.
 * @param qntTarefas
 */
void Principal::inicializarMatrizFeromonio(int qntMaquinas,int qntTarefas) {
    this->matrizFeromonio = new double**[qntMaquinas];
    
    for(int index = 0; index < qntMaquinas; index++){
        this->matrizFeromonio[index] = new double*[qntTarefas];
        for(int indexJ = 0; indexJ < qntTarefas; indexJ++){
            this->matrizFeromonio[index][indexJ] = new double[qntTarefas];
            for(int indexI = 0; indexI < qntTarefas; indexI++){
                this->matrizFeromonio[index][indexJ][indexI] = 10.0;
            }
        }
    }
}

/**
 *  Inicializa as estruturas iniciais do programa.
 */
bool Principal::inicializarEstruturas() {
    
    LerDados *ler = new LerDados();
//    bool existeArquivo = ler->lerArquivo("instancias/m2n5tau0.3R0.25eta0.25i0.txt");
//    bool existeArquivo = ler->lerArquivo("instancias/m2n5tau0.3R0.25eta0.25i0.txt-I.A.txt");
//    ler->lerArquivo("instancias/I3-m5n8-A.txt");
//    ler->lerArquivo("instancias/m3n50tau0.3R0.25eta0.25i4-I.D.txt");
//    bool existeArquivo = ler->lerArquivo("instancias/m2n20tau0.3R0.25eta0.25i5.txt-I.E.txt");
//    bool existeArquivo = ler->lerArquivo("instancias/m2n10tau0.3R0.25eta0.25i0-I.D.txt");
    bool existeArquivo = ler->lerArquivo(this->nomeArquivo.c_str());
    
    if(existeArquivo){
        this->qntMaquinas = ler->getNumMaquinas();
        this->qntTarefas = ler->getNumTarefas();
        this->arestasSetup = ler->getSetupTarefas();
        this->matrizTempoTarefas = ler->getTarefas();
        this->limitePoluicao = ler->getLimitePoluicao();
        this->custoPoluicaoMaquina = ler->getCusto();
        this->alfa = ler->getAlfa();
        this->beta = ler->getBeta();
        this->dataEntrega = ler->getDataEntrega();

        inicializarMatrizFeromonio(this->qntMaquinas,this->qntTarefas);

        this->bestSolutionFormiga = new EstruturaSolucao();
        this->bestSolutionFormiga->criarGrafoVetor(this->qntMaquinas);
    }else{
        cout << "Não existe arquivo !" << endl;
    }
    delete ler;
    
    return existeArquivo;
}

/**
 *  Executa o procedimento principal do algoritmo.
 */
void Principal::executar(){    
    
    EscreverDados *teste = new EscreverDados();
    teste->abrirArquivo("teste.txt");
    
    if(inicializarEstruturas()){
        criarGrafo(this->getQntTarefas());
        
        bool notEnd = false;
        double valorNormal = 0.0;
        int *limiteMin = new int[this->qntMaquinas];/* Limite minimo de poluicao para gastar*/
        int *valorAdic = new int[this->qntMaquinas]; /* Valor adicional para cada máquina*/
        int extra = 0;
        int numGeracoes = numIteracao;

        // solucao inicial
        EstruturaSolucao *solucaoMaquina = new EstruturaSolucao();
        solucaoMaquina->criarGrafoVetor(this->qntMaquinas);

        while(!notEnd){
            valorNormal = 0.0;
            calcularLimiteMinimo(limiteMin); 
            calcularValorAdicional(valorAdic,&valorNormal,extra,limiteMin);

            this->grafo->resetarSelecaoGrafo(); // reseta a seleção do grafo

            int indiceTarefa = getRandomNumero(this->qntTarefas,0);
            int indiceTarefaAnterior = indiceTarefa;

            for(int indexFormiga = 0; indexFormiga < this->qntMaquinas; indexFormiga++){
                Formiga *formigas = new Formiga();

                while(limiteMin[indexFormiga] > 0 && indiceTarefa != -1){                        
                    limiteMin[indexFormiga] =  limiteMin[indexFormiga]-(this->matrizTempoTarefas[indiceTarefa][indexFormiga] * this->custoPoluicaoMaquina[indexFormiga]);                

                    if(limiteMin[indexFormiga] > 0){
                        // Add anterior que entrou na while que acabou de ser avaliada no limite.
                        Tarefa *tarefaRemovida = this->grafo->removerTarefa(indiceTarefaAnterior,indiceTarefa);
                        formigas->adicionarTarefaUltima(tarefaRemovida,indexFormiga,matrizTempoTarefas,arestasSetup); // alterar indice
                        indiceTarefaAnterior = indiceTarefa;
                        
                        // avaliar feromonio e proxima tarefa
                        double totalFeromonio = calcularTotalFeromonio(this->grafo,indexFormiga,indiceTarefaAnterior,matrizFeromonio);
                        indiceTarefa = escolherMelhorCaminho(this->grafo, indiceTarefaAnterior,totalFeromonio,indexFormiga);
                        
//                        cout << endl;
//                        this->grafo->imprimirVetor();
                    }      
                }
                formigas->imprimirDados();
                
                solucaoMaquina->setListaSolucao(formigas->getTarefas(),indexFormiga);
                delete formigas;
            }
            
//            solucaoMaquina->imprimirGrafo();
            
            if(ehViavel(solucaoMaquina)){
                double taxaSolucao = 0;
                
                solucaoMaquina->calcularFuncaoObj(dataEntrega,alfa,beta);
                if(solucaoMaquina->getFuncaoObj() > 0){
                    // Ociosidade
                    for(int index = 0; index < this->qntMaquinas; index++){
                        inserirOciosidade(solucaoMaquina,index);
                    }
                }
                solucaoMaquina->calcularFuncaoObj(dataEntrega,alfa,beta);
                teste->escreverDadosSol(solucaoMaquina);
                
                if(this->bestSolutionFormiga->estaVazio()){
                    atualizarBestSolucaoVazia(solucaoMaquina,&taxaSolucao);
                }else{
                    atualizarBestSolucao(solucaoMaquina,&taxaSolucao,&numGeracoes);
                }
                
            }else{
//                cout << "<<<<<<<<< " << numGeracoes << " >>>> DEU RUIM <<<<" << endl;
                solucaoMaquina->finalizarGrafo();
            }

            if(numGeracoes == 0)
                notEnd = true;
            else
                numGeracoes -= 1;

            delete [] limiteMin;
            delete [] valorAdic;
        }

        cout << "\n\n" << endl;
        this->bestSolutionFormiga->imprimirGrafo();
        cout << " Funcao Obj : " << this->bestSolutionFormiga->getFuncaoObj() << endl;
        cout << endl;
        
    }else{
        cout << "Não foi possível rodar !" << endl;
    }
    
    delete teste;
}

void Principal::inserirOciosidade(EstruturaSolucao* estruturaSolucao, int indiceMaquina) {
    int tarefa = 0;
    int tempoTermino = 0;
    int tarefaAnterior = 0;
    int firstTask = 0;
    int lastTask = 0;
    int qntTarefas = 0;
    
    if(estruturaSolucao->getListaTarefaProxima(indiceMaquina) != NULL){
        Tarefa *tarefaA = estruturaSolucao->getListaTarefaProxima(indiceMaquina);
        
        while(tarefaA->getProxima() != NULL){
            tarefaA = tarefaA->getProxima();
            qntTarefas += 1;
        }
        
        firstTask = tarefaA->getIndice();
        tarefa = firstTask;
        
        if(dataEntrega[tarefa] >= matrizTempoTarefas[tarefa][indiceMaquina]){
            tempoTermino = dataEntrega[tarefa];
        }else{
            tempoTermino = matrizTempoTarefas[tarefa][indiceMaquina];
        }
        tarefaA->setTempoTermino(tempoTermino);
        tarefaA->setTempoInicio(tempoTermino - matrizTempoTarefas[tarefa][indiceMaquina]);
        
        tarefaAnterior = tarefa;
        
//        cout << " Etapa 1" << endl;
        
        for(int index = 0; index < qntTarefas; index++){
            tarefaA = estruturaSolucao->getListaTarefaProxima(indiceMaquina);
            while(tarefaA->getProxima()->getIndice() != tarefaAnterior){
                tarefaA = tarefaA->getProxima();
            }
            
            if((tarefaA->getProxima()->getTempoTermino() + arestasSetup[tarefaA->getProxima()->getIndice()][tarefaA->getIndice()][indiceMaquina] + matrizTempoTarefas[tarefaA->getIndice()][indiceMaquina]) < dataEntrega[tarefaA->getIndice()]){
                firstTask = tarefaA->getIndice();
                lastTask = tarefaA->getIndice();
                tarefaA->setTempoTermino( dataEntrega[tarefaA->getIndice()]);
                tarefaA->setTempoInicio( dataEntrega[tarefaA->getIndice()] - arestasSetup[tarefaA->getProxima()->getIndice()][tarefaA->getIndice()][indiceMaquina] - matrizTempoTarefas[tarefaA->getIndice()][indiceMaquina]);
            }else{
                lastTask = tarefaA->getIndice();
                tarefaA->setTempoTermino( tarefaA->getProxima()->getTempoTermino() + arestasSetup[tarefaA->getProxima()->getIndice()][tarefaA->getIndice()][indiceMaquina] + matrizTempoTarefas[tarefaA->getIndice()][indiceMaquina]);
                tarefaA->setTempoInicio(tarefaA->getProxima()->getTempoTermino());
            }
            
//            cout << " Etapa 2" << endl;
            moverBloco(estruturaSolucao,indiceMaquina,lastTask,firstTask);
            tarefaAnterior = tarefaA->getIndice();
        }
    }
}

void Principal::moverBloco(EstruturaSolucao* estruturaSolucao,int indiceMaquina, int lastTask, int firstTask) {
    
    int funcaoObj = estruturaSolucao->getFuncaoObj();
    int novaFuncaoObj = funcaoObj;
    int Cmax = estruturaSolucao->getListaTarefaProxima(indiceMaquina)->getTempoTermino();
    Tarefa *tarefaA;
    Tarefa *tarefaB = estruturaSolucao->getListaTarefaProxima(indiceMaquina);
    
    // encontra a ultima tarefa do bloco
    while((tarefaB->getProxima() != NULL)&&(tarefaB->getIndice() != lastTask)){
        tarefaB = tarefaB->getProxima();
    }
    tarefaA = tarefaB;
    
//    cout << " Etapa 3" << endl;
    // adianta bloco
    while(novaFuncaoObj < funcaoObj){
        funcaoObj = estruturaSolucao->getFuncaoObj();
        tarefaB = tarefaA;
        
//        cout << " Funcao Obj " << funcaoObj << endl;
        
        while(tarefaB->getIndice() != firstTask){
            tarefaB->setTempoInicio( tarefaB->getTempoInicio() - 1);
            tarefaB->setTempoTermino( tarefaB->getTempoTermino() - 1);
            tarefaB = tarefaB->getProxima();
        }
        tarefaB->setTempoInicio( tarefaB->getTempoInicio() - 1);
        tarefaB->setTempoTermino( tarefaB->getTempoTermino() - 1);
        
        novaFuncaoObj = estruturaSolucao->getFuncaoObj();
        
//        cout << "Func Nova : " << novaFuncaoObj << endl;
        
        if((tarefaB->getProxima() != NULL) && (tarefaB->getTempoInicio() < tarefaB->getProxima()->getTempoTermino())){
            novaFuncaoObj = funcaoObj + 1;
        }
        if((tarefaB->getProxima() != NULL) && (tarefaB->getTempoInicio() < 0)){
            novaFuncaoObj = funcaoObj + 1;
        }
    }
    
//    cout << " Etapa 4" << endl;
    
    tarefaB = tarefaA;
    
    // desfaz ultimo adiantamento
    while(tarefaB->getIndice() != firstTask){
        tarefaB->setTempoInicio( tarefaB->getTempoInicio() + 1);
        tarefaB->setTempoTermino( tarefaB->getTempoTermino() + 1);
        tarefaB = tarefaB->getProxima();
    }
    tarefaB->setTempoInicio( tarefaB->getTempoInicio() + 1);
    tarefaB->setTempoTermino( tarefaB->getTempoTermino() + 1);
    
    // atrasa bloco
    funcaoObj = estruturaSolucao->getFuncaoObj();
    novaFuncaoObj = funcaoObj;
    
//    cout << " Etapa 5" << endl;
    
    while(novaFuncaoObj < funcaoObj){
        funcaoObj = novaFuncaoObj;
        tarefaB = tarefaA;
        
        while(tarefaB->getIndice() != firstTask){
            tarefaB->setTempoInicio( tarefaB->getTempoInicio() + 1);
            tarefaB->setTempoTermino( tarefaB->getTempoTermino() + 1);
            tarefaB = tarefaB->getProxima();
        }
        tarefaB->setTempoInicio( tarefaB->getTempoInicio() + 1);
        tarefaB->setTempoTermino( tarefaB->getTempoTermino() + 1);
        
        novaFuncaoObj = estruturaSolucao->getFuncaoObj();
    }
    
    // desfaz ultimo atraso
    tarefaB = tarefaA;
    
//    cout << " Etapa 6" << endl;
    
    while(tarefaB->getIndice() != firstTask){
        tarefaB->setTempoInicio( tarefaB->getTempoInicio() - 1);
        tarefaB->setTempoTermino( tarefaB->getTempoTermino() - 1);
        tarefaB = tarefaB->getProxima();
    }
    
    tarefaB->setTempoInicio( tarefaB->getTempoInicio() - 1);
    tarefaB->setTempoTermino( tarefaB->getTempoTermino() - 1);
    
    if((tarefaB->getProxima() != NULL) && (tarefaB->getTempoInicio() == tarefaB->getProxima()->getTempoTermino())){
        novaFuncaoObj = funcaoObj + 1;
    }
}

bool Principal::ehViavel(EstruturaSolucao* solucao) {
    int totalTarefas = 0;
    for(int index = 0; index < solucao->getTamanho(); index++){
        Tarefa *tarefa = solucao->getListaTarefaProxima(index);
        
        if(tarefa != NULL){
            totalTarefas += 1;
            while(tarefa->getProxima() != NULL){
                tarefa = tarefa->getProxima();
                totalTarefas += 1;
            }
        }
    }
    if(totalTarefas == this->qntTarefas)
        return true;
    return false;
}


void Principal::atualizarBestSolucaoVazia(EstruturaSolucao *solucaoMaquina, double *taxaSolucao){
    this->bestSolutionFormiga->transferirTarefas(solucaoMaquina);
    this->bestSolutionFormiga->calcularFuncaoObj(dataEntrega,alfa,beta);
    cout << "\n ___\n Funcao primeira : " << bestSolutionFormiga->getFuncaoObj() << " \n ____ \n" << endl;
    *taxaSolucao = 1;
    atualizarFeromonio(this->bestSolutionFormiga,*taxaSolucao);
}

void Principal::atualizarBestSolucao(EstruturaSolucao *solucaoMaquina, double *taxaSolucao, int *numGeracoes) {
//    solucaoMaquina->calcularFuncaoObj(dataEntrega,alfa,beta);
    *taxaSolucao = ((double)this->bestSolutionFormiga->getFuncaoObj() / (double)solucaoMaquina->getFuncaoObj() );
    atualizarFeromonio(solucaoMaquina,*taxaSolucao);

    cout << "\n\n Funcao atual : " << solucaoMaquina->getFuncaoObj() << " funcao melhor : " << this->bestSolutionFormiga->getFuncaoObj() << endl;

    if(this->bestSolutionFormiga->getFuncaoObj() > solucaoMaquina->getFuncaoObj()){
        this->bestSolutionFormiga->finalizarGrafo();
        this->bestSolutionFormiga->transferirTarefas(solucaoMaquina);
        this->bestSolutionFormiga->setFuncaoObj( solucaoMaquina->getFuncaoObj());

        *numGeracoes = numIteracao;

        cout << "\n------------------------------------------------------------\n";
        this->bestSolutionFormiga->imprimirGrafo();
        cout << "\n------------------------------------------------------------\n";

    }else{
        solucaoMaquina->finalizarGrafo();
    }
//    imprimirMatrizFeromonio();
}

/*
 * Retorna o vetor com o limite minimo de poluição para cada máquina
 */
void Principal::calcularLimiteMinimo(int *vetor) {
    int menorPoluicao = 0;
    int calculoPoluicao = 0;
    int maqMenorPoluicao = 0;
    
    for(int index = 0; index < this->qntMaquinas; index++){
        vetor[index]= 0;
    }    
    menorPoluicao = this->custoPoluicaoMaquina[0] * this->matrizTempoTarefas[0][0];
    
    for(int index = 0; index < this->qntTarefas; index++){
        maqMenorPoluicao = 0;
        menorPoluicao = this->custoPoluicaoMaquina[maqMenorPoluicao] * this->matrizTempoTarefas[index][maqMenorPoluicao];
        
        for(int indexMaq = 1; indexMaq < this->qntMaquinas; indexMaq++){
            calculoPoluicao = this->custoPoluicaoMaquina[indexMaq] * this->matrizTempoTarefas[index][indexMaq];
            if(menorPoluicao > calculoPoluicao){
                menorPoluicao = calculoPoluicao;
                maqMenorPoluicao = indexMaq;
            }
        }
        vetor[maqMenorPoluicao] += menorPoluicao;
    }
    
    for(int index = 0; index < this->qntMaquinas; index++){
        cout << " Limite Min [ "<< index <<" ] : " << vetor[index] << endl;
    }    
}

void Principal::calcularValorAdicional(int* valorAdic, double *valorNormal, int extra, int* limiteMin) {
    /* Inicializar o vetor da taxa adicional para com os valores aleatorios*/
    int total = 0;
    
    for(int index = 0; index < this->qntMaquinas; index++){
        total += limiteMin[index];
    }
    extra = this->limitePoluicao - total;
    
    for(int indexMaq = 0; indexMaq < this->qntMaquinas; indexMaq++){
        valorAdic[indexMaq] = getRandomNumero(100,0);
        *valorNormal += valorAdic[indexMaq];
    }
    
    for(int indexMaq = 0; indexMaq < this->qntMaquinas; indexMaq++){
        valorAdic[indexMaq] = (valorAdic[indexMaq]/ *valorNormal) * extra;
        cout << "\n Valor Adic : " <<  valorAdic[indexMaq] << endl;
        limiteMin[indexMaq] += valorAdic[indexMaq];
        cout << " Limite Min : " <<  limiteMin[indexMaq] << endl;
        cout << " Limite Poluicao : " << this->limitePoluicao << endl;
    }
}

int Principal::getProximaTarefaAleatoria() {
    int tarefasNaoMarcadas = this->qntTarefas - this->grafo->getNumTarefasMarcadas() ;
    return this->grafo->getIndiceEnesimaTarefaNaoMarcada(tarefasNaoMarcadas);
}

int Principal::escolherMelhorCaminho(Grafo* grafo, int indiceTarefaAnterior, double totalFeromonio,int indexMaquina) {
    int valor =  0;
    int indice = -1;
    int div = 1000;
    
    if(totalFeromonio < 1){
        valor = (totalFeromonio * div);
        
        if(valor == 0){
            valor = getRandomNumero(1,0);
        }else{        
            valor = getRandomNumero(valor,0);
            valor = valor / div;
        }
    }else{
        valor = getRandomNumero(totalFeromonio,0);
    }
    
    for(int index = 0; index < grafo->getTamanho(); index++){
        if(grafo->getListaTarefaTotal(index)->getSelecionada()== false){
            valor = valor - matrizFeromonio[indexMaquina][indiceTarefaAnterior][index];
            indice = index;
        }
    }    
    return indice;
}


/**
 *  Cria o grafo completo com as tarefas, em que cada posição do vetor 
 * possui todas as tarefas, menos a tarefa indice do vetor.
 */
void Principal :: criarGrafo(int qntTarefas){
    this->grafo = new Grafo(qntTarefas);
    this->grafo->criarGrafoCompleto(qntTarefas);
}

EstruturaSolucao* Principal::getBestSolutionFormiga() {
    return this->bestSolutionFormiga;
}

void Principal::setBestSolutionFormiga(EstruturaSolucao* bestSolutionFormiga) {
    this->bestSolutionFormiga = bestSolutionFormiga;
}

void Principal::atualizarFeromonio(EstruturaSolucao *solucao, double taxaSolucao) {
    double taxaEvaporacao = 0.3;
    evaporarFeromonio(solucao,taxaEvaporacao,taxaSolucao);
    incrementarFeromonio(solucao,taxaEvaporacao,taxaSolucao);
}

void Principal::evaporarFeromonio(EstruturaSolucao *solucao,double taxaEvaporacao,double taxaSolucao) {
    for(int indexMaquina = 0; indexMaquina < this->qntMaquinas; indexMaquina++){
        for(int indexI = 0; indexI < qntTarefas; indexI++){
            for(int indexJ = 0; indexJ < this->qntTarefas; indexJ++){
                matrizFeromonio[indexMaquina][indexI][indexJ] = matrizFeromonio[indexMaquina][indexI][indexJ] * (1 - taxaEvaporacao);
                
                if(matrizFeromonio[indexMaquina][indexI][indexJ] < 0){
                    matrizFeromonio[indexMaquina][indexI][indexJ] = 0;
                }
            }
        }
    }
}

void Principal::incrementarFeromonio(EstruturaSolucao *solucao,double taxaEvaporacao,double taxaSolucao){
    for(int indexMaquina = 0; indexMaquina < this->qntMaquinas; indexMaquina++){
        Tarefa *t = solucao->getListaTarefaProxima(indexMaquina);
        
        while((t != NULL)&&(t->getProxima() != NULL)){
            int indexAtual = t->getIndice();
            int indexProximo = t->getProxima()->getIndice();
            matrizFeromonio[indexMaquina][indexProximo][indexAtual] = matrizFeromonio[indexMaquina][indexProximo][indexAtual]  + taxaSolucao * taxaEvaporacao;
            t = t->getProxima();
        }
    }
}

double Principal::calcularTotalFeromonio(Grafo *grafo, int indiceMaquina, int indiceVetor, double ***matrizFeromonio) {
    double totalFeromonio = 0.0;
    
    for(int index = 0; index < grafo->getTamanho(); index++){
        if(grafo->getListaTarefaTotal(index)->getSelecionada()== false){
            totalFeromonio += matrizFeromonio[indiceMaquina][indiceVetor][index];
        }
    }
    
    return totalFeromonio;
}

/**
 * Imprime a matriz.
 */
void Principal::imprimirMatrizFeromonio() {
    for(int indexI = 0; indexI < qntMaquinas; indexI++){
        cout << endl;
        for(int indexJ = 0; indexJ < getQntTarefas(); indexJ++){
            for(int index = 0; index < getQntTarefas(); index++){
                cout << this->matrizFeromonio[indexI][indexJ][index] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Desaloca todas as estruturas.
 */
void Principal :: desalocarEstruturas(){
    delete this->grafo;
//    delete this->bestSolutionFormiga;
    desalocarMatriz(this->arestasSetup,this->qntTarefas,this->qntTarefas);
    desalocarMatriz(this->matrizFeromonio,this->qntMaquinas,this->qntTarefas);
}

void Principal :: desalocarMatriz(int *matriz, int linhas, int colunas){
    delete [] matriz;
}

void Principal :: desalocarMatriz(int **matriz, int linhas, int colunas){
    for(int index = 0; index < colunas; index++){
        delete [] matriz[index];
    }
    delete [] matriz;
}

void Principal :: desalocarMatriz(int ***matriz, int linhas, int colunas){
    for(int indexI = 0; indexI < linhas; indexI++){
        for(int index = 0; index < colunas; index++){
            delete [] matriz[indexI][index];
        }
        delete [] matriz[indexI];
    }
    delete [] matriz;
}

void Principal :: desalocarMatriz(double ***matriz, int linhas, int colunas){
    for(int indexI = 0; indexI < linhas; indexI++){
        for(int index = 0; index < colunas; index++){
            delete [] matriz[indexI][index];
        }
        delete [] matriz[indexI];
    }
    delete [] matriz;
}

double*** Principal::getMatrizFeromonio() {
    return this->matrizFeromonio;
}

int Principal::getQntMaquinas() {
    return this->qntMaquinas;
}

void Principal :: imprimirDados(){
    cout << "Numero de maquinas : " << this->qntMaquinas << endl;
    cout << "Numero de tarefas : " << this->qntTarefas << endl;
    cout << "Custo de maquinas : " << endl;
    for(int i = 0; i < this->qntMaquinas; i++){
        cout << this->custoPoluicaoMaquina[i] << " ";
    }
    cout << "\nTempos das tarefas : " << endl;
    for(int i = 0; i < this->qntTarefas; i++){
        for(int k = 0; k < this->qntMaquinas; k++){
            cout << this->matrizTempoTarefas[i][k] << " ";
        }
        cout << "\n";
    }
    cout << "\nSetup : " << endl;
    for(int k = 0; k < this->qntMaquinas; k++){
        for(int i = 0; i < this->qntTarefas; i++){
            for(int j = 0; j < this->qntTarefas; j++){
                cout << this->arestasSetup[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "\nAlfa : " << endl;
    for(int i = 0; i < this->qntTarefas; i++){
        cout << this->alfa[i] << " ";
    }
    cout << "\nBeta : " << endl;
    for(int i = 0; i < this->qntTarefas; i++){
        cout << this->beta[i] << " ";
    }
    cout << "\nLimite de poluicao : " << this->limitePoluicao << "\n\n" << endl;
}

/*
 * Gera um valor aleatório => rand() % range + limSup.
 * Ex: rand() % 100 + 1 => 1 a 99.
 */
int Principal::getRandomNumero(int range, int limInf) {
    return (rand() % range + limInf);
}