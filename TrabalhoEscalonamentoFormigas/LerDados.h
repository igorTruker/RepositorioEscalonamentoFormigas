/* 
 * File:   LerDados.h
 * Author: igor
 *
 * Created on 4 de Junho de 2017, 19:28
 */

#ifndef LERDADOS_H
#define LERDADOS_H

#include <string>

using namespace std;

class LerDados {
public:
    LerDados();
    virtual ~LerDados();
    void lerArquivo(string file);

    int** getTarefas();
    int*** getSetupTarefas();
    int* getCusto();
    int getNumTarefas();
    int getNumMaquinas();
    int getLimitePoluicao();
    int* getDataEntrega();
    int* getAlfa();
    int* getBeta();
    int aleatorio(int limiteSup,int limiteInf);
    void calculaLimitePoluicao();
    void calculaCustoMaquina();
    void imprimirDados();

protected:
private:
    int numTarefas;
    int numMaquinas;
    int limitePoluicao;
    int *custo;
    int **matrizTarefas;
    int ***setupTarefas;
    int *dataEntrega;
    int *alfa;
    int *beta;

};

#endif /* LERDADOS_H */

