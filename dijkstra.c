#include "graph.h"
#include<string.h>
#define INF 999999

int minDistance(int dist[], int sptSet[], int V) {
    int min = INF, min_index;
    
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

void Dijkstra(AdjList* graph, int start) {
    FILE* output = fopen("output.op", "a");
    if (!output) {
        printf("Error opening output file\n");
        return;
    }
    
    int V = graph->num_vertices;
    int dist[V];
    int sptSet[V];
    int parent[V];
    
    // Initialize distances and visited array
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
        parent[i] = -1;
    }
    
    dist[start] = 0;
    
    writeOutput(output, "\nStarting Dijkstra's algorithm...\n");
    
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = 1;
        
        // Update dist value of adjacent vertices
        AdjListNode* pCrawl = graph->array[u];
        while (pCrawl) {
            int v = pCrawl->dest;
            
            if (!sptSet[v] && pCrawl->edge.rule.allow && 
                dist[u] != INF && 
                dist[u] + pCrawl->edge.latency < dist[v]) {
                dist[v] = dist[u] + pCrawl->edge.latency;
                parent[v] = u;
            }
            pCrawl = pCrawl->next;
        }
    }
    
    // Print the results
    for (int i = 0; i < V; i++) {
        if (i != start && dist[i] != INF) {
            char message[200];
            sprintf(message, "Shortest path from %d to %d: Distance = %d\n", 
                    start, i, dist[i]);
            writeOutput(output, message);
            
            // Print the path
            int current = i;
            char path[1000] = "";
            while (current != -1) {
                char temp[10];
                sprintf(temp, "%d ", current);
                strcat(path, temp);
                current = parent[current];
            }
            strcat(path, "\n");
            writeOutput(output, path);
        }
    }
    
    fclose(output);
}