#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>


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




int main(int argc, char **argv) {

    int e = INF;

    loadAndGenerateGraphviz(argv[1]);

    return 0;
}
