#include "Graph/graph.h"
#include <cstdio>
#include <iostream>

int main(){
    std::string filename;
    int thread_num;
    std::cin >> filename >> thread_num;
    Graph::solveTSP(filename, thread_num);

    return 0;
}