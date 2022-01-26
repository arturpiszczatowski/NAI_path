#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>


using namespace std;

#define INF ((int)(1 << (8 * sizeof(int) - 3)))

using graph = vector<vector<int>>;

graph loadGraph(string fileName)
{
    ifstream inputfile(fileName);
    graph result;

    while (!inputfile.eof())
    {
        int first_node;
        int second_node;
        int cost;

        inputfile >> first_node;
        inputfile >> second_node;
        inputfile >> cost;

        vector<int> edge;
        edge.push_back(first_node);
        edge.push_back(second_node);
        edge.push_back(cost);

        result.push_back(edge);
    }

    result.pop_back();
    return result;
}

void generateGraph(graph g, ofstream &output){
    output << "graph {" << endl;

    for(int i=0; i<g.size(); i++){
        output << g[i][0] << " -- " << g[i][1]  << " [ label = " << g[i][2] << " ]" << endl;
    }

    output << "}";
}

//graph convertIncidentToDot(graph g){
//    graph dot_g;
//    int connections = g[0].size();
//    int nodes = g.size();
//
//    for(int i=0; i<nodes; i++){
//        for(int j=0; j<connections; j++){
//            if(g[j][i] == 1){
//                dot_g[i].push_back(j+1);
//            }
//        }
//    }
//
//    return dot_g;
//}

//graph convertNeighbourToDot(graph g){
//    graph dot_g;
//    int nodes = g.size();
//    int connections = 0;
//
//    for(int i=0; i<nodes; i++){
//        for(int j=0; j<nodes; j++){
//            if(g[i][j] == 1){
//                connections++;
//            }
//        }
//    }
//
//    int row = 0;
//    while(row<connections){
//        for(int j=0; j<nodes; j++){
//            for(int k=0; k<nodes; k++){
//                if(g[j][k] == 1){
//                    dot_g[row][0] = j+1;
//                    dot_g[row][1] = k+1;
//                    row++;
//                }
//            }
//        }
//    }
//
//    return dot_g;
//}

void loadAndGenerateGraphviz(string fileName){
    graph inputGraph = loadGraph(fileName);
    ofstream output ("result.txt");
    generateGraph(inputGraph, output);
}

int findShortestDistance(vector<int> distance, vector<bool> visited)
{
    int shortest_distance=INF;
    int closest_node;

    for(int k=0;k<distance.size();k++)
    {
        if(distance[k] <= shortest_distance && visited[k] == false)
        {
            shortest_distance=distance[k];
            closest_node=k;
        }
    }
    return closest_node;
}

void Dijkstra(graph g, int initial_node)
{
    vector<int> total_distance; // // array to calculate the minimum total_distance for each node
    vector<bool> visited;// boolean array to mark visited and unvisited for each node

    vector<pair<int, vector<int>>> shortest_paths;
    vector<int> current_path;


    for(int k = 0; k<g[0].size(); k++)
    {
        total_distance.push_back(INF);
        visited.push_back(false);
        shortest_paths.push_back(make_pair(k, current_path));
    }

    total_distance[initial_node] = 0;

    for(int i = 0; i < g[0].size(); i++)
    {
        int closest_node= findShortestDistance(total_distance, visited);
        visited[closest_node]=true;

        for(int j = 0; j < g[0].size(); j++)
        {
            if(!visited[j] && g[closest_node][j] && total_distance[closest_node] != INF && total_distance[closest_node] + g[closest_node][j] < total_distance[j]) {
                total_distance[j] = total_distance[closest_node] + g[closest_node][j];

                if((find(shortest_paths[j].second.begin(), shortest_paths[j].second.end(), closest_node) == shortest_paths[j].second.end())) {
                    shortest_paths[j].second.push_back(closest_node);
                }
            }
        }
    }

    cout << "Initial node: " << initial_node << endl;
    cout << "Shortest paths to other nodes: " << endl;

    for(auto path : shortest_paths)
    {
        path.second.push_back(path.first);

        if(path.first == initial_node) {
            cout << "Node: " << path.first << " => Initial node" << endl;
            continue;
        }
        cout << "Node: " << path.first << " => Path: {";
        for(int node : path.second){
            if(node==initial_node){
                continue;
            }
            cout << " " << node << " ";
        }
        cout << "} => Total distance: " << total_distance[path.first] << endl;
    }
}



int main(int argc, char **argv) {

//    loadAndGenerateGraphviz(argv[1]);

    graph g={
            {0, 1, 2, 0, 0, 0},
            {1, 0, 0, 5, 1, 0},
            {2, 0, 0, 2, 3, 0},
            {0, 5, 2, 0, 2, 2},
            {0, 1, 3, 2, 0, 1},
            {0, 0, 0, 2, 1, 0}};

    Dijkstra(g, 3);


    return 0;
}
