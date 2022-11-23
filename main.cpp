#include <cstdio>
#include <omp.h>
#include <iostream>
#include "Parser.h"
#include "graph.hpp"

#include <stack>
#include <deque>



Tour BestTour;

void Graph::dfs(Tour &tour, int vertex = 0, float cost_in){
    // Bound
    if(BestTour.cost <= cost_in) return;

    tour.path.push(vertex);
    for(int i = 0; i < size; i++ ){
        if(tour.visited[i]) continue;
        tour.visited[i] = 1;

        for(int j = 0; j<size;j++){
            if(tour.visited[j]) continue;    

            dfs(tour, j, cost_in + adj[i][j]);
            //when a path is completed then i can compared it to best path
            if(tour.path.size() == this->points.size()){
                BestTour = tour;
            }
            tour.path.pop(); //BackTracking
        }

    }
}

std::vector<Point> Graph::ShortestPath(){

    Tour t;
    BestTour = Tour();
    // TODO:
    // Search for lower bound with mst?
    dfs(t, 0, INF);
    
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