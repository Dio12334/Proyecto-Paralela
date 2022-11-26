#include "point.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>

float Point::dist(const Point& p1, const Point& p2){
    return std::sqrt((p1.x - p2.x) *  (p1.x - p2.x) + (p1.y - p2.y) *  (p1.y - p2.y));
}

std::optional<std::vector<Point>> parseFromFile(std::string fileName, int& r, bool verbose){
    std::string path = "./DataSets/";
    std::fstream file(path + fileName);

    if(file.is_open()){
        std::string line;
        int points_num = 0;

        // Metadata: 1st line is the name of the file, 2nd the starting point and 3rd is the number of points
        std::getline(file, line);
        std::getline(file, line);
        r = stoi(line);
        std::getline(file, line);
        points_num = stoi(line);

        std::vector<Point> points; 
        points.reserve(points_num);

        while(std::getline(file, line)){
            std::istringstream record(line);
            Point point;
            record >> point.id >> point.x >> point.y;
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
