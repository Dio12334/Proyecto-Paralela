#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>

std::optional<std::vector<Point>> Parse(std::string fileName, bool verbose){
    std::string path = "./DataSets/";
    std::fstream file(path + fileName);

    if(file.is_open()){
        std::vector<Point> points; 
        points.reserve(662); // Max number of points is 662 in current dataset
        std::string line;

        // First 8 lines are trash
        for(int i = 0; i < 8; ++i)
            std::getline(file, line);

        while(std::getline(file, line)){
            
            std::istringstream record(line);
            Point point;
            record >> point.z >> point.x >> point.y;
            points.push_back(point);
        }

        file.close();
        points.pop_back();

        if(verbose) std::clog << "File " << path + fileName << " read successfully\n";
        return points;
    }
    else{
        if(verbose) std::cerr << "File " << path + fileName << " not found\n";
        return {};
    }
}
