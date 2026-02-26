/*
C++ Graph Implementation - Comprehensive Guide
==============================================
This file demonstrates various graph representations and algorithms
including adjacency matrix, adjacency list, and common graph traversal
and search algorithms.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <list>

using namespace std;

// =========================================================================
// 1. Adjacency Matrix Representation
// =========================================================================
class AdjacencyMatrixGraph {
private:
    int numVertices;
    vector<vector<int>> matrix;
    
public:
    AdjacencyMatrixGraph(int vertices) : numVertices(vertices) {
        matrix.resize(vertices, vector<int>(vertices, 0));
    }
    
    void addEdge(int src, int dest, int weight = 1) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            matrix[src][dest] = weight;
            matrix[dest][src] = weight; // Undirected graph
        }
    }
    
    void removeEdge(int src, int dest) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            matrix[src][dest] = 0;
            matrix[dest][src] = 0;
        }
    }
    
    bool hasEdge(int src, int dest) const {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            return matrix[src][dest] != 0;
        }
        return false;
    }
    
    vector<int> getNeighbors(int vertex) const {
        vector<int> neighbors;
        if (vertex >= 0 && vertex < numVertices) {
            for (int i = 0; i < numVertices; ++i) {
                if (matrix[vertex][i] != 0) {
                    neighbors.push_back(i);
                }
            }
        }
        return neighbors;
    }
    
    int getWeight(int src, int dest) const {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            return matrix[src][dest];
        }
        return 0;
    }
    
    int getNumVertices() const {
        return numVertices;
    }
    
    void print() const {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < numVertices; ++i) {
            cout << i << ": ";
            for (int j = 0; j < numVertices; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// =========================================================================
// 2. Adjacency List Representation
// =========================================================================
class AdjacencyListGraph {
private:
    int numVertices;
    unordered_map<int, unordered_map<int, int>> adjList;
    
public:
    AdjacencyListGraph(int vertices) : numVertices(vertices) {
        for (int i = 0; i < vertices; ++i) {
            adjList[i] = unordered_map<int, int>();
        }
    }
    
    void addEdge(int src, int dest, int weight = 1) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            adjList[src][dest] = weight;
            adjList[dest][src] = weight; // Undirected graph
        }
    }
    
    void removeEdge(int src, int dest) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            adjList[src].erase(dest);
            adjList[dest].erase(src);
        }
    }
    
    bool hasEdge(int src, int dest) const {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            auto it = adjList.find(src);
            if (it != adjList.end()) {
                return it->second.find(dest) != it->second.end();
            }
        }
        return false;
    }
    
    vector<int> getNeighbors(int vertex) const {
        vector<int> neighbors;
        if (vertex >= 0 && vertex < numVertices) {
            auto it = adjList.find(vertex);
            if (it != adjList.end()) {
                for (const auto& pair : it->second) {
                    neighbors.push_back(pair.first);
                }
            }
        }
        return neighbors;
    }
    
    int getWeight(int src, int dest) const {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            auto it = adjList.find(src);
            if (it != adjList.end()) {
                auto edgeIt = it->second.find(dest);
                if (edgeIt != it->second.end()) {
                    return edgeIt->second;
                }
            }
        }
        return 0;
    }
    
    int getNumVertices() const {
        return numVertices;
    }
    
    void print() const {
        cout << "Adjacency List:\n";
        for (int i = 0; i < numVertices; ++i) {
            cout << i << ": ";
            for (const auto& edge : adjList.at(i)) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }
};

// =========================================================================
// 3. Graph Algorithms
// =========================================================================
class GraphAlgorithms {
public:
    // Breadth First Search (BFS)
    static vector<int> BFS(const AdjacencyListGraph& graph, int start) {
        vector<int> result;
        unordered_set<int> visited;
        queue<int> q;
        
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);
            
            vector<int> neighbors = graph.getNeighbors(current);
            for (int neighbor : neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        
        return result;
    }
    
    // Depth First Search (DFS) - Recursive
    static vector<int> DFSRecursive(const AdjacencyListGraph& graph, int start) {
        vector<int> result;
        unordered_set<int> visited;
        DFSHelper(graph, start, visited, result);
        return result;
    }
    
    static void DFSHelper(const AdjacencyListGraph& graph, int current, 
                          unordered_set<int>& visited, vector<int>& result) {
        visited.insert(current);
        result.push_back(current);
        
        vector<int> neighbors = graph.getNeighbors(current);
        for (int neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                DFSHelper(graph, neighbor, visited, result);
            }
        }
    }
    
    // Depth First Search (DFS) - Iterative
    static vector<int> DFSIterative(const AdjacencyListGraph& graph, int start) {
        vector<int> result;
        unordered_set<int> visited;
        stack<int> s;
        
        s.push(start);
        
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            
            if (visited.find(current) == visited.end()) {
                visited.insert(current);
                result.push_back(current);
                
                vector<int> neighbors = graph.getNeighbors(current);
                // Push in reverse order to maintain same order as recursive
                for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
                    if (visited.find(*it) == visited.end()) {
                        s.push(*it);
                    }
                }
            }
        }
        
        return result;
    }
    
    // Shortest Path using BFS (unweighted graph)
    static vector<int> shortestPathBFS(const AdjacencyListGraph& graph, int start, int end) {
        unordered_map<int, int> parent;
        unordered_set<int> visited;
        queue<int> q;
        
        q.push(start);
        visited.insert(start);
        parent[start] = -1;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            if (current == end) {
                vector<int> path;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                reverse(path.begin(), path.end());
                return path;
            }
            
            vector<int> neighbors = graph.getNeighbors(current);
            for (int neighbor : neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
        
        return {}; // Path not found
    }
    
    // Dijkstra's Algorithm for shortest path (weighted graph)
    static vector<int> dijkstra(const AdjacencyListGraph& graph, int start, int end) {
        int n = graph.getNumVertices();
        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);
        vector<bool> visited(n, false);
        
        dist[start] = 0;
        
        for (int i = 0; i < n - 1; ++i) {
            int u = -1;
            int minDist = INT_MAX;
            
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }
            
            if (u == -1) break;
            visited[u] = true;
            
            if (u == end) break;
            
            vector<int> neighbors = graph.getNeighbors(u);
            for (int v : neighbors) {
                if (!visited[v]) {
                    int weight = graph.getWeight(u, v);
                    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        prev[v] = u;
                    }
                }
            }
        }
        
        vector<int> path;
        int current = end;
        
        if (prev[end] == -1 && start != end) {
            return path; // No path
        }
        
        while (current != -1) {
            path.push_back(current);
            current = prev[current];
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
    
    // Bellman-Ford Algorithm for shortest path (negative weights)
    static vector<int> bellmanFord(const AdjacencyListGraph& graph, int start, int end) {
        int n = graph.getNumVertices();
        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);
        
        dist[start] = 0;
        
        for (int i = 0; i < n - 1; ++i) {
            for (int u = 0; u < n; ++u) {
                if (dist[u] == INT_MAX) continue;
                
                vector<int> neighbors = graph.getNeighbors(u);
                for (int v : neighbors) {
                    int weight = graph.getWeight(u, v);
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        prev[v] = u;
                    }
                }
            }
        }
        
        // Check for negative weight cycles
        for (int u = 0; u < n; ++u) {
            if (dist[u] == INT_MAX) continue;
            
            vector<int> neighbors = graph.getNeighbors(u);
            for (int v : neighbors) {
                int weight = graph.getWeight(u, v);
                if (dist[u] + weight < dist[v]) {
                    cout << "Graph contains negative weight cycle!" << endl;
                    return {};
                }
            }
        }
        
        vector<int> path;
        int current = end;
        
        if (prev[end] == -1 && start != end) {
            return path; // No path
        }
        
        while (current != -1) {
            path.push_back(current);
            current = prev[current];
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
    
    // Kruskal's Algorithm for Minimum Spanning Tree
    static vector<pair<pair<int, int>, int>> kruskal(const AdjacencyListGraph& graph) {
        vector<pair<pair<int, int>, int>> edges;
        int n = graph.getNumVertices();
        
        for (int u = 0; u < n; ++u) {
            vector<int> neighbors = graph.getNeighbors(u);
            for (int v : neighbors) {
                if (u < v) { // Avoid duplicates
                    int weight = graph.getWeight(u, v);
                    edges.push_back({{u, v}, weight});
                }
            }
        }
        
        sort(edges.begin(), edges.end(), 
             [](const auto& a, const auto& b) {
                 return a.second < b.second;
             });
        
        vector<int> parent(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        
        vector<pair<pair<int, int>, int>> mst;
        int count = 0;
        
        for (const auto& edge : edges) {
            int u = edge.first.first;
            int v = edge.first.second;
            int w = edge.second;
            
            int rootU = find(parent, u);
            int rootV = find(parent, v);
            
            if (rootU != rootV) {
                mst.push_back(edge);
                unite(parent, rootU, rootV);
                count++;
                
                if (count == n - 1) {
                    break;
                }
            }
        }
        
        return mst;
    }
    
    static int find(vector<int>& parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    static void unite(vector<int>& parent, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
        }
    }
    
    // Prim's Algorithm for Minimum Spanning Tree
    static vector<pair<pair<int, int>, int>> prim(const AdjacencyListGraph& graph, int start = 0) {
        int n = graph.getNumVertices();
        vector<bool> visited(n, false);
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        
        dist[start] = 0;
        visited[start] = true;
        
        vector<pair<pair<int, int>, int>> mst;
        
        for (int i = 0; i < n - 1; ++i) {
            int u = -1;
            int minDist = INT_MAX;
            
            for (int v = 0; v < n; ++v) {
                if (!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }
            
            if (u == -1) break;
            
            visited[u] = true;
            
            if (parent[u] != -1) {
                int w = graph.getWeight(parent[u], u);
                mst.push_back({{parent[u], u}, w});
            }
            
            vector<int> neighbors = graph.getNeighbors(u);
            for (int v : neighbors) {
                int weight = graph.getWeight(u, v);
                if (!visited[v] && weight < dist[v]) {
                    dist[v] = weight;
                    parent[v] = u;
                }
            }
        }
        
        return mst;
    }
    
    // Check if graph is bipartite
    static bool isBipartite(const AdjacencyListGraph& graph) {
        int n = graph.getNumVertices();
        vector<int> color(n, -1); // -1: uncolored, 0 and 1: two colors
        
        for (int start = 0; start < n; ++start) {
            if (color[start] == -1) {
                queue<int> q;
                q.push(start);
                color[start] = 0;
                
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    
                    vector<int> neighbors = graph.getNeighbors(u);
                    for (int v : neighbors) {
                        if (color[v] == -1) {
                            color[v] = color[u] ^ 1;
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false;
                        }
                    }
                }
            }
        }
        
        return true;
    }
    
    // Count connected components
    static int countConnectedComponents(const AdjacencyListGraph& graph) {
        int n = graph.getNumVertices();
        unordered_set<int> visited;
        int count = 0;
        
        for (int i = 0; i < n; ++i) {
            if (visited.find(i) == visited.end()) {
                vector<int> component = BFS(graph, i);
                for (int vertex : component) {
                    visited.insert(vertex);
                }
                count++;
            }
        }
        
        return count;
    }
};

// =========================================================================
// Helper Functions
// =========================================================================
void printPath(const vector<int>& path) {
    if (path.empty()) {
        cout << "No path exists" << endl;
        return;
    }
    
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) {
            cout << " -> ";
        }
        cout << path[i];
    }
    cout << endl;
}

void printMST(const vector<pair<pair<int, int>, int>>& mst) {
    if (mst.empty()) {
        cout << "No MST exists (graph is disconnected)" << endl;
        return;
    }
    
    cout << "Minimum Spanning Tree:\n";
    int totalWeight = 0;
    
    for (const auto& edge : mst) {
        cout << edge.first.first << " - " << edge.first.second 
             << " (Weight: " << edge.second << ")" << endl;
        totalWeight += edge.second;
    }
    
    cout << "Total weight: " << totalWeight << endl;
}

void printTraversal(const vector<int>& traversal, const string& algorithm) {
    cout << algorithm << ": ";
    for (int vertex : traversal) {
        cout << vertex << " ";
    }
    cout << endl;
}

// =========================================================================
// Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Graph Implementation Example ===\n\n";
    
    // Create a graph
    int numVertices = 6;
    AdjacencyListGraph graph(numVertices);
    
    // Add edges (undirected, weighted)
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 1);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 5, 6);
    
    // Print graph
    graph.print();
    cout << endl;
    
    // Graph traversals
    cout << "1. Graph Traversals:\n";
    vector<int> bfsResult = GraphAlgorithms::BFS(graph, 0);
    printTraversal(bfsResult, "BFS");
    
    vector<int> dfsRecursiveResult = GraphAlgorithms::DFSRecursive(graph, 0);
    printTraversal(dfsRecursiveResult, "DFS Recursive");
    
    vector<int> dfsIterativeResult = GraphAlgorithms::DFSIterative(graph, 0);
    printTraversal(dfsIterativeResult, "DFS Iterative");
    
    cout << endl;
    
    // Shortest path algorithms
    cout << "2. Shortest Path Algorithms:\n";
    int start = 0, end = 5;
    
    vector<int> bfsPath = GraphAlgorithms::shortestPathBFS(graph, start, end);
    cout << "BFS Shortest Path (unweighted) from " << start << " to " << end << ": ";
    printPath(bfsPath);
    
    vector<int> dijkstraPath = GraphAlgorithms::dijkstra(graph, start, end);
    cout << "Dijkstra's Shortest Path (weighted) from " << start << " to " << end << ": ";
    printPath(dijkstraPath);
    
    vector<int> bellmanFordPath = GraphAlgorithms::bellmanFord(graph, start, end);
    cout << "Bellman-Ford Shortest Path (negative weights) from " << start << " to " << end << ": ";
    printPath(bellmanFordPath);
    
    cout << endl;
    
    // Minimum Spanning Tree algorithms
    cout << "3. Minimum Spanning Tree:\n";
    cout << "Kruskal's Algorithm:\n";
    vector<pair<pair<int, int>, int>> kruskalMST = GraphAlgorithms::kruskal(graph);
    printMST(kruskalMST);
    
    cout << "\nPrim's Algorithm:\n";
    vector<pair<pair<int, int>, int>> primMST = GraphAlgorithms::prim(graph);
    printMST(primMST);
    
    cout << endl;
    
    // Graph properties
    cout << "4. Graph Properties:\n";
    cout << "Number of connected components: " 
         << GraphAlgorithms::countConnectedComponents(graph) << endl;
    cout << "Is bipartite: " << (GraphAlgorithms::isBipartite(graph) ? "Yes" : "No") << endl;
    
    cout << endl;
    
    cout << "=== All Tests Completed ===\n";
    return 0;
}

/*
Key Takeaways:
1. Graph Representations:
   - Adjacency Matrix: O(n^2) space, O(1) edge check, suitable for dense graphs
   - Adjacency List: O(n + m) space, O(degree) edge check, suitable for sparse graphs
   
2. Traversal Algorithms:
   - BFS: Level-order traversal using queue, finds shortest path in unweighted graphs
   - DFS: Depth-first traversal using stack/recursion, explores as far as possible
   
3. Shortest Path Algorithms:
   - BFS: O(n + m), unweighted graphs
   - Dijkstra: O(m log n), weighted graphs with non-negative weights
   - Bellman-Ford: O(nm), handles negative weights and detects negative cycles
   
4. Minimum Spanning Tree (MST):
   - Kruskal: O(m log m), uses Union-Find (Disjoint Set Union) to add smallest edges
   - Prim: O(m log n), grows tree from start vertex, suitable for dense graphs
   
5. Other Graph Properties:
   - Bipartite Check: Checks if graph can be colored with two colors without conflicts
   - Connected Components: Number of disjoint subgraphs
   
6. Time Complexity Analysis:
   - V: number of vertices
   - E: number of edges
   - Most algorithms: O(V + E) for simple traversal, O(E log V) for advanced algorithms
*/
