#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <ctime>
#include <limits> // for numeric_limits
#include <stdlib.h>
#include <chrono>
#include <random>
#include <iostream>
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include "functions.h"
#include <bits/stdc++.h>


int main()
{
    // remember to insert edges both ways for an undirected graph
    int r = 3;
    bool end = false;
    srand(time(NULL));


    //std::vector<double> datamax;
    //std::vector<double> datamin;
    //datamax.push_back((double)1/3);//first max is always 1
    //datamin.push_back((double )1/3);
    while(!end){
        Graph graph(0);
        createNodes(graph, 3);
        createEdge(graph, 0, 1, 1);
        createEdge(graph, 1, 2, 1);

        std::vector<std::vector<double>> d_bars = initiate_d_bars(graph);
        std::vector<std::vector<double>> distances = initiate_distances(graph);
        std::vector<double> datamax;
        std::vector<double> datamin;
        datamax.push_back((double)1/3);//first max is always 1
        datamin.push_back((double )1/3);
        for(int i = 0; i<1000; i++){
            grow_r_DecomposableGraph(graph, r, distances);
            update_d_bars(graph, d_bars, r);
            update_distances(graph, distances);
            datamax.push_back(determine_max(d_bars, distances, datamax[i]));

            datamin.push_back(determine_min(d_bars, distances, datamin[i]));
            //std::cout << "RANK -> " << i << std::endl;
            std::cout << i << " ---- " << datamin[i] << "*d < d_bar < " << datamax[i] << "*d" << std::endl ;
            if (datamax[i] > 1){
                end = true;
                break;
            }
            //for(int i = 0;i<d_bars[3].size();i++){
            //    std::cout << "D_bars[3][" << i << "]" << d_bars[3][i] << std::endl;
            //}

        }

    }
    /*std::cout << " DATA " << std::endl;
    std::fstream file;
    file.open("vector_file_2.txt",std::ios_base::out);

    typedef std::vector<double>::iterator dubIter;
    std::vector<double>::iterator itr;

    for(std::pair<dubIter, dubIter> i(datamax.begin(), datamin.begin()); i.first != datamax.end() ; ++i.first, ++i.second)
    {
        file<<(*i.first)<<";"<<(*i.second)<<std::endl;
    }

    file.close();
    */
    return 0;

    /*
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    DijkstraComputePaths(0, graph, min_distance, previous);
    std::cout << "Distance from 0 to 4: " << min_distance[4] << std::endl;
    std::list<vertex_t> path = DijkstraGetShortestPathTo(4, previous);
    std::cout << "Path : ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;
    */

}
