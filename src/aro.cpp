#include "aro.hpp"
#include "utils.hpp"
#include <time.h>
#include <algorithm>

ARO::ARO(Par instance, int max_eval){
    //Creates a random solution
    this->instance = instance;
    for(int i = 0; i < this->instance.nClusters(); i++)
        this->instance.modifySolution(i,i);
    for(int i = this->instance.nClusters(); i < this->instance.nElements(); i++)
        this->instance.modifySolution(i, rand()%this->instance.nClusters());
    this->instance.shuffleSolution();
    for(int i = 0; i < this->instance.nClusters(); i++)
        this->instance.computeCentroid(i);
    
    //Set the rest of the class atributes
    this->MAX_EVALUATIONS = max_eval;
}

void ARO::generateSolution(){
    vector<int> bud;
    int eval = 0;
    while(eval < MAX_EVALUATIONS){
        bud = generateBud();
        if(instance.getAgregated(bud) < instance.getAgregated()){
            instance.setSolution(bud);
            for(int i = 0; i < instance.nClusters(); i++)
                instance.computeCentroid(i);
        }
        eval++;
    }
}

vector<int> ARO::generateBud(){
    vector<int> solution = getSolution();
    vector<int> larva = generateLarva();
    vector<int>r = random_selection(rand()%instance.nElements(), instance.nElements());
    for(int i = 0; i < r.size(); i++)
        larva[r[i]] = solution[r[i]];
    return reparation(larva);
}

vector<int> ARO::generateLarva(){
    vector<int> solution = getSolution();
    int g = rand()%solution.size();
    int s = rand()%solution.size();
    for(int i = 0; i < s; i++)
        solution[(i+g)%solution.size()] = rand()%instance.nClusters();
    return solution;
}

//Repares a child if it has an empty cluster
vector<int> ARO::reparation(vector<int> solution){
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

const vector<int> ARO::getSolution(){
    return this->instance.getSolution();
}

const float ARO::getDeviation(){
    return this->instance.getDeviation();
}

const int ARO::getInfeasibility(){
    return this->instance.getInfeasibility();
}

const float ARO::getAgregated(){
    return this->instance.getAgregated();
}