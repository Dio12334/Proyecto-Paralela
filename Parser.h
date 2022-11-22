#include <string>
#include <vector>
#include <optional>

struct Point{
    unsigned int x, y ,z;
};

std::optional<std::vector<Point>> Parse(std::string fileName);