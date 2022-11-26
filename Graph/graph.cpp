#include "graph.h"
#include <iostream>
#include <omp.h>

Tour BestTour;
float BestCost;
int root = 0;
int thread_num = 0;

Graph::Graph(std::vector<Point> points_):
points(points_), adj(points.size(), std::vector<float>(points.size(),0)){
    size = points.size();
    for(size_t u = 0;u < points.size(); u++){
        for(size_t v = 0; v < points.size(); v++){
            adj[u][v] = adj[v][u] = Point::dist(points[u] , points[v]);
        }
    }
}

void Graph::dfs(Tour &tour, int vertex, float cost_in, int depth = 0){
    if(BestCost < cost_in) return;

    //when a path is completed, its cost is compared to the current best
    if(depth == this->points.size() - 1){
        tour.path.push(root);
        if(cost_in + adj[vertex][root] < BestCost){
            #pragma omp critical
            {
                    BestTour = tour;
                    BestCost = cost_in + adj[vertex][root];
            }
        }
        tour.path.pop();
        return;
    }

    for(size_t i = 0; i < size; i++ ){
        if(tour.visited[i]) continue;

        tour.path.push(i);
        tour.visited[i] = 1;

        if(depth != 0){
            dfs(tour, i, cost_in + adj[vertex][i], depth + 1);
        }
        else{
            #pragma omp task default(none) shared(BestTour, BestCost) firstprivate(i,tour,vertex,depth, cost_in, root)
            {
                dfs(tour, i, cost_in + adj[vertex][i], depth+1);
            }
        }

        tour.path.pop();
        tour.visited[i] = 0;
    }
}

std::stack<int> Graph::shortestPath(){
    Tour t;
    BestTour = Tour();
    BestCost = INF;
    std::vector<Point> result;

    t.path.push(root);
    t.visited[root] = 1;

    #pragma omp parallel default(none) shared(BestTour, BestCost) firstprivate(t,root) num_threads(thread_num)
    {
        #pragma omp single
        dfs(t, root, 0);
        #pragma omp taskwait
    }

    return BestTour.path;
}

void Graph::solveTSP(std::string filename, const int th){
    std::string path = "../DataSets/";
    int r;
    auto ifPoints = parseFromFile(path + filename, r);

    if(!ifPoints) {
        std::cout << "\n[ERR] No points could be proccesed from DataSets/" + filename;
        return;
    }

    root = r;
    thread_num = th;
    auto points = ifPoints.value();
    std::cout << "\nPOINTS IN " << filename << ": " << points.size() << '\n';
    std::stack<int> bestPath;
    Graph g(points);

    {  
        Timer t("");            
        bestPath = g.shortestPath();
    }

    std::vector<Point> res;
    std::cout << "\nPATH: ";
    while(!bestPath.empty()) {
        std::cout << bestPath.top() << " ";
        res.push_back(points[bestPath.top()]);
        bestPath.pop();
    }

    float cost = 0;
    for(int i = 0; i < res.size() - 1; i++ ){
        cost +=  Point::dist( res[i] , res[i+1]);   
    }

    std::cout<<"\nCOST (calc from the shortest path): "<< cost;
    std::cout<<"\nTSP-COST (calc from actual TSP algorithm): " << BestCost << '\n';

    Display display(res);
    display.run();
}