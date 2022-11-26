#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "point.h"
#include "tour.h"
#include "timer.hpp"
#include "Display/display.h"
#include <vector>

#define INF 2e9;
typedef std::vector<std::vector<float>>  DistMatrix;

class Graph{
    private:
        std::vector<Point> points;
        DistMatrix adj;
        size_t size;

    public:
        Graph() = default;
        Graph(std::vector<Point> points_);
        std::stack<int> shortestPath();
        void dfs(Tour&, int, float, int);
        static void solveTSP(std::string filename, const int);
};

#endif