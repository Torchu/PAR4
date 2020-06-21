#include <iostream>
#include <time.h>
#include <string.h>
#include <map>
#include "bmb.hpp"
#include "ils.hpp"
#include "es.hpp"
#include "ilses.hpp"

using namespace std;

int main(int argc, char **argv){
    if(argc != 5){
        cerr<<"Wrong number of arguments"<<endl
            <<"./p1 n_clusters elements_data restrictions_data seed"<<endl;
        return 1;
    }

    int clusters = atoi(argv[1]);
    vector<vector<float>> elements = extractElements(argv[2]);
    list<Restriction> restrictions = extractRestrictions(argv[3]);
    srand(atoi(argv[4]));
    clock_t t1, t2;
    vector<int> solution;
    Par a(clusters, elements, restrictions);
    BMB bmb(a, 10, 10000);
    ILS ils(a, 10000, 10, 0.1);
    ES es(a, 0.001, 100000);
    ILSES ilses(a, 0.001, 10000, 10, 0.1);

    cout<<"Solución del BMB: "<<endl;
    t1 = clock();
    bmb.generateSolution();
    t2 = clock();
    solution = bmb.getSolution();
    cout<<"Solución: [ ";
    for(int i = 0; i < solution.size(); i++)
        cout<<solution[i]<<" ";
    cout<<"]"<<endl;
    cout<<"Tasa_C: "<<bmb.getDeviation()<<endl;
    cout<<"Tasa_Inf: "<<bmb.getInfeasibility()<<endl;
    cout<<"Agregado: "<<bmb.getAgregated()<<endl;
    cout<<"Tiempo: "<<((float)(t2-t1))/CLOCKS_PER_SEC<<endl<<endl;

    cout<<"Solución del ILS: "<<endl;
    t1 = clock();
    ils.generateSolution();
    t2 = clock();
    solution = ils.getSolution();
    cout<<"Solución: [ ";
    for(int i = 0; i < solution.size(); i++)
        cout<<solution[i]<<" ";
    cout<<"]"<<endl;
    cout<<"Tasa_C: "<<ils.getDeviation()<<endl;
    cout<<"Tasa_Inf: "<<ils.getInfeasibility()<<endl;
    cout<<"Agregado: "<<ils.getAgregated()<<endl;
    cout<<"Tiempo: "<<((float)(t2-t1))/CLOCKS_PER_SEC<<endl<<endl;

    cout<<"Solución del ES: "<<endl;
    t1 = clock();
    es.generateSolution();
    t2 = clock();
    solution = es.getSolution();
    cout<<"Solución: [ ";
    for(int i = 0; i < solution.size(); i++)
        cout<<solution[i]<<" ";
    cout<<"]"<<endl;
    cout<<"Tasa_C: "<<es.getDeviation()<<endl;
    cout<<"Tasa_Inf: "<<es.getInfeasibility()<<endl;
    cout<<"Agregado: "<<es.getAgregated()<<endl;
    cout<<"Tiempo: "<<((float)(t2-t1))/CLOCKS_PER_SEC<<endl<<endl;

    cout<<"Solución del ILS-ES: "<<endl;
    t1 = clock();
    ilses.generateSolution();
    t2 = clock();
    solution = ilses.getSolution();
    cout<<"Solución: [ ";
    for(int i = 0; i < solution.size(); i++)
        cout<<solution[i]<<" ";
    cout<<"]"<<endl;
    cout<<"Tasa_C: "<<ilses.getDeviation()<<endl;
    cout<<"Tasa_Inf: "<<ilses.getInfeasibility()<<endl;
    cout<<"Agregado: "<<ilses.getAgregated()<<endl;
    cout<<"Tiempo: "<<((float)(t2-t1))/CLOCKS_PER_SEC<<endl<<endl;

    return 0;
}