#include "graph.h"

void DFSUtil(AdjList* graph, int vertex, int* visited, FILE* output) {
    // Mark current vertex as visited
    visited[vertex] = 1;
    
    char message[100];
    sprintf(message, "Visited vertex %d\n", vertex);
    writeOutput(output, message);
    
    // Recur for all adjacent vertices
    AdjListNode* pCrawl = graph->array[vertex];
    while (pCrawl) {
        if (!visited[pCrawl->dest]) {
            // Check firewall rules before traversing
            if (pCrawl->edge.rule.allow) {
                DFSUtil(graph, pCrawl->dest, visited, output);
            } else {
                sprintf(message, "Access denied from %d to %d due to firewall rules\n", 
                        vertex, pCrawl->dest);
                writeOutput(output, message);
            }
        }
        pCrawl = pCrawl->next;
    }
}

void DFS(AdjList* graph, int start) {
    // Open output file
    FILE* output = fopen("output.op", "a");
    if (!output) {
        printf("Error opening output file\n");
        return;
    }
    
    // Mark all vertices as not visited
    int* visited = (int*)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }
    
    writeOutput(output, "\nStarting DFS traversal...\n");
    
    // Call recursive helper function
    DFSUtil(graph, start, visited, output);
    
    free(visited);
    fclose(output);
}