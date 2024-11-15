#include "graph.hpp"
#include <algorithm>
#include <stdexcept>
#include <random>
#include <iostream>
#include <cstdlib> // for std::atoi
#include <unistd.h> // for getopt

// Constructor
Graph::Graph(int vertices)
    : vertexCount(vertices), edgeCount(0), adjList(vertices) {}

// Add an edge between vertex u and vertex v
void Graph::addEdge(int u, int v) {
    if (u >= vertexCount || v >= vertexCount || u < 0 || v < 0) {
        throw std::out_of_range("Vertex index out of bounds");
    }
    adjList[u].push_back(v);
    adjList[v].push_back(u); // Since this is an undirected graph
    edgeCount++;
}

// Get the total number of vertices in the graph
int Graph::getVertexCount() const {
    return vertexCount;
}

// Get the total number of edges in the graph
int Graph::getEdgeCount() const {
    return edgeCount;
}

// Check if there is an edge between vertex u and vertex v
bool Graph::hasEdge(int u, int v) const {
    if (u >= vertexCount || v >= vertexCount || u < 0 || v < 0) {
        throw std::out_of_range("Vertex index out of bounds");
    }
    const auto &neighbors = adjList[u];
    return std::find(neighbors.begin(), neighbors.end(), v) != neighbors.end();
}

// Check if the graph has an Eulerian cycle
bool Graph::hasEulerianCycle() const {
    if (!isConnected()) {
        return false;
    }
    for (int v = 0; v < vertexCount; ++v) {
        if (degree(v) % 2 != 0) {
            return false;
        }
    }
    return true;
}

// Helper function to check if the graph is connected
bool Graph::isConnected() const {
    std::vector<bool> visited(vertexCount, false);
    int start = -1;
    for (int i = 0; i < vertexCount; ++i) {
        if (!adjList[i].empty()) {
            start = i;
            break;
        }
    }
    if (start == -1) return true;

    std::vector<int> stack{start};
    visited[start] = true;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push_back(neighbor);
            }
        }
    }

    for (int i = 0; i < vertexCount; ++i) {
        if (!adjList[i].empty() && !visited[i]) {
            return false;
        }
    }
    return true;
}

// Helper function to get the degree of a vertex
int Graph::degree(int v) const {
    return adjList[v].size();
}

// Generate a random graph with a specified seed
Graph generateRandomGraph(int vertices, int edges, int seed) {
    Graph graph(vertices);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(0, vertices - 1);

    while (graph.getEdgeCount() < edges) {
        int u = dist(gen);
        int v = dist(gen);
        if (u != v && !graph.hasEdge(u, v)) {
            graph.addEdge(u, v);
        }
    }
    return graph;
}

// Main function to get input from the command line using getopt, generate the graph, and check for Eulerian cycle
int main(int argc, char* argv[]) {
    int vertices = 0;
    int edges = 0;
    int seed = 0;

    int option;
    while ((option = getopt(argc, argv, "v:e:s:")) != -1) {
        switch (option) {
            case 'v':
                vertices = std::atoi(optarg);
                break;
            case 'e':
                edges = std::atoi(optarg);
                break;
            case 's':
                seed = std::atoi(optarg);
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -v <number of vertices> -e <number of edges> -s <seed>\n";
                return 1;
        }
    }

    if (vertices <= 0 || edges < 0) {
        std::cerr << "The number of vertices must be positive, and the number of edges must be 0 or more.\n";
        return 1;
    }

    Graph graph = generateRandomGraph(vertices, edges, seed);
    std::cout << "Random graph generated with " << vertices << " vertices and " << edges << " edges, seed: " << seed << ".\n";

    if (graph.hasEulerianCycle()) {
        std::cout << "The graph has an Eulerian cycle.\n";
    } else {
        std::cout << "The graph does not have an Eulerian cycle.\n";
    }

    return 0;
}
