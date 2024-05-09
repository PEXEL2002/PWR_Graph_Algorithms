#include "ListGraph.h"
ListGraph::ListGraph(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    std::string line;
    _numVertices = 0;
    // Czytaj każdą linię pliku, która reprezentuje listę sąsiedztwa jednego wierzchołka
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::list<std::pair<int, int>> vertexList;

        while (iss >> token) {
            int pos = token.find('(');
            int endPos = token.find(')');
            int vertex = std::stoi(token.substr(0, pos));
            int weight = std::stoi(token.substr(pos + 1, endPos - pos - 1));
            vertexList.push_back({vertex, weight});
        }
        _adjacencyList.push_back(vertexList);
        _numVertices++;
    }

    file.close();
}
ListGraph::~ListGraph(){}
void ListGraph::addEdge(int v, int w, int weight) {
    if (v >= _numVertices || w < 0) {
        throw std::out_of_range("Vertex index out of valid range");
    }
    _adjacencyList[v].push_back({w, weight});
}
void ListGraph::print() {
    std::cout << "List: " << std::endl;
    for (int i = 0; i < _numVertices; i++) {
        std::cout << i << ": ";
        for (const auto& edge : _adjacencyList[i]) {
            std::cout << edge.first << "(" << edge.second << ") ";
        }
        std::cout << std::endl;
    }
}
void ListGraph::dijkstraAlgorithmToAll(int startVertex){
    if (startVertex >= _numVertices || startVertex < 0) {
        throw std::out_of_range("Vertex index out of valid range");
    }
    std::vector<int> distance(_numVertices, INT_MAX); // Initialize distances to all vertices as infinity
    std::vector<bool> visited(_numVertices, false); // Initialize all vertices as not visited
    std::vector<int> predecessor(_numVertices, -1); // Initialize all predecessors as -1
    distance[startVertex] = 0;// Distance from start vertex to itself is 0
    for(int i = 0; i < _numVertices - 1; i++){ // Find shortest path for all vertices
        int u = -1;
        for(int j = 0; j < _numVertices; j++){ // Find the vertex with the minimum distance
            if(!visited[j] && (u == -1 || distance[j] < distance[u])){
                u = j;
            }
        }
        visited[u] = true;
        for(const auto& edge : _adjacencyList[u]){ // Update distances to all adjacent vertices
            int v = edge.first;
            int weight = edge.second;
            if(distance[u] != INT_MAX && distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
                predecessor[v] = u;
            }
        }
    }
    // Display all distances and paths
    std::cout << "Dijkstra List: " << std::endl;
    for(int i = 0; i < _numVertices; i++){
        if (i == startVertex) continue; // Skip start vertex
        std::cout << "Distance from " << startVertex+1 << " to " << i+1 << " is " << distance[i];
        if(distance[i] == INT_MAX){
            std::cout << " (No path)" << std::endl;
        } else {
            std::cout << " Path: ";
                std::vector<int> path;
                for (int at = i; at != -1; at = predecessor[at]) { //   Construct path
                    path.insert(path.begin(), at);  // Insert at the    beginning
                }
                for (int v : path) { // Print path
                    std::cout << v+1 << " ";
                }
            std::cout << std::endl;
        }
    }
}
void ListGraph::dijkstraAlgorithmToPoint(int startVertex, int endVertex) {
    if(startVertex >= _numVertices || endVertex >= _numVertices || startVertex < 0 || endVertex < 0){
        throw std::out_of_range("Vertex index out of valid range");
    }
    if(startVertex == endVertex){
        throw std::invalid_argument("Start and end vertex are the same");
    }
    std::vector<int> distance(_numVertices, INT_MAX); // Initialize distances to all vertices as infinity
    std::vector<bool> visited(_numVertices, false); // Initialize all vertices as not visited
    std::vector<int> predecessor(_numVertices, -1); //  Initialize all predecessors as -1
    distance[startVertex] = 0; // Distance from start vertex to itself is 0
    for(int i = 0; i < _numVertices - 1; i++){ // Find shortest path for all vertices
        int u = -1;
        for(int j = 0; j < _numVertices; j++){ // Find the vertex with the minimum distance
            if(!visited[j] && (u == -1 || distance[j] < distance[u])){
                u = j;
            }
        }
        visited[u] = true; 
        for(const auto& edge : _adjacencyList[u]){ // Update distances to all adjacent vertices
            int v = edge.first;
            int weight = edge.second;
            if(distance[u] != INT_MAX && distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
                predecessor[v] = u;
            }
        }
    }
    // Display distance and path
    std::cout << "Dijkstra List: " << std::endl;
    std::cout << "Distance from " << startVertex+1 << " to " << endVertex+1;
    // Display distance and path
    if (distance[endVertex] == INT_MAX) { // If there is no path
        std::cout << ":No path" << std::endl;
    } else {
        std::cout << " is " << distance[endVertex] << " Path: ";
        std::vector<int> path;
        for (int at = endVertex; at != -1; at = predecessor[at]) { // Construct path
            path.insert(path.begin(), at);
        }
        for (int v : path) { // Print path
            std::cout << v+1 << " ";
        }
    }
    std::cout << std::endl;
}