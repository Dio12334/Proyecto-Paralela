#include <cstdio>
#include <omp.h>
#include <iostream>
#include "Parser.h"
#include "graph.hpp"

std::vector<Point> Graph::ShortestPath(){

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