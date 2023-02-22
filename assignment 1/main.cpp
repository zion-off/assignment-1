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

bool dfs(int curr, int depth, vector<int>& path) {
    // if number of jumps maxed out, return and print results
    if (depth == 0) {
        return true;
    }
    // if we still have jumps left
    else if (depth > 0) {
        path.push_back(curr);
        for (int i=curr+1; i<graph.size(); i++) {
            bool neighbor_found = false;
            for (int j=0; j<graph[curr].neighbors.size(); j++) {
                if (i == graph[curr].neighbors[j]) {
                    neighbor_found = true;
                    break;
                }
            }
            if (neighbor_found) continue;
            else if (!graph[i].visited) {
                dfs(i, --depth, path);
            }
            continue;
        }
    }
    return true;
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
    if (flag == "V") {
        for (int depth=1; depth<=graph.size(); depth++) {
            cout << "Depth:" << depth << endl;
            int accrue = 0;
            for (int i=0; i<graph.size(); i++) {
                if (dfs(i, depth, path)) {
                    accrue = 0;
                    for (int j=0; j<path.size(); j++) {
                        cout << graph[path[j]].name << " ";
                        accrue += graph[path[j]].value;
                    } 
                    cout << "Value=" << accrue << endl;
                    path.clear();
                    if (accrue >= target) {
                        cout << "Solution found." << endl;
                        break;
                    }
                }
                for (int j=0; j<graph.size(); j++) {
                    graph[j].visited = false;
                }
            }
            if (accrue >= target) {
                break;
            }
        }
    }
    return 0;
}
