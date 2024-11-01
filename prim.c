#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#define INF 999999

int findMinKey(int key[], int mstSet[], int V) {
    int min = INF;
    int min_index = -1;
    
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    
    if (min_index == -1) {
        printf("Error: No valid vertex found\n");
        exit(1);
    }
    
    return min_index;
}

void printMST(int parent[], AdjList* graph, FILE* output) {
    if (!graph || !output || !parent) {
        printf("Invalid parameters in printMST\n");
        return;
    }

    writeOutput(output, "\nEdges in the Minimum Spanning Tree:\n");
    
    for (int i = 1; i < graph->num_vertices; i++) {
        if (parent[i] < 0 || parent[i] >= graph->num_vertices) {
            printf("Invalid parent index: %d\n", parent[i]);
            continue;
        }
        
        AdjListNode* pCrawl = graph->array[parent[i]];
        if (!pCrawl) {
            printf("Invalid graph node at index %d\n", parent[i]);
            continue;
        }

        while (pCrawl && pCrawl->dest != i) {
            pCrawl = pCrawl->next;
        }
        
        if (pCrawl) {
            char message[200];
            sprintf(message, "Edge: %d - %d, Bandwidth: %d, Latency: %d\n", 
                    parent[i], i, pCrawl->edge.bandwidth, pCrawl->edge.latency);
            writeOutput(output, message);
        }
    }
}

void Prim(AdjList* graph, int start) {
    if (!graph || start < 0 || start >= graph->num_vertices) {
        printf("Invalid parameters for Prim's algorithm\n");
        return;
    }

    FILE* output = fopen("output.op", "a");
    if (!output) {
        printf("Error opening output file\n");
        return;
    }
    
    int V = graph->num_vertices;
    int* parent = (int*)malloc(V * sizeof(int));
    int* key = (int*)malloc(V * sizeof(int));
    int* mstSet = (int*)malloc(V * sizeof(int));
    
    if (!parent || !key || !mstSet) {
        printf("Memory allocation failed\n");
        fclose(output);
        return;
    }
    
    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = 0;
        parent[i] = -1;
    }
    
    // Start with the first vertex
    key[start] = 0;
    parent[start] = -1;
    
    writeOutput(output, "\nStarting Prim's algorithm...\n");
    
    // Construct MST with V vertices
    for (int count = 0; count < V - 1; count++) {
        int u = findMinKey(key, mstSet, V);
        mstSet[u] = 1;
        
        AdjListNode* pCrawl = graph->array[u];
        while (pCrawl) {
            int v = pCrawl->dest;
            
            if (mstSet[v] == 0 && pCrawl->edge.rule.allow && 
                pCrawl->edge.bandwidth < key[v]) {
                parent[v] = u;
                key[v] = pCrawl->edge.bandwidth;
                
                char message[100];
                sprintf(message, "Updated vertex %d, parent: %d, bandwidth: %d\n", 
                        v, u, key[v]);
                writeOutput(output, message);
            } else if (!pCrawl->edge.rule.allow) {
                char message[100];
                sprintf(message, "Skipping edge %d-%d due to firewall rules\n", u, v);
                writeOutput(output, message);
            }
            
            pCrawl = pCrawl->next;
        }
    }
    
    printMST(parent, graph, output);
    
    int total_bandwidth = 0;
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            AdjListNode* pCrawl = graph->array[parent[i]];
            while (pCrawl && pCrawl->dest != i) {
                pCrawl = pCrawl->next;
            }
            if (pCrawl) {
                total_bandwidth += pCrawl->edge.bandwidth;
            }
        }
    }
    
    char summary[100];
    sprintf(summary, "\nTotal network bandwidth in MST: %d\n", total_bandwidth);
    writeOutput(output, summary);
    
    free(parent);
    free(key);
    free(mstSet);
    fclose(output);
}