#include <cstdio>
#include <omp.h>
#include <iostream>
#include "Parser.h"
#include "graph.hpp"

#include <stack>
#include <deque>

#define N 20

struct Tour{
    std::stack<int> path;    
    bool visited[N];
    float cost;
};


int best_cost;

void Graph::dfs(Tour tour, int cost_in){
    
    if(best_cost <= cost_in) return;
    for(int i = 0; i < size; i++ ){
        if(vist_path[i]) continue;
        
        vist_path[i] = 1;

        for(int j = 0; j<size;j++){
            if(vist_path[j]) continue;    
            dfs(, cost_in + adj[i][j]);
        }



    }
}

std::vector<Point> Graph::ShortestPath(){

    bool vis[points.size()] = {};
    int best_cost = INF;

    
    return {};
}

int main(){
    auto ifPoints = Parse("xqf131.tsp");
    if(ifPoints){
        auto points = ifPoints.value();
        std::cout<< points.size()<<'\n';
        Graph g(points);
    }
    return 0;
}