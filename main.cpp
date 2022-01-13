#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <set>
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

vector<int> dijkstra(graph g, int initial_node){

    int e = INF;

    vector<int> visited_nodes;
    vector<int> available_nodes;
    vector<int> uncharted_nodes;

    int total_distance = 0;

    for(int i=0; i<g.size(); i++){
        uncharted_nodes.push_back(i);
    }

    visited_nodes.push_back(initial_node);
    uncharted_nodes.erase(remove(uncharted_nodes.begin(), uncharted_nodes.end(), initial_node), uncharted_nodes.end());

    while(!uncharted_nodes.empty()){

        available_nodes.erase(available_nodes.begin(), available_nodes.end());

        //0
        //0 1 e e 1
        for(int i=0; i<g[0].size(); i++){
            if(g[initial_node][i] != e && g[initial_node][i] >= 1 && (find(visited_nodes.begin(), visited_nodes.end(), i)==visited_nodes.end())){
                available_nodes.push_back(i);
                cout << "DODALEM " << i << endl;
            }
        }
        cout << "NEXT" << endl;

        int closest_node_distance = e;
        int closest_node;


        //1 4
        for(int possible_closest_node : available_nodes){
            if(g[initial_node][possible_closest_node] < closest_node_distance){
                closest_node_distance = g[initial_node][possible_closest_node];
                closest_node = possible_closest_node;

                cout << "NAJBLIZSZY NODE: " << possible_closest_node << endl;
            }
        }


        total_distance += closest_node_distance;
        initial_node = closest_node;
        visited_nodes.push_back(closest_node);
        uncharted_nodes.erase(remove(uncharted_nodes.begin(), uncharted_nodes.end(), closest_node), uncharted_nodes.end());

        for(int un : uncharted_nodes){
            cout << "UNCHARTED : " << un << endl;
        }

    }

    return visited_nodes;

}


int main(int argc, char **argv) {

    int e = INF;

    graph g = {
            {0, 1, e, e, 1},
            {1, 0, 3, 1, e},
            {e, 3, 0, 1, e},
            {e, 1, 1, 0, 1},
            {1, e, e, 1, 0}};

    vector<int> visited_nodes = dijkstra(g, 0);

    for(int node : visited_nodes) {
        cout << node << endl;
    }


    return 0;
}
