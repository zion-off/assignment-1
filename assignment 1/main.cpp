#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctype.h>
#include <stack>
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

void dfs_utility(int curr, vector<int>& path, int depth) {
    stack<int> dfs_stack;
    dfs_stack.push(curr);

    while (!dfs_stack.empty()) {
        if (path.size() >= depth) {
            return;
        }

        curr = dfs_stack.top();
        dfs_stack.pop();
        
        path.push_back(curr);

        for (int i=curr+1; i<graph.size(); i++) {
            bool neighbor = false;
            for (int j=0; j<graph[curr].neighbors.size(); j++) {
                if (i == graph[curr].neighbors[j]) {
                    neighbor = true;
                    break;
                }
            }
            if (!neighbor) {
                dfs_stack.push(i);
            }
        }
    }
}

void dfs(vector<int>& path, int target) {
    bool solution_found = false;
    for (int depth=1; depth<graph.size(); depth++) {
        cout << "Depth:" << depth << endl;
        for (int i=0; i<graph.size(); i++) {
            dfs_utility(i, path, depth);
            int accrue = 0;
            for (int j=0; j<path.size(); j++) {
                cout << graph[path[j]].name << " ";
                accrue += graph[path[j]].value;
            }
            cout << "Value=" << accrue << endl;
            if (accrue >= target) {
                solution_found = true;
                cout << "Solution found" << endl;
                break;
            }
            path.clear();
        }
        if (solution_found) {
            break;
        }
    }
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

    dfs(path, target);

    return 0;
}
