#include <cstdio>
#include <omp.h>
#include <iostream>
#include "Parser.h"
#include "graph.hpp"




Tour BestTour;
float BestCost;

void Graph::dfs(Tour &tour, int vertex, float cost_in, int depth = 0){
    
    // Bound
    if(BestCost < cost_in or tour.path.size() == this->points.size() ) return;

    for(size_t i = 0; i < size; i++ ){
        if(tour.visited[i]) continue;

        tour.path.push(i);
        tour.visited[i] = 1;

        if(){
            dfs(tour, i, cost_in + adj[vertex][i]);
        }
        else{
            #pragma omp task default(none) shared(first, middle1) firstprivate(lv, num_threads){
                auto ltour = tour;
                dfs(ltour, i, cost_in + adj[vertex][i]);
        }
        //when a path is completed then i can compared it to best path
        if(tour.path.size() == this->points.size() && cost_in < BestCost ){
            // printf("%f, %f\n", cost_in, BestTour.cost);
            BestTour = tour;
            BestCost = cost_in;
        }
        tour.path.pop();
        tour.visited[i] = 0;
    }

}

std::vector<Point> Graph::ShortestPath(){

    Tour t;
    BestTour = Tour();
    BestCost = INF;
    // TODO:
    // Search for lower bound with mst?
    t.path.push(0);
    t.visited[0] = 1;
    dfs(t, 0, 0);

    auto st = BestTour.path;
    while(!st.empty()) {
        std::cout << st.top()<<" ";
        st.pop();
    }

    
    return {};
}

int main(){
    auto ifPoints = Parse("xqf131.tsp");
    if(ifPoints){
        auto points = ifPoints.value();
        std::cout<< points.size()<<'\n';
        Graph g(points);

        g.ShortestPath();
    }
    return 0;
}