#include "arols.hpp"
#include "utils.hpp"
#include <time.h>
#include <algorithm>

AROLS::AROLS(Par instance, int max_eval, int k, int max_fails){
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
    this->INTERVAL = k;
    this->MAX_FAILS = max_fails*instance.nElements();
}

void AROLS::generateSolution(){
    vector<int> bud;
    int eval = 0;
    int iter = 1;
    while(eval < MAX_EVALUATIONS){
        //Applies local search every INTERVAL interval
        if(iter%INTERVAL == 0){
            eval += BLS();
        }
        //If not, applies the usual algorithm
        else{
            bud = generateBud();
            if(instance.getAgregated(bud) < instance.getAgregated()){
                instance.setSolution(bud);
                for(int i = 0; i < instance.nClusters(); i++)
                    instance.computeCentroid(i);
            }
            eval++;
        }
        iter++;
    }
}

//Does BLS to the chromosome and return the number of evaluations done
int AROLS::BLS(){
    Par chromosome = instance;
    vector<int> RSI;
    for(int i = 0; i < chromosome.nElements(); i++)
        RSI.push_back(i);
    random_shuffle(RSI.begin(), RSI.end());
    int fails = 0;
    int i = 0;
    bool upgrade = true;
    vector<int> auxSolution;
    int bestCluster;
    float bestAgregated;
    float auxAgregated;
    int eval = 0;

    while((upgrade || fails < MAX_FAILS) && i < RSI.size()){
        upgrade = false;
        auxSolution = chromosome.getSolution();                                 //Copy the solution
        bestCluster = auxSolution[RSI[i]];
        bestAgregated = chromosome.getAgregated(auxSolution);
        for(int j = 0; j < chromosome.nClusters(); j++){                        //Loops the clusters finding which suits better the element
            auxSolution[RSI[i]] = j;
            auxAgregated = chromosome.getAgregated(auxSolution);
            eval++;
            if(!chromosome.emptyClusters(auxSolution) && auxAgregated < bestAgregated){
                bestCluster = j;
                bestAgregated = auxAgregated;
                upgrade = true;
            }
        }
        chromosome.modifySolution(RSI[i], bestCluster);                         //Modifies the solution to set the suitablest cluster
        if(!upgrade)                                                            //If there's no changes add one fail
            fails++;
        i++;
    }
    for(int i = 0; i < chromosome.nClusters(); i++)
        chromosome.computeCentroid(i);
    this->instance = chromosome;
    return eval;
}

vector<int> AROLS::generateBud(){
    vector<int> solution = getSolution();
    vector<int> larva = generateLarva();
    vector<int>r = random_selection(rand()%instance.nElements(), instance.nElements());
    for(int i = 0; i < r.size(); i++)
        larva[r[i]] = solution[r[i]];
    return reparation(larva);
}

vector<int> AROLS::generateLarva(){
    vector<int> solution = getSolution();
    int g = rand()%solution.size();
    int s = rand()%solution.size();
    for(int i = 0; i < s; i++)
        solution[(i+g)%solution.size()] = rand()%instance.nClusters();
    return solution;
}

//Repares a child if it has an empty cluster
vector<int> AROLS::reparation(vector<int> solution){
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

const vector<int> AROLS::getSolution(){
    return this->instance.getSolution();
}

const float AROLS::getDeviation(){
    return this->instance.getDeviation();
}

const int AROLS::getInfeasibility(){
    return this->instance.getInfeasibility();
}

const float AROLS::getAgregated(){
    return this->instance.getAgregated();
}