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
    cout << "Funcionou !" << endl;
    
    Principal *p = new Principal();
    p->executar();
//    p->imprimirGrafo();
    
    delete p;
    
    return 0;
}

