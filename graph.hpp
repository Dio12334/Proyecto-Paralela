#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <vector>
#include <stack>
#include <deque>

#include "Parser.h"


#define N 20

const int INF = 2e9;

struct Tour{
    std::stack<int> path;    
    bool visited[N] = {};
    float cost = 0;
};


class Graph{

    private:
    typedef std::vector<std::vector<float>>  DistMatrix;
    std::vector<Point> points;
    DistMatrix adj;
    size_t size;

    
    public:
    Graph() = default;

    Graph(std::vector<Point> points_): points(points_), adj(points.size(), std::vector<float>(points.size(),0)){
        size = points.size();
        for(size_t u = 0;u < points.size(); u++){
            for(size_t v = 0; v < points.size(); v++){
                adj[u][v] = adj[v][u] = Point::dist(points[u] , points[v]);
                // printf("%d, %d, %f\n", u, v, adj[u][v]);
            }
        }
    }

    std::vector<Point> ShortestPath();
    void dfs(Tour&, int, float, int);
      
};

#endif