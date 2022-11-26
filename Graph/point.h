#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
#include <optional>
#include <tgmath.h>

struct Point{
    unsigned int id, x, y;
    
    static float dist(const Point& p1, const Point& p2);
};

std::optional<std::vector<Point>> parseFromFile(std::string fileName, int& r, bool verbose = false);

#endif