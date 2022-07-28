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

#include <bits/stdc++.h>

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
            : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor>> Graph;


void DijkstraComputePaths(vertex_t source, const Graph &graph, std::vector<weight_t> &min_distance, std::vector<vertex_t> &previous);


std::list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t> &previous);

void createEdge(Graph &graph, int u, int v, double w);

void createNode(Graph &graph);

void createNodes(Graph &graph, int n);

double determineA(Graph &graph, std::vector<int> &Ui, std::vector<std::vector<double>> &distances);

std::vector<std::vector<double>> initiate_d_bars(Graph &graph);

std::vector<std::vector<double>> initiate_distances(Graph &graph);

std::vector<std::vector<double>> update_distances(Graph &graph, std::vector<std::vector<double>> &distances);

/*
void update_d_bars(Graph & graph, std::vector<std::vector<double>> &d_bars, int r)
{
    double sum = 0;
    int u = graph.size()-1;
    d_bars.push_back(std::vector<double>());
    //std::cout << "HEY IT'S ME :" << graph[u][0].weight << std::endl;
    for(int i = 0; i < graph.size()-1; i++){
        //neighbor n = graph[u][i];
        sum = 0;
        for(int j = 0; j < r; j++) {
            neighbor n2 = graph[u][j];
            if(u == n2.target){
                //std::cout << "TEMP0 d_bar[" << n.target << "][" << n2.target << "] = " << d_bars[n.target][n2.target] << std::endl;
            }
            else {
                sum += d_bars[i][n2.target];
                //std::cout << "TEMP d_bar[" << n.target << "][" << n2.target << "] = " << d_bars[n.target][n2.target << std::endl;
            }
        }
        sum = sum/r + graph[u][0].weight;

        d_bars[u].push_back(sum);
        d_bars[i].push_back(sum);
        //std::cout << "d_bar[" << graph.size()-1 << "][" << i << "] = " << sum << std::endl;
    }
    d_bars[u].push_back(0);




}
*/

void update_d_bars(Graph &graph, std::vector<std::vector<double>> &d_bars, int r);

   
double determine_max(std::vector<std::vector<double>> &d_bars, std::vector<std::vector<double>> &distances, double current_max);

double determine_min(std::vector<std::vector<double>> &d_bars, std::vector<std::vector<double>> &distances, double current_min);

void determine_neighbors(std::vector<int> &Ui, int r, int V);

void grow_r_DecomposableGraph(Graph &graph, int r, std::vector<std::vector<double>> &distances);
    

