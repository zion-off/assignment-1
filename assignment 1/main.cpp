#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctype.h>
using namespace std;

class Node {
public:
    char name;
    int value = 0;
    bool visited = false;
    vector<int> neighbors;
    
    Node(char n, int v) {
        name = n;
        value = v;
    }
};

vector<Node> graph;

//void dfs(int curr, int depth, vector<int>& path) {
//    path.push_back(curr);
//    for (int i=curr+1; i<graph.size(); i++) {
//        bool neighbor = false;
//        for (int j=0; j<graph[i].neighbors.size(); j++) {
//            for (int k=0; k<path.size(); k++) {
//                if (path[k] == i) {
//                    neighbor = true;
//                    break;
//                }
//            }
//        }
//        if (!neighbor) path.push_back(i);
//        if (path.size() > depth) return;
//    }
//    return;
//}

bool dfs(int curr, int depth, vector<int>& path) {
    if (path.size() == depth) {
        return true;
    }
    path.push_back(curr);
    for (int i=0; i<graph[curr].neighbors.size(); i++) {
        int neighbor = graph[curr].neighbors[i];
        bool is_neighbor = false;
        for (int j=0; j<path.size()-1; j++) {
            if (graph[path[j]].name == graph[neighbor].name) {
                cout << "dfs reached " << graph[path[j]].name << " " << graph[neighbor].name << endl;
                is_neighbor = true;
                break;
            }
        }
        if (!is_neighbor) {
            if (dfs(neighbor, depth, path)) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    int target;
    string flag;
    ifstream input_file("input.txt");
    
    input_file >> target >> flag;
    
    string line;
    while (getline(input_file, line)) {
        istringstream parse(line);
        string value1, value2;
        parse >> value1 >> value2;
        if ((isdigit(value2[0])) && (line.size()!=0)) {
            graph.push_back(Node(value1[0], stoi(value2)));
        }
        else if (line.size()==0) {
            continue;
        }
        else {
            int u = -1, v =-1;
            for (int i=0; i<graph.size(); i++) {
                if (graph[i].name == value1[0]) {
                    u=i;
                }
                if (graph[i].name == value2[0]) {
                    v=i;
                }
            }
            graph[u].neighbors.push_back(v);
            graph[v].neighbors.push_back(u);
        }
    }
    
    vector<int> path;
    for (int depth=1; depth<=graph.size(); depth++) {
        cout << "Depth:" << depth << endl;
        for (int i=0; i<graph.size(); i++) {
            int accrue = 0;
            path.clear();
            dfs(i, depth, path);
            for (int j=0; j<path.size(); j++) {
                cout << graph[path[j]].name << " ";
                accrue += graph[path[j]].value;
            }
            cout << "Value=" << accrue << endl;
            if (accrue >= target) {
                cout << "Solution found." << endl;
                return 0;
            }
        }
    }
    return 0;
}
