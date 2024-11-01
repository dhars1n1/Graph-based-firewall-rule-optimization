#include "graph.h"

AdjList* createAdjList(int vertices) {
    if (vertices <= 0 || vertices > MAX_NODES) {
        printf("Invalid number of vertices: %d\n", vertices);
        return NULL;
    }
    
    AdjList* graph = (AdjList*)malloc(sizeof(AdjList));
    if (!graph) {
        printf("Failed to allocate graph structure\n");
        return NULL;
    }
    
    graph->num_vertices = vertices;
    graph->array = (AdjListNode**)malloc(vertices * sizeof(AdjListNode*));
    if (!graph->array) {
        printf("Failed to allocate adjacency list array\n");
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i < vertices; i++) {
        graph->array[i] = NULL;
    }
    
    return graph;
}

AdjListNode* createNode(int dest, Edge edge) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) {
        printf("Failed to allocate new node\n");
        return NULL;
    }
    
    newNode->dest = dest;
    newNode->edge = edge;
    newNode->next = NULL;
    return newNode;
}

void addEdgeAL(AdjList* graph, int src, int dest, Edge edge) {
    if (!graph || !graph->array) {
        printf("Invalid graph structure\n");
        return;
    }
    
    if (src < 0 || src >= graph->num_vertices || 
        dest < 0 || dest >= graph->num_vertices) {
        printf("Invalid vertex indices: %d -> %d\n", src, dest);
        return;
    }
    
    // Add edge from src to dest
    AdjListNode* newNode = createNode(dest, edge);
    if (!newNode) return;
    
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
    
    // Add edge from dest to src (undirected graph)
    newNode = createNode(src, edge);
    if (!newNode) return;
    
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}

void printAdjList(AdjList* graph) {
    if (!graph || !graph->array) {
        printf("Invalid graph structure\n");
        return;
    }
    
    for (int v = 0; v < graph->num_vertices; v++) {
        AdjListNode* pCrawl = graph->array[v];
        printf("\nAdjacency list of vertex %d\n head", v);
        while (pCrawl) {
            printf(" -> %d (BW: %d, Latency: %d)", 
                   pCrawl->dest, 
                   pCrawl->edge.bandwidth, 
                   pCrawl->edge.latency);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void freeAdjList(AdjList* graph) {
    if (!graph) return;
    
    if (graph->array) {
        for (int v = 0; v < graph->num_vertices; v++) {
            AdjListNode* current = graph->array[v];
            while (current) {
                AdjListNode* next = current->next;
                free(current);
                current = next;
            }
        }
        free(graph->array);
    }
    free(graph);
}