#include "graph.h"

AdjMatrix* createAdjMatrix(int vertices) {
    AdjMatrix* graph = (AdjMatrix*)malloc(sizeof(AdjMatrix));
    graph->num_vertices = vertices;
    
    // Create 2D array for matrix
    graph->matrix = (Edge**)malloc(vertices * sizeof(Edge*));
    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (Edge*)malloc(vertices * sizeof(Edge));
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j].bandwidth = 0;
            graph->matrix[i][j].latency = 0;
            graph->matrix[i][j].rule.allow = 0;
        }
    }
    
    return graph;
}

void addEdgeAM(AdjMatrix* graph, int src, int dest, Edge edge) {
    // Add edge from src to dest
    graph->matrix[src][dest] = edge;
    
    // Add edge from dest to src (undirected graph)
    graph->matrix[dest][src] = edge;
}

void printAdjMatrix(AdjMatrix* graph) {
    printf("\nAdjacency Matrix Representation:\n");
    for (int i = 0; i < graph->num_vertices; i++) {
        for (int j = 0; j < graph->num_vertices; j++) {
            if (graph->matrix[i][j].bandwidth > 0) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void freeAdjMatrix(AdjMatrix* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}