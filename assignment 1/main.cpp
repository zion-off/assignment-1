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
    path.push_back(curr);
    while (path.size()<=depth) {
        for (int i=0; i<path.size(); i++) {
            if (!(find(graph[path[i]].neighbors.begin(), graph[path[i]].neighbors.end(), curr+1) != graph[path[i]].neighbors.end()))
                dfs(curr+1, depth, path);
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
        for (int depth=0; depth<=graph.size(); depth++) {
            cout << "Depth:" << depth+1 << endl;
            for (int i=0; i<graph.size(); i++) {
                int accrue = 0;
                if (dfs(i, depth, path)) {
                    for (int j=0; j<path.size(); j++) {
                        cout << graph[path[j]].name << " ";
                        accrue += graph[path[j]].value;
                    }
                    cout << "Value=" << accrue << endl;
                    if (accrue >= target) {
                        cout << "Solution found." << endl;
                        return 0;
                    }
                    path.clear();
                }
            }
        }
    }
    return 0;
}
