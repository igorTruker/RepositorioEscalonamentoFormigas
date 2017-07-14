/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EscreverDados.h
 * Author: igor
 *
 * Created on 4 de Junho de 2017, 19:29
 */

#ifndef ESCREVERDADOS_H
#define ESCREVERDADOS_H

#include <string>
#include <fstream>

#include "EstruturaSolucao.h"

using namespace std;

class EscreverDados {
public:
    EscreverDados();
    EscreverDados(const EscreverDados& orig);
    virtual ~EscreverDados();
    
    void abrirArquivo(string arquivo);
    void escreverDados(string dados);
    void escreverDadosSol(EstruturaSolucao *solucao);
    void fecharArquivo();
private:
    ofstream arquivo;
};

#endif /* ESCREVERDADOS_H */

