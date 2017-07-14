/* 
 * File:   main.cpp
 * Author: igor
 *
 * Created on 3 de Junho de 2017, 11:51
 */
#include <iostream>
#include <cstdlib>
#include "Principal.h"

using namespace std;

int main(int argc, char** argv) {
    
    string instancias[] = {"instancias/m2n5tau0.3R0.25eta0.25i0.txt",
      "instancias/m2n5tau0.3R0.25eta0.25i0.txt-I.A.txt", "instancias/I3-m5n8-A.txt",
      "instancias/m3n50tau0.3R0.25eta0.25i4-I.D.txt","instancias/m2n20tau0.3R0.25eta0.25i5.txt-I.E.txt",
      "instancias/m2n10tau0.3R0.25eta0.25i0-I.D.txt","instancias/m3n50tau0.3R0.25eta0.25i8-I.E.txt"};
//    Principal *p = new Principal("instancias/m2n10tau0.3R0.25eta0.25i0-I.D.txt");
    
    EscreverDados *escritor = new EscreverDados();
    escritor->abrirArquivo("saidaSolucao.txt");
    
    Principal *p = new Principal(instancias[6].c_str());
    p->executar();
    
    escritor->escreverDadosSol(p->getBestSolutionFormiga());
    escritor->escreverFeromonio(p->getMatrizFeromonio(),p->getQntTarefas(),p->getQntMaquinas());
    delete p;
    
    escritor->fecharArquivo();
    delete escritor;
    
    return 0;
}

