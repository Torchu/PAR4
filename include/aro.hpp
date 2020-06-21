#include "par.hpp"
class ARO{
    private:
        int MAX_ITERATIONS;
        Par instance;
    public:
        ARO(Par instance, int max_iter);
        void generateSolution();
        vector<int> generateBud(vector<int> solution);
        vector<int> generateLarva(vector<int> solution);
        vector<int> reparation(vector<int> solution);
        const vector<int> getSolution();
        const float getDeviation();
        const int getInfeasibility();
        const float getAgregated();
};

vector<int> random_selection(int k, int n);