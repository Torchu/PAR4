#include "aroes.hpp"
#include "utils.hpp"
#include <time.h>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

AROES::AROES(Par instance, float ftemp, int max_eval){
    //Creates a random solution
    this->instance = instance;
    for(int i = 0; i < this->instance.nClusters(); i++)
        this->instance.modifySolution(i,i);
    for(int i = this->instance.nClusters(); i < this->instance.nElements(); i++)
        this->instance.modifySolution(i, rand()%this->instance.nClusters());
    this->instance.shuffleSolution();
    for(int i = 0; i < this->instance.nClusters(); i++)
        this->instance.computeCentroid(i);

    this->temperature = 0.3*this->instance.getAgregated()/-log(0.3);
    this->FINAL_TEMPERATURE = ftemp;
    this->MAX_NEIGHBOURS = 5*this->instance.nElements();
    this->MAX_SUCCESS = 0.1*MAX_NEIGHBOURS;
    float M = 100000/this->MAX_NEIGHBOURS;
    this->BETA = (this->temperature - this->FINAL_TEMPERATURE)/(M * this->temperature * this->FINAL_TEMPERATURE);
    this->MAX_EVALUATIONS = max_eval;
}

void AROES::generateSolution(){
    vector<int> solution(instance.getSolution());
    vector<int> bud;
    float diff;
    float r;
    int generated;
    int acepted;
    int evaluations = 0;
    do{
        generated = 0;
        acepted = 0;
        while(generated < MAX_NEIGHBOURS && acepted < MAX_SUCCESS){                             //Cooling speed
            bud = generateBud(solution);                                                        //New solution generation
            generated++;
            diff = instance.getAgregated(bud) - instance.getAgregated(solution);                //Costs difference
            evaluations += 2;
            r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if(diff < 0 || r <= exp(-diff/temperature)){                                        //Acceptance criteria
                solution = bud;
                acepted++;
                evaluations += 2;
                if(instance.getAgregated(solution) < instance.getAgregated()){
                    instance.setSolution(solution);
                    for(int j = 0; j < instance.nClusters(); j++)
                        instance.computeCentroid(j);
                }
            }
        }
        this->temperature = this->temperature/(1+BETA*this->temperature);                       //Cooling mechanism
    }while(evaluations < MAX_EVALUATIONS && acepted > 0);                                       //Stop condition
}

vector<int> AROES::generateBud(vector<int> solution){
    vector<int> larva = generateLarva(solution);
    vector<int>r = random_selection(rand()%instance.nElements(), instance.nElements());
    for(int i = 0; i < r.size(); i++)
        larva[r[i]] = solution[r[i]];
    return reparation(larva);
}

vector<int> AROES::generateLarva(vector<int> solution){
    int g = rand()%solution.size();
    int s = rand()%solution.size();
    for(int i = 0; i < s; i++)
        solution[(i+g)%solution.size()] = rand()%instance.nClusters();
    return solution;
}

//Repares a child if it has an empty cluster
vector<int> AROES::reparation(vector<int> solution){
    bool empty = true;
    //For each cluster, if one is empty, places an element in that cluster until no cluster is empty
    while(empty){
        empty = false;
        for(int i = 0; i < instance.nClusters(); i++){
            if(instance.emptyCluster(i, solution)){
                solution[rand()%solution.size()] = i;
                empty = true;
            }
        }
    }
    return solution;
}

const vector<int> AROES::getSolution(){
    return instance.getSolution();
}

const float AROES::getDeviation(){
    return instance.getDeviation();
}

const int AROES::getInfeasibility(){
    return instance.getInfeasibility();
}

const float AROES::getAgregated(){
    return instance.getAgregated();
}