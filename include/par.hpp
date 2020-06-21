#ifndef PAR_H
#define PAR_H

#include<vector>
#include <list>
using namespace std;

//The two integers are the indexes of the elements and the bool is false if they can't be in the same group or true if they must be in the same group
struct Restriction{
    int a;
    int b;
    bool type;
};

class Par{
    private:
        vector<vector<float>> elements;                            
        list<Restriction> restrictions;                                                                      
        vector<int> solution;                                      
        vector<vector<float>> centroids;  
        float lambda;
    public:
        Par(int clusters, vector<vector<float>> elements, list<Restriction> restrictions);
        Par(const Par& other);      //New copy constructor
        Par();                      //New default constructor
        const float getLongestDistance();
        const float getDistance(vector<float> a, vector<float> b);                           
        void computeCentroid(int cluster);                         
        const bool emptyCluster(int cluster, vector<int> solution);
        const bool emptyClusters(vector<int> solution);
        void setSolution(vector <int> newSolution);
        void modifySolution(int index, int value);
        void shuffleSolution();
        const vector<float> getCentroid(int cluster);
        void setCentroid(int cluster, vector<float> elements);
        const float getDeviation();                    
        const float getDeviation(vector<int> solution);
        const int getInfeasibility();
        const int getInfeasibility(vector<int> solution);
        const vector<int> getSolution();
        const float getAgregated();
        const float getAgregated(vector<int> solution);
        const int nElements();
        const int nClusters();
        const int nAtributes();
        Par& operator=(const Par& other);
};

vector<vector<float>> extractElements(const char* elementsFile);
list<Restriction> extractRestrictions(const char* restrictionsFile);

#endif