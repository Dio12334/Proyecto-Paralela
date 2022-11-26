#ifndef TOUR_H
#define TOUR_H

#include <stack>
#define N 40

struct Tour{
    std::stack<int> path;    
    bool visited[N] = {};
    float cost = 0;
};

#endif