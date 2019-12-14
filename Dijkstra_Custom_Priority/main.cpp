#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

template<class t>
vector<t> cinVector(int size, int scaleDiff, bool toSort = false) {
    vector<t> curr;
    t temp;
    for (int i = 0; i < size; i++) {
        cin >> temp;
        temp += scaleDiff;
        curr.push_back(temp);
    }
    if (toSort) {
        sort(curr.begin(), curr.end());
    }
    return curr;
}

template<class t>
vector<t> cinVector(int size, bool toSort = false) {
    return cinVector<t>(size, 0, toSort);
}

//Dijkstra Algorithm
typedef struct {
    map<int, int> path;
    int index = 0;
    int lenght = 0;
    int gain = 0;
} Dijkstra_Path;

bool dijkstra_compare(const Dijkstra_Path &a, Dijkstra_Path b) {
    if (a.lenght < b.lenght) return false;
    if (a.lenght > b.lenght) return true;
    return a.gain < b.gain;
}

Dijkstra_Path dijkstra(int source, int destination, vvi graph, vvi weights, vi gain) {
    /* Modify dijkstra_compare function to customize the relaxation
     * Graph is expected as:
     * Each vector element contains the indexes of the connected nodes
     * Gain is an amount assigned to every node
     * Weights are the weights of the edges for connections [a][b]
     */
    //Priority queue will sort based on dijkstra_compare
    priority_queue<Dijkstra_Path, vector<Dijkstra_Path>, decltype(&dijkstra_compare)> pq(dijkstra_compare);
    Dijkstra_Path curr;
    curr.path[source] = 1;
    curr.gain = gain[source];
    pq.push(curr);
    bool found = false;
    map<int, int> visited;
    while (!pq.empty()) {
        curr = pq.top();
        pq.pop();
        if (visited.find(curr.index) == visited.end()) {
            //Mark as visited
            visited[curr.index] = 1;
            if (curr.index == destination) {
                found = true;
                break;
            }
            //Relax
            int size = graph[curr.index].size();
            for (int i = 0; i < size; i++) {
                int index = graph[curr.index][i];
                if (curr.path.find(index) == curr.path.end()) {
                    Dijkstra_Path temp = curr;
                    temp.path[index] = temp.path.size();
                    temp.index = index;
                    temp.lenght += weights[index][curr.index];
                    temp.gain += gain[index];
                    pq.push(temp);
                }
            }
        }
    }
    if (!found) {
        Dijkstra_Path error;
        error.index = -1;
        return error;
    }
    return curr;
}

Dijkstra_Path dijkstra(int source, int destination, vvi graph, vvi weights) {
    vi gain(graph.size(), 0);
    return dijkstra(source, destination, graph, weights, gain);
}

int main() {
    //Find relative problem to understand how the input is considered here:
    //https://open.kattis.com/problems/bigtruck
    int n, m;
    cin >> n;
    vvi graph(n);
    vi temp(n, 0);
    vvi weights(n, temp);
    vi gain = cinVector<int>(n);
    n--;
    cin >> m;
    int a, b, l;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> l;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
        weights[a][b] = l;
        weights[b][a] = l;
    }
    Dijkstra_Path path = dijkstra(0, n, graph, weights, gain);
    if (path.index == -1) {
        cout << "impossible" << endl;
    } else {
        cout << path.lenght << " " << path.gain << endl;
    }
}
