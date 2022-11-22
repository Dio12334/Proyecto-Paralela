#include <cstdio>
#include <omp.h>
#include <iostream>
#include "Parser.h"


int main(int argc, char* argv[]){
    auto ifPoints = Parse("xqf131.tsp");
    if(ifPoints){
        auto points = ifPoints.value();
        for(auto point: points){
            std::cout << point.x << " " << point.y << " " << point.z << "\n";
        }
    }
    return 0;
}