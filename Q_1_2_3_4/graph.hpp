#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

class Graph {
public:
    // Constructor
    Graph(int vertices);

    // Function to add edges
    void addEdge(int u, int v);

    // Getters
    int getVertexCount() const;
    int getEdgeCount() const;

    // Utility functions
    bool hasEdge(int u, int v) const;
    bool hasEulerianCycle() const;

private:
    int vertexCount;
    int edgeCount;
    std::vector<std::vector<int>> adjList; // Adjacency list using a simple 2D vector

    // Helper functions
    bool isConnected() const;
    int degree(int v) const;
};

// Function to generate a random graph with a specified seed
Graph generateRandomGraph(int vertices, int edges, int seed);

#endif // GRAPH_HPP
