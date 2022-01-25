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

road_with_score dijkstra(graph g, int initial_node, int final_node){

    int e = INF;

    vector<int> visited_nodes;
    vector<int> available_nodes;
    vector<int> uncharted_nodes;

    list<road_with_score> all_roads;
    road_with_score current_road;
    road_with_score best_road;

    int total_distance = 0;

    for(int i=0; i<g.size(); i++){
        uncharted_nodes.push_back(i);
    }

    visited_nodes.push_back(initial_node);
    uncharted_nodes.erase(remove(uncharted_nodes.begin(), uncharted_nodes.end(), initial_node), uncharted_nodes.end());

    while(!uncharted_nodes.empty() && (find(all_roads.begin(), all_roads.end(), current_road) == all_roads.end())){

//        available_nodes.erase(available_nodes.begin(), available_nodes.end());


        //0
        //0 1 e e 1
        for(int i=0; i<g[0].size(); i++){
            if(g[initial_node][i] != e && g[initial_node][i] >= 1 && (find(visited_nodes.begin(), visited_nodes.end(), i)==visited_nodes.end())){
                available_nodes.push_back(i);
            }
        }

        vector<vector<int>> every_road;

        do {
            vector<int> current_road;
            for (int available_node: available_nodes) {
                int current_node = available_node;
                for (int i = 0; i < g[0].size(); i++) {
                    if (g[current_node][i] != e && g[current_node][i] >= 1 &&
                        (find(visited_nodes.begin(), visited_nodes.end(), i) == visited_nodes.end())) {
                        available_nodes.push_back(i);
                    }
                }
            }
            every_road.push_back(current_road);
        }while()

        int closest_node_distance = e;
        int closest_node;


        //1 4
        for(int possible_closest_node : available_nodes){
            if(g[initial_node][possible_closest_node] <= closest_node_distance){
                closest_node_distance = g[initial_node][possible_closest_node];
                closest_node = possible_closest_node;

                vector<int> discovered_road = {initial_node, possible_closest_node};

                if(possible_closest_node != final_node){
                    vector<int> future_available_nodes;
                    for(int j=0; j<g[0].size(); j++){
                        if(g[possible_closest_node][j] != e && g[possible_closest_node][j] >= 1 && (find(visited_nodes.begin(), visited_nodes.end(), j)==visited_nodes.end())){
                            future_available_nodes.push_back(j);
                        }
                        if(!(find(future_available_nodes.begin(), future_available_nodes.end(), final_node)==future_available_nodes.end())){

                        }
                    }
                }
            }
        }


        total_distance += closest_node_distance;
        initial_node = closest_node;
        visited_nodes.push_back(closest_node);
        uncharted_nodes.erase(remove(uncharted_nodes.begin(), uncharted_nodes.end(), closest_node), uncharted_nodes.end());
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
