#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <optional>
#include <math.h>

struct Point{
    unsigned int x, y ,z;
    
    static float dist(const Point& p1, const Point& p2){
        return   std::sqrt( (p1.x - p2.x) *  (p1.x - p2.x) +
                (p1.y - p2.y) *  (p1.y - p2.y) +
                (p1.z - p2.z) *  (p1.z - p2.z) );
    }
};
std::optional<std::vector<Point>> Parse(std::string fileName);

#endif