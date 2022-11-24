#include <cstdio>
#include <omp.h>
#include <iostream>
#include "Parser.h"
#include "graph.hpp"
#include "timer.hpp"



Tour BestTour;
float BestCost;
int thread_num = 16;
int curthreads = 0;

void Graph::dfs(Tour &tour, int vertex, float cost_in, int depth = 0){

    // Bound
    if(BestCost < cost_in) return;
    
    //when a path is completed then i can compared it to best path
    if(tour.path.size() == this->points.size() ){
        tour.path.push(0);
        for(size_t i = 0; i < size; i++ ){
            // connection back to root
            if(cost_in + adj[0][vertex] < BestCost){
                #pragma omp critical
                {
                    BestTour = tour;
                    BestCost = cost_in;
                }
            }
            
        }
    }

    for(size_t i = 0; i < size; i++ ){
        if(tour.visited[i]) continue;

        tour.path.push(i);
        tour.visited[i] = 1;

        if(depth != 0){
            dfs(tour, i, cost_in + adj[vertex][i], depth + 1);
        }
        else{
            #pragma omp task default(none) shared(BestTour, BestCost) firstprivate(i,tour,vertex,depth, cost_in)
            {
                dfs(tour, i, cost_in + adj[vertex][i], depth+1);
            }
        }

        tour.path.pop();
        tour.visited[i] = 0;
    }

}

std::vector<Point> Graph::ShortestPath(){

    Tour t;
    BestTour = Tour();
    BestCost = INF;
    std::vector<Point> result;
    // TODO:
    // Search for lower bound with mst?
    t.path.push(0);
    t.visited[0] = 1;

    #pragma omp parallel default(none) shared(BestTour, BestCost) firstprivate(t) num_threads(16)
    {
        #pragma omp single
        dfs(t, 0, 0);
        #pragma omp taskwait
    }
    auto st = BestTour.path;
    while(!st.empty()) {
        // std::cout << st.top()<<" ";
        result.push_back(points[st.top()]);
        st.pop();
    }

    
    return result;
}

int main(){
    std::string filename;
    
    std::cin>>filename>>thread_num;

    auto ifPoints = Parse(filename);
    if(ifPoints){
        auto points = ifPoints.value();
        std::cout<< "Points:"<< points.size()<<'\n';
        Graph g(points);
        {  
            Timer t("");            
            g.ShortestPath();
        }

        
    }
    return 0;
}