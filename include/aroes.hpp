#include "par.hpp"
class AROES{
    private:
        Par instance;
        int MAX_EVALUATIONS;
        float temperature;
        float FINAL_TEMPERATURE;
        int MAX_NEIGHBOURS;
        int MAX_SUCCESS;
        float BETA;
    public:
        AROES(Par instance, float ftemp, int max_eval);
        void generateSolution();
        vector<int> generateBud(vector<int> solution);
        vector<int> generateLarva(vector<int> solution);
        vector<int> reparation(vector<int> solution);
        const vector<int> getSolution();
        const float getDeviation();
        const int getInfeasibility();
        const float getAgregated();
};