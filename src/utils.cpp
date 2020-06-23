#include "utils.hpp"
#include <time.h>
#include <algorithm>

//Choose k numbers from [0, n) without repeating
vector<int> random_selection(int k, int n){
    vector<int> range, selected;
    int position;
    for(int i = 0; i < n; i++)
        range.push_back(i);
    for(int i = 0; i < k; i++){
        position = rand()%range.size();
        selected.push_back(range[position]);
        range.erase(range.begin()+position);
    }
    return selected;
}