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
    
    EscreverDados *escritor = new EscreverDados();
    escritor->abrirArquivo("saidaSolucao.txt");
    
//    for(int index = 0; index < Principal::numTentativas; index++){
//    for(int index = 0; index < 2; index++){
        Principal *p = new Principal();
        p->executar();
        escritor->escreverDadosSol(p->getBestSolutionFormiga());
        delete p;
//    }
    escritor->fecharArquivo();
    delete escritor;
    
    return 0;
}

