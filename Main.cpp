#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>
using namespace std;

// Graph class for adjacency matrix representation
class Graph {
private:
    int numOfVertices;
    int **adjMatrix;

public:
    // Constructor
    Graph(int n) {
        numOfVertices = n;

        // Dynamically allocate a 2D array for adjacency matrix
        adjMatrix = new int*[numOfVertices];
        for (int i = 0; i < numOfVertices; ++i) {
            adjMatrix[i] = new int[numOfVertices];
            memset(adjMatrix[i], 0, numOfVertices * sizeof(int)); // Initialize to 0
        }
    }

    // Destructor
    ~Graph() {
        for (int i = 0; i < numOfVertices; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    // Add edge to the graph
    void addEdge(int u, int v) {
        adjMatrix[u - 1][v - 1] = 1;
        adjMatrix[v - 1][u - 1] = 1; // Undirected graph
    }

    // Print the adjacency matrix
    void printAdjacencyMatrix() {
        cout << "The adjacency matrix of G:\n";
        for (int i = 0; i < numOfVertices; ++i) {
            for (int j = 0; j < numOfVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Find odd-degree vertices
    void findOddDegreeVertices() {
    int *degree = new int[numOfVertices];
    memset(degree, 0, numOfVertices * sizeof(int));

    // Compute degree of each vertex
    for (int i = 0; i < numOfVertices; ++i) {
        for (int j = 0; j < numOfVertices; ++j) {
            degree[i] += adjMatrix[i][j];
        }
    }

    // Print odd-degree vertices
    cout << "\nThe odd degree vertices in G:\nO = { ";
    bool first = true; // To handle spacing correctly
    for (int i = 0; i < numOfVertices; ++i) {
        if (degree[i] % 2 != 0) {
            if (!first) cout << " "; // Add space before subsequent vertices
            cout << (i + 1);
            first = false;
        }
    }
    cout << " }\n"; // Close the set notation

    // Execute Dijkstra's for each odd-degree vertex
    for (int i = 0; i < numOfVertices; ++i) {
        if (degree[i] % 2 != 0) {
            dijkstra(i + 1);
        }
    }

    delete[] degree;
}


    // Perform Dijkstra's algorithm to find shortest paths
    void dijkstra(int startVertex) {
        int *distance = new int[numOfVertices];
        bool *visited = new bool[numOfVertices];

        // Initialize distance and visited arrays
        for (int i = 0; i < numOfVertices; ++i) {
            distance[i] = INT_MAX; // Use INT_MAX as infinity
            visited[i] = false;
        }

        distance[startVertex - 1] = 0; // Distance to self is 0

        // Dijkstra's main loop
        for (int i = 0; i < numOfVertices; ++i) {
            // Find the unvisited vertex with the smallest distance
            int minDistance = INT_MAX, minIndex = -1;
            for (int j = 0; j < numOfVertices; ++j) {
                if (!visited[j] && distance[j] < minDistance) {
                    minDistance = distance[j];
                    minIndex = j;
                }
            }

            // Mark the vertex as visited
            visited[minIndex] = true;

            // Update distances to neighbors
            for (int j = 0; j < numOfVertices; ++j) {
                if (adjMatrix[minIndex][j] && !visited[j] &&
                    distance[minIndex] + 1 < distance[j]) {
                    distance[j] = distance[minIndex] + 1;
                }
            }
        }

        // Print shortest path results
        cout << "\n\nSingle source shortest path lengths from node " << startVertex << "\n";
        for (int i = 0; i < numOfVertices; ++i) {
            cout << "  " << (i + 1) << ": ";
            if (distance[i] == INT_MAX) {
                cout << "Unreachable\n";
            } else {
                cout << distance[i] << "\n";
            }
        }

        delete[] distance;
        delete[] visited;
    }
};

int main() {
    int numOfVertices, numOfEdges;

    // Read number of vertices and edges
    if (!(cin >> numOfVertices >> numOfEdges)) {
        cerr << "Invalid input format!\n";
        return -1;
    }

    Graph graph(numOfVertices);

    // Read edges
    for (int i = 0; i < numOfEdges; ++i) {
        int u, v;
        if (cin >> u >> v) {
            graph.addEdge(u, v);
        } else {
            cerr << "Invalid edge format!\n";
            return -1;
        }
    }

    // Part 1: Print adjacency matrix
    graph.printAdjacencyMatrix();

    // Part 2 & 3: Find odd-degree vertices and compute shortest paths
    graph.findOddDegreeVertices();

    return 0;
}
