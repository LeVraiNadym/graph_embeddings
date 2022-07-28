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


void DijkstraComputePaths(vertex_t source,
                          const Graph &graph,
                          std::vector<weight_t> &min_distance,
                          std::vector<vertex_t> &previous)
{
    int n = graph.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
        const std::vector<neighbor> &neighbors = graph[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) {
                vertex_queue.erase(std::make_pair(min_distance[v], v));

                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(std::make_pair(min_distance[v], v));

            }

        }
    }
}


std::list<vertex_t> DijkstraGetShortestPathTo(
        vertex_t vertex, const std::vector<vertex_t> &previous)
{
    std::list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}

void createEdge(Graph &graph, int u, int v, double w)
{
    graph[u].push_back(neighbor(v, w));
    graph[v].push_back(neighbor(u, w));
}

void createNode(Graph &graph)
{
    graph.push_back(std::vector<neighbor>());
}
void createNodes(Graph &graph, int n)
{
    for (int i = 0; i < n; i++)
        graph.push_back(std::vector<neighbor>());
}

double determineA(Graph &graph, std::vector<int> &Ui, std::vector<std::vector<double>> &distances)
{
    int n = Ui.size();
    double maxElement = 0;

    for(int i=0; i<n; i++){
        //std::vector<weight_t> min_distance;
        //std::vector<vertex_t> previous;
        //DijkstraComputePaths(Ui[i], graph, min_distance, previous);
        for(int j=i+1; j<n; j++){

            if(maxElement < distances[Ui[i]][Ui[j]])
                maxElement = distances[Ui[i]][Ui[j]];
        }
    }

    //int maxElementIndex = std::max_element(distances.begin(),distances.end()) - distances.begin();
    //double maxElement = *std::max_element(dist.begin(), dist.end());

    return maxElement/2;
}

std::vector<std::vector<double>> initiate_d_bars(Graph &graph){
    int n = graph.size();
    std::vector<std::vector<double>> d_bars ;
    for(int i = 0; i<n ; i++){
        d_bars.push_back(std::vector<double>());
        std::vector<weight_t> min_distance;
        std::vector<vertex_t> previous;
        DijkstraComputePaths(i, graph, min_distance, previous);
        for(int j = 0; j<n; j++){
            //std::cout << "Distance from " << i << " to " << j << " : " << min_distance[j] << std::endl;
            d_bars[i].push_back(min_distance[j]/3);
        }
    }
    //std::cout << "I AM THE SIZE   " << d_bars.size() << std::endl;
    return d_bars;
}

std::vector<std::vector<double>> initiate_distances(Graph &graph){
    int n = graph.size();
    std::vector<std::vector<double>> distances;
    for(int i = 0; i<n ; i++){
        distances.push_back(std::vector<double>());
        std::vector<weight_t> min_distance;
        std::vector<vertex_t> previous;
        DijkstraComputePaths(i, graph, min_distance, previous);
        for(int j = 0; j<n; j++){
            //std::cout << "Distance from " << i << " to " << j << " : " << min_distance[j] << std::endl;
            distances[i].push_back(min_distance[j]);
        }
    }

    return distances;
}

std::vector<std::vector<double>> update_distances(Graph &graph, std::vector<std::vector<double>> &distances){
    int u = graph.size() - 1;
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    DijkstraComputePaths(u, graph, min_distance, previous);
    distances.push_back(std::vector<double>());
    for(int j = 0; j<u+1; j++){
        //std::cout << "Distance from " << u << " to " << j << " : " << min_distance[j] << std::endl;
        distances[u].push_back(min_distance[j]);
    }
    for(int j = 0; j<u; j++) {
        distances[j].push_back(min_distance[j]);
    }


    return distances;
}

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

void update_d_bars(Graph &graph, std::vector<std::vector<double>> &d_bars, int r)
{
    double sum = 0;
    double minus = 0;
    int u = graph.size()-1;
    d_bars.push_back(std::vector<double>());
    //std::cout << "HEY IT'S ME :" << graph[u][0].weight << std::endl;

    for(int j = 0; j < r; j++) {
        neighbor n1 = graph[u][j];
        for (int k = j + 1; k < r; k++) {
            neighbor n2 = graph[u][k];
            minus += d_bars[n1.target][n2.target];
            //std::cout << "TEMP d_bar[" << n1.target << "][" << n2.target << "] = " << d_bars[n1.target][n2.target] << std::endl;
            //minus = 0;
        }
    }
    for(int i = 0; i < graph.size()-1; i++){
        //neighbor n = graph[u][i];
        sum = 0;
        for(int j = 0; j < r; j++) {
            neighbor n3 = graph[u][j];
            if(u == n3.target){
                //std::cout << "TEMP0 d_bar[" << n.target << "][" << n2.target << "] = " << d_bars[n.target][n2.target] << std::endl;
            }
            else {
                sum += d_bars[i][n3.target];

                //std::cout << "TEMP d_bar[" << i << "][" << n3.target << "] = " << d_bars[i][n3.target] << std::endl;
                }
        }



        sum = sum/r + graph[u][0].weight/3 - minus/18;
        if (graph[u][0].weight/3 < minus/18){
            std::cout << "Ohh nooo a/3 =" << graph[u][0].weight << " and minus/18 = " << minus/18 << " ! It's not good :(" << std::endl;
        }
        d_bars[u].push_back(sum);
        d_bars[i].push_back(sum);
        //std::cout << "d_bar[" << graph.size()-1 << "][" << i << "] = " << sum << std::endl;
    }
    d_bars[u].push_back(0);


}
double determine_max(std::vector<std::vector<double>> &d_bars, std::vector<std::vector<double>> &distances, double current_max){
    int n = d_bars.size();
    int u = d_bars.size()-1;
    double max = current_max;
    double tmp;
    //int ind_i;
    //int ind_j;
    /*
    for(int i = 0; i<3 ; i++){

        if(max <= (tmp = d_bars[u][graph[u][i].target]/distances[u][graph[u][i].target])){
            max = tmp;
        }
    }
    */
    for(int i = 0; i<u ; i++){
        //std::cout << "Ratio for (" << i << "," << j << ") : " << d_bars[i][j] << "/" << distances[i][j] << " = " << tmp << std::endl;
         if(max <= (tmp = d_bars[u][i]/distances[u][i])){
            //std::cout << "Oh, a new max at point (" << i << "," << j << ")! " << d_bars[i][j] << "/" << distances[i][j] << " = " << tmp << std::endl;
            max = tmp;
            //ind_i = i;
            //ind_j = u;
        }
    }
    //std::cout << "MAX : (" << ind_i << "," << ind_j << ")! " << d_bars[ind_i][ind_j] << "/" << distances[ind_i][ind_j] << " = " << max << std::endl;
    return max;
}

double determine_min(std::vector<std::vector<double>> &d_bars, std::vector<std::vector<double>> &distances, double current_min){
    //int n = d_bars.size();
    int u = d_bars.size()-1;
    double min = current_min;
    double tmp;
    //int ind_i;
    //int ind_j;
    for(int i = 0; i<u ; i++){
        //std::cout << "Ratio for (" << i << "," << j << ") : " << d_bars[i][j] << "/" << distances[i][j] << " = " << tmp << std::endl;
        if(min >= (tmp = d_bars[u][i]/distances[u][i])){
            //std::cout << "Oh, a new max at point (" << i << "," << j << ")! " << d_bars[i][j] << "/" << distances[i][j] << " = " << tmp << std::endl;
            min = tmp;
            //ind_i = i;
            //ind_j = u;
        }
    }
    //std::cout << "MAX : (" << ind_i << "," << ind_j << ")! " << d_bars[ind_i][ind_j] << "/" << distances[ind_i][ind_j] << " = " << max << std::endl;
    return min;
}

void determine_neighbors(std::vector<int> &Ui, int r, int V){

    for(int i = 0; i<r ; i++){
        Ui.push_back(rand() % V);
    }
    bool tmp = false;
    for (int i = 0; i<r; i++) {
        tmp = tmp || std::count(Ui.begin(), Ui.end(), Ui[i]) > 1;
    }
    if(!tmp){
        return;
    }




    while(true){
        for(int i = 0; i<r ; i++){
            Ui[i] = rand() % V;
        }
        bool tmp = false;
        for (int i = 0; i<r; i++) {
            tmp = tmp || std::count(Ui.begin(), Ui.end(), Ui[i]) > 1;
        }
        if(!tmp){
            return;
        }
    }
    return;
}
void grow_r_DecomposableGraph(Graph &graph, int r, std::vector<std::vector<double>> &distances){
    std::vector<int> numbers;
    std::vector<int> neighbours;
    std::vector<int> Ui;

    int V = graph.size();


    determine_neighbors(Ui, r, V);

    double a = determineA(graph, Ui, distances);
    createNode(graph);
    for(int i=0; i<r; i++) {
        createEdge(graph, Ui[i], V, a);
        //std::cout << "neighbors of " << graph.size() - 1 << " : " << Ui[i] << std::endl;
    }
}


