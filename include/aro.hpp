#include "par.hpp"
class ARO{
    private:
        int MAX_EVALUATIONS;
        Par instance;
    public:
        ARO(Par instance, int max_eval);
        void generateSolution();
        vector<int> generateBud();
        vector<int> generateLarva();
        vector<int> reparation(vector<int> solution);
        const vector<int> getSolution();
        const float getDeviation();
        const int getInfeasibility();
        const float getAgregated();
};