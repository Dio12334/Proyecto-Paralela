#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <vector>
#include "Parser.h"

class Graph{

    private:
    typedef std::vector<std::vector<float>>  DistMatrix;
    std::vector<Point> points;
    DistMatrix adj;

    
    public:
    Graph() = default;

    Graph(std::vector<Point> points_): points(points_), adj(points.size(), std::vector<float>(points.size(),0)){
        
        for(size_t u = 0;u < points.size(); u++){
            for(size_t v = 0; v < points.size(); v++){
                adj[u][v] = adj[v][u] = Point::dist(points[u] , points[v]);
            }
        }
    }

    std::vector<Point> ShortestPath();
      
};

#endif