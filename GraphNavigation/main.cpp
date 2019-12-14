#include <vector>
#include <queue>
#include <iostream>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void navigateGraph(vvi graph, int &missingConnections, int &cycles) {
    int size = graph.size();
    vector<bool> reached(size, false);
    vector<bool> inQue(size, false);
    queue<int> q;
    //Let N be the number of separated graphs: the number of missing connections is N-1
    missingConnections--;
    //It will visit every node in the graph once
    for (int i = 0; i < size; i++) {
        if (!reached[i]) {
            missingConnections++;
            q.push(i);
            inQue[i] = true;
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                reached[curr] = true;
                inQue[curr] = false;
                int currSize = graph[curr].size();
                for (int j = 0; j < currSize; j++) {
                    int index = graph[curr][j];
                    if (!reached[index]) {
                        if (inQue[index]) {
                            cycles++;
                        } else {
                            inQue[index] = true;
                            q.push(index);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    //Solution to the problem:
    //https://open.kattis.com/problems/reachableroads
    //I'm pretty sure this algorithm solves other problems on kattis, I just cant remember which
    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        vvi graph(m);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        int missingConnections = 0;
        int cycles = 0;
        navigateGraph(graph, missingConnections, cycles);
        cout << missingConnections << endl;
    }
}
