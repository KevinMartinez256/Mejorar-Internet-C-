#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <queue>
#include <numeric>
#include <cfloat>

using namespace std;

// Estructura para representar un borde en el grafo
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Estructura para representar un grafo
class Graph {
public:
    int N;
    vector<Edge> edges;
    vector<vector<int>> capacity;
    vector<pair<int, int>> locations;

    Graph(int n) : N(n) {
        capacity.resize(N, vector<int>(N, 0));
    }

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    int findMST();
    vector<int> solveTSP();
    int maxFlow(int source, int sink);
    pair<int, int> findNearestCentral(pair<int, int> newPoint);
};

// Disjoint Set para Kruskal
class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Algoritmo de Kruskal para MST
int Graph::findMST() {
    sort(edges.begin(), edges.end());
    DisjointSet ds(N);
    int mstWeight = 0;

    for (auto& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unite(edge.u, edge.v);
            mstWeight += edge.weight;
            cout << "(" << char('A' + edge.u) << ", " << char('A' + edge.v) << ")\n";
        }
    }
    return mstWeight;
}

// TSP usando fuerza bruta (para ciudades pequeñas)
vector<int> Graph::solveTSP() {
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 0);
    vector<int> bestRoute;
    int minDist = INT_MAX;
    
    do {
        int dist = 0;
        for (int i = 0; i < N - 1; i++) dist += edges[i].weight;
        dist += edges[N - 1].weight;
        
        if (dist < minDist) {
            minDist = dist;
            bestRoute = perm;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    for (int i : bestRoute) cout << char('A' + i) << " ";
    cout << char('A' + bestRoute[0]) << endl;
    return bestRoute;
}

// Algoritmo de Ford-Fulkerson
int Graph::maxFlow(int source, int sink) {
    vector<vector<int>> residual = capacity;
    vector<int> parent(N);
    int max_flow = 0;

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<pair<int, int>> q;
        q.push({source, INT_MAX});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next = 0; next < N; next++) {
                if (parent[next] == -1 && residual[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = min(flow, residual[cur][next]);
                    if (next == sink) {
                        max_flow += new_flow;
                        int node = sink;
                        while (node != source) {
                            int prev = parent[node];
                            residual[prev][node] -= new_flow;
                            residual[node][prev] += new_flow;
                            node = prev;
                        }
                        break;
                    }
                    q.push({next, new_flow});
                }
            }
        }
        if (parent[sink] == -1) break;
    }
    cout << "Flujo máximo: " << max_flow << endl;
    return max_flow;
}

// Encuentra la central más cercana
pair<int, int> Graph::findNearestCentral(pair<int, int> newPoint) {
    double minDist = DBL_MAX;
    pair<int, int> closestCentral;

    for (auto& central : locations) {
        double dist = sqrt(pow(central.first - newPoint.first, 2) + pow(central.second - newPoint.second, 2));
        if (dist < minDist) {
            minDist = dist;
            closestCentral = central;
        }
    }
    cout << "Central más cercana: (" << closestCentral.first << ", " << closestCentral.second << ")\n";
    return closestCentral;
}

int main() {
    int N;
    cin >> N;
    Graph g(N);

    // Leer matriz de distancias
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int dist;
            cin >> dist;
            if (i != j) g.addEdge(i, j, dist);
        }
    }

    // Leer matriz de capacidades
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> g.capacity[i][j];
        }
    }

    // Leer ubicaciones de las centrales
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        g.locations.push_back({x, y});
    }

    cout << "Matriz de capacidades y ubicaciones leídas correctamente" << endl;

    // Ejecutar algoritmos
    g.findMST();
    g.solveTSP();
    g.maxFlow(0, N - 1);

    // Leer la nueva ubicación y encontrar la central más cercana
    pair<int, int> newPoint;
    cin >> newPoint.first >> newPoint.second;
    g.findNearestCentral(newPoint);

    return 0;
}
