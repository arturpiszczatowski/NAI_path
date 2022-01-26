#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <list>


using namespace std;

#define INF ((int)(1 << (8 * sizeof(int) - 3)))

using graph = vector<vector<int>>;
using road_with_score = pair<vector<int>, int>;

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

road_with_score dijkstra(graph g, int given_initial_node, int given_final_node){

    int e = INF;


    vector<int> uncharted_nodes;

    list<road_with_score> all_roads;
    road_with_score current_road;
    road_with_score best_road;

    vector<pair<int, vector<int>>> every_node_connections;

    for(int i=0; i < g[0].size(); i++){
        int initial_node = i;
        vector<int> available_nodes;
        for(int j=0; j < g[0].size(); j++) {
            if(g[i][j] != e && g[i][j] >= 1){
                available_nodes.push_back(j);
            }
        }
        pair<int, vector<int>> connection = {initial_node, available_nodes};
        every_node_connections.push_back(connection);
    }


    for(auto node_connection : every_node_connections){
         vector<pair<int, vector<int>>> buffer_connections = every_node_connections;
         vector<int> current_path;
         int lowest_node;
         int total_cost = 0;

         vector<int> visited_nodes;

         int initial_node = node_connection.first;
         vector<int> available_nodes = node_connection.second;

         visited_nodes.push_back(initial_node);

         remove(buffer_connections.begin(), buffer_connections.end(), node_connection);

         current_path.push_back(initial_node);

         while(!buffer_connections.empty() && !available_nodes.empty()){
             int cost = 0;
             for(int available_node : available_nodes){
                 int lowest_cost = e;
                 if(g[initial_node][available_node] < lowest_cost){
                     lowest_cost = g[initial_node][available_node];
                     lowest_node = available_node;
                     cost = lowest_cost;
                 }
             }
             current_path.push_back(lowest_node);
             visited_nodes.push_back(lowest_node);
             initial_node=lowest_node;
             total_cost += cost;
             available_nodes = every_node_connections[initial_node].second;

             for(int visited : visited_nodes){
                 available_nodes.erase(remove(available_nodes.begin(), available_nodes.end(), visited), available_nodes.end());
             }

             node_connection = every_node_connections[initial_node];
             remove(buffer_connections.begin(), buffer_connections.end(), node_connection);
         }

         road_with_score new_road = {current_path, total_cost};
         all_roads.push_back(new_road);
    }


    for(auto road : all_roads) {
        cout << "Road: {";
        for (int node: road.first) {
            cout << node << " ";
        }
        cout << "}" << endl;
        cout << "Cost:" << road.second << endl;
    }


    return best_road;

}


int main(int argc, char **argv) {

    int e = INF;

//    loadAndGenerateGraphviz(argv[1]);

    graph g = {
            {0, 1, e, e, 1},
            {1, 0, 3, 1, e},
            {e, 3, 0, 1, e},
            {e, 1, 1, 0, 1},
            {1, e, e, 1, 0}};


    road_with_score best = dijkstra(g, 1, 2);

    cout << "Road: {";
    for(int node : best.first) {
        cout << node << " ";
    }
    cout << "}" << endl;
    cout << "Cost:" << best.second;


    return 0;
}
