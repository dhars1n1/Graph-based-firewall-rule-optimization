#include "graph.h"

void readInput(const char* filename, AdjList** adjList, AdjMatrix** adjMatrix) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening input file: %s\n", filename);
        return;
    }
    
    int num_vertices, num_edges;
    if (fscanf(fp, "%d %d", &num_vertices, &num_edges) != 2) {
        printf("Error reading number of vertices and edges\n");
        fclose(fp);
        return;
    }
    
    printf("Creating graph with %d vertices and %d edges\n", num_vertices, num_edges);
    
    if (num_vertices <= 0 || num_vertices > MAX_NODES || num_edges <= 0) {
        printf("Invalid number of vertices or edges\n");
        fclose(fp);
        return;
    }
    
    *adjList = createAdjList(num_vertices);
    *adjMatrix = createAdjMatrix(num_vertices);
    
    if (!*adjList || !*adjMatrix) {
        printf("Failed to create graph structures\n");
        fclose(fp);
        return;
    }
    
    char line[256];
    // Skip any remaining characters on the first line
    fgets(line, sizeof(line), fp);
    
    // Read edges and their properties
    for (int i = 0; i < num_edges; i++) {
        int src, dest, bandwidth, latency;
        char source_ip[MAX_IP_LENGTH], dest_ip[MAX_IP_LENGTH];
        int allow;
        int security_level_int;
        
        if (fgets(line, sizeof(line), fp) == NULL) {
            printf("Error reading line %d\n", i + 1);
            break;
        }
        
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') {
            i--;
            continue;
        }
        
        int result = sscanf(line, "%d %d %d %d %s %s %d %d",
                           &src, &dest, &bandwidth, &latency,
                           source_ip, dest_ip, &allow, &security_level_int);
        
        if (result != 8) {
            printf("Error parsing line %d: got %d values\n", i + 1, result);
            continue;
        }
        
        // Validate input values
        if (src < 0 || src >= num_vertices || dest < 0 || dest >= num_vertices) {
            printf("Invalid vertex indices on line %d: %d -> %d\n", i + 1, src, dest);
            continue;
        }
        
        printf("Adding edge %d -> %d (BW: %d, Latency: %d)\n", 
               src, dest, bandwidth, latency);
        
        Edge edge;
        edge.bandwidth = bandwidth;
        edge.latency = latency;
        strncpy(edge.rule.source_ip, source_ip, MAX_IP_LENGTH - 1);
        edge.rule.source_ip[MAX_IP_LENGTH - 1] = '\0';
        strncpy(edge.rule.dest_ip, dest_ip, MAX_IP_LENGTH - 1);
        edge.rule.dest_ip[MAX_IP_LENGTH - 1] = '\0';
        edge.rule.allow = allow;
        
        switch(security_level_int) {
            case 0:
                edge.rule.security_level = LOW;
                break;
            case 1:
                edge.rule.security_level = MEDIUM;
                break;
            case 2:
                edge.rule.security_level = HIGH;
                break;
            default:
                edge.rule.security_level = LOW;
                break;
        }
        
        addEdgeAL(*adjList, src, dest, edge);
        addEdgeAM(*adjMatrix, src, dest, edge);
    }
    
    fclose(fp);
}

int main() {
    AdjList* adjList = NULL;
    AdjMatrix* adjMatrix = NULL;
    
    // Clear output file
    FILE* output = fopen("output.op", "w");
    if (!output) {
        printf("Error opening output file\n");
        return 1;
    }
    fprintf(output, "Network Analysis Results\n");
    fprintf(output, "=======================\n");
    fclose(output);
    
    printf("Reading input file...\n");
    readInput("input.ip", &adjList, &adjMatrix);
    
    if (!adjList || !adjMatrix) {
        printf("Error creating graph representations\n");
        return 1;
    }
    
    printf("\nAdjacency List Representation:\n");
    printAdjList(adjList);
    
    printf("\nAdjacency Matrix Representation:\n");
    printAdjMatrix(adjMatrix);
    
    printf("\nRunning graph algorithms...\n");
    
    output = fopen("output.op", "a");
    if (!output) {
        printf("Error opening output file for algorithms\n");
        freeAdjList(adjList);
        freeAdjMatrix(adjMatrix);
        return 1;
    }
    
    fprintf(output, "\nStarting graph traversals...\n");
    fclose(output);
    
    // DFS from vertex 0
    printf("Running DFS...\n");
    DFS(adjList, 0);
    
    // BFS from vertex 0
    printf("Running BFS...\n");
    BFS(adjList, 0);
    
    // Find shortest paths from vertex 0
    printf("Running Dijkstra's algorithm...\n");
    Dijkstra(adjList, 0);
    
    // Find minimum spanning tree from vertex 0
    printf("Running Prim's algorithm...\n");
    Prim(adjList, 0);
    
    // Clean up
    freeAdjList(adjList);
    freeAdjMatrix(adjMatrix);
    
    printf("\nAnalysis complete. Check output.op for results.\n");
    
    return 0;
}