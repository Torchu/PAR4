#include <iostream>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include "par.hpp"

//Class constructor
Par::Par(int clusters, vector<vector<float>> elements, list<Restriction> restrictions){
    this->elements = elements;
    this->restrictions = restrictions;
    this->solution = vector<int>(elements.size(), -1);
    this->centroids = vector<vector<float>>(clusters);
    this->lambda = getLongestDistance()/restrictions.size();
}

//Copy constructor
Par::Par(const Par& other){
    this->elements = other.elements;
    this->restrictions = other.restrictions;
    this->solution = other.solution;
    this->centroids = other.centroids;
    this->lambda = other.lambda;
}

//Default constructor
Par::Par(){
}

//Calculates the longest distance between every element in the set
const float Par::getLongestDistance(){
    float maxDistance = 0;
    for(int i = 0; i < nElements(); i++)
        for(int j = i+1; j < nElements(); j++)
            if(getDistance(this->elements[i], this->elements[j]) > maxDistance)
                maxDistance = getDistance(this->elements[i], this->elements[j]);
    return maxDistance;
}

//Calculates the distance between 2 elements in the set
const float Par::getDistance(vector<float> a, vector<float> b){
    float distance = 0;
    for(int i = 0; i < nAtributes(); i++)
        distance += pow((a[i] - b[i]), 2);
    return sqrt(distance);
}

//Calculates the centroid's position
void Par::computeCentroid(int cluster){
    int nelements = 0;
    vector<float> newCentroid(nAtributes(),0);
    for(int i = 0; i < solution.size(); i++)                    //For every elements in the cluster, the centroid adds its positions and
        if(solution[i] == cluster){                             //Records how many elements the cluster has
            nelements++;
            for(int j = 0; j < nAtributes(); j++)
                newCentroid[j] += this->elements[i][j];
        }
    for(int i = 0; i < newCentroid.size(); i++)     //Finally, the function does the mean of the positions
        newCentroid[i] /= nelements;
    setCentroid(cluster, newCentroid);
}

//Checks if the cluster is empty
const bool Par::emptyCluster(int cluster, vector<int> solution){
    for(int i = 0; i < nElements(); i++)
        if(solution[i] == cluster)
            return false;
    return true;
}

//Checks if there is any empty cluster
const bool Par::emptyClusters(vector<int> solution){
    bool empty;
    for(int i = 0; i < nClusters(); i++){
        empty = true;
        for(int j = 0; j < nElements(); j++)
            if(solution[j] == i){
                empty = false;
                break;
            }
        if(empty)
            return true;
    }
    return false;
}

const vector<float> Par::getCentroid(int cluster){
    return this->centroids[cluster];
}

const float Par::getDeviation(){
    float deviation = 0;
    float clusterDeviation;
    int clusterElements;
    for(int i = 0; i < nClusters(); i++){
        clusterDeviation = 0;
        clusterElements = 0;
        for(int j = 0; j < nElements(); j++)
            if(solution[j] == i){
                clusterDeviation += getDistance(this->elements[j], centroids[i]);
                clusterElements++;
            }
        deviation += clusterDeviation/clusterElements;
    }
    return deviation/centroids.size();
}

const float Par::getDeviation(vector<int> solution){
    float deviation = 0;
    float clusterDeviation;
    int clusterElements;
    for(int i = 0; i < nClusters(); i++){
        clusterDeviation = 0;
        clusterElements = 0;
        for(int j = 0; j < nElements(); j++)
            if(solution[j] == i){
                clusterDeviation += getDistance(this->elements[j], centroids[i]);
                clusterElements++;
            }
        deviation += clusterDeviation/clusterElements;
    }
    return deviation/centroids.size();
}

//Calculates the infeasibility
const int Par::getInfeasibility(){
    int infeasibility = 0;
    for(list<Restriction>::iterator it=this->restrictions.begin(); it != this->restrictions.end(); ++it)
        if((*it).a != -1 && (*it).b != -1)         //-1 Means that that position has no solution yet
            if((*it).type != (solution[(*it).a] == solution[(*it).b]))
                infeasibility++;
    return infeasibility;
}

const int Par::getInfeasibility(vector<int> solution){
    int infeasibility = 0;
    for(list<Restriction>::iterator it=this->restrictions.begin(); it != this->restrictions.end(); ++it)
        if((*it).a != -1 && (*it).b != -1)         //-1 Means that that position has no solution yet
            if((*it).type != (solution[(*it).a] == solution[(*it).b]))
                infeasibility++;
    return infeasibility;
}

const float Par::getAgregated(){
    return getDeviation(solution) + getInfeasibility(solution)*this->lambda;
}

const float Par::getAgregated(vector<int> solution){
    return getDeviation(solution) + getInfeasibility(solution)*this->lambda;
}

//Returns the solution
const vector<int> Par::getSolution(){
    return this->solution;
}

void Par::setSolution(vector <int> newSolution){
    this->solution = newSolution;
}

void Par::modifySolution(int index, int value){
    this->solution[index] = value;
}

void Par::shuffleSolution(){
    random_shuffle(this->solution.begin(), this->solution.end());
}

const int Par::nElements(){
    return this->elements.size();
}

const int Par::nClusters(){
    return centroids.size();
}

const int Par::nAtributes(){
    return this->elements[0].size();
}

void Par::setCentroid(int cluster, vector<float> elements){
    this->centroids[cluster] = elements;
}

Par& Par::operator=(const Par& other){
    if(this != &other){
        this->elements = other.elements;
        this->restrictions = other.restrictions;
        this->solution = other.solution;
        this->centroids = other.centroids;
        this->lambda = other.lambda;
    }
    return *this;
}

//Extract the data from a file
vector<vector<float>> extractElements(const char* elementsFile){
    vector<vector<float>> elements;
    string inputLine;
    string inputData;
    ifstream file(elementsFile);
    vector<float> aux;
    if(file.is_open()){
        while(file.peek() != EOF){
            getline(file, inputLine);
            stringstream input_stringstream(inputLine);
            while(input_stringstream.peek() != EOF){
                getline(input_stringstream, inputData, ',');
                aux.push_back(stof(inputData));
            }
            elements.push_back(aux);
            aux.clear();
        }
        file.close();
    }else
        cerr<<"Unable to open file"<<endl;
    return elements;
}

list<Restriction> extractRestrictions(const char* restrictionsFile){
    list<Restriction> restrictions;
    string inputLine;
    string inputData;
    ifstream file(restrictionsFile);
    Restriction aux;
    if(file.is_open()){
        aux.a = 0;
        while(file.peek() != EOF){
            getline(file, inputLine);
            stringstream input_stringstream(inputLine);
            aux.b = 0;
            while(input_stringstream.peek() != EOF){
                getline(input_stringstream, inputData, ',');
                if(aux.b > aux.a){                          //With this we avoid repeated restrictions
                    if(inputData == "1"){
                        aux.type = true;
                        restrictions.push_back(aux);
                    }
                    else if(inputData == "-1"){
                        aux.type = false;
                        restrictions.push_back(aux);
                    }
                }
                aux.b++;
            }
            aux.a++;
        }
        file.close();
    }else
        cerr<<"Unable to open file"<<endl;
    return restrictions;
}