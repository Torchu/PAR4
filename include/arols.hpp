#include "par.hpp"
class AROLS{
    private:
        int MAX_EVALUATIONS;
        int INTERVAL;
        int MAX_FAILS;
        Par instance;
    public:
        AROLS(Par instance, int max_eval, int k, int max_fails);
        void generateSolution();
        int BLS();
        vector<int> generateBud(vector<int> solution);
        vector<int> generateLarva(vector<int> solution);
        vector<int> reparation(vector<int> solution);
        const vector<int> getSolution();
        const float getDeviation();
        const int getInfeasibility();
        const float getAgregated();
};