#include <iostream>
#include <time.h>
#include <string.h>
#include <map>
#include "aro.hpp"
#include "arols.hpp"
using namespace std;

int main(int argc, char **argv){
    if(argc != 5){
        cerr<<"Wrong number of arguments"<<endl
            <<"./par n_clusters elements_data restrictions_data seed"<<endl;
        return 1;
    }

    int clusters = atoi(argv[1]);
    vector<vector<float>> elements = extractElements(argv[2]);
    list<Restriction> restrictions = extractRestrictions(argv[3]);
    srand(atoi(argv[4]));
    clock_t t1, t2;
    vector<int> solution;
    Par a(clusters, elements, restrictions);
    ARO aro(a, 600000);
    AROLS arols(a, 100000, 10, 0.1);
/*
    cout<<"Solución del ARO: "<<endl;
    t1 = clock();
    aro.generateSolution();
    t2 = clock();
    solution = aro.getSolution();
    cout<<"Solución: [ ";
    for(int i = 0; i < solution.size(); i++)
        cout<<solution[i]<<" ";
    cout<<"]"<<endl;
    cout<<"Tasa_C: "<<aro.getDeviation()<<endl;
    cout<<"Tasa_Inf: "<<aro.getInfeasibility()<<endl;
    cout<<"Agregado: "<<aro.getAgregated()<<endl;
    cout<<"Tiempo: "<<((float)(t2-t1))/CLOCKS_PER_SEC<<endl<<endl;
*/
    cout<<"Solución del ARO-LS: "<<endl;
    t1 = clock();
    arols.generateSolution();
    t2 = clock();
    solution = arols.getSolution();
    cout<<"Solución: [ ";
    for(int i = 0; i < solution.size(); i++)
        cout<<solution[i]<<" ";
    cout<<"]"<<endl;
    cout<<"Tasa_C: "<<arols.getDeviation()<<endl;
    cout<<"Tasa_Inf: "<<arols.getInfeasibility()<<endl;
    cout<<"Agregado: "<<arols.getAgregated()<<endl;
    cout<<"Tiempo: "<<((float)(t2-t1))/CLOCKS_PER_SEC<<endl<<endl;

    return 0;
}