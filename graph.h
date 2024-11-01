#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_IP_LENGTH 16
#define MAX_RULE_LENGTH 50

// Security levels
typedef enum {
    LOW,
    MEDIUM,
    HIGH
} SecurityLevel;

// Firewall rule structure
typedef struct {
    char source_ip[MAX_IP_LENGTH];
    char dest_ip[MAX_IP_LENGTH];
    int allow;  // 1 for allow, 0 for deny
    SecurityLevel security_level;
} FirewallRule;

// Edge structure for both adjacency list and matrix
typedef struct {
    int bandwidth;
    int latency;
    FirewallRule rule;
} Edge;

// Node for adjacency list
typedef struct AdjListNode {
    int dest;
    Edge edge;
    struct AdjListNode* next;
} AdjListNode;

// Adjacency List representation
typedef struct {
    int num_vertices;
    AdjListNode** array;
} AdjList;

// Adjacency Matrix representation
typedef struct {
    int num_vertices;
    Edge** matrix;
} AdjMatrix;

// Function declarations for adjacency list
AdjList* createAdjList(int vertices);
void addEdgeAL(AdjList* graph, int src, int dest, Edge edge);
void printAdjList(AdjList* graph);
void freeAdjList(AdjList* graph);

// Function declarations for adjacency matrix
AdjMatrix* createAdjMatrix(int vertices);
void addEdgeAM(AdjMatrix* graph, int src, int dest, Edge edge);
void printAdjMatrix(AdjMatrix* graph);
void freeAdjMatrix(AdjMatrix* graph);

// Graph algorithm declarations
void DFS(AdjList* graph, int start);
void BFS(AdjList* graph, int start);
void Dijkstra(AdjList* graph, int start);
void Prim(AdjList* graph, int start);

// Utility functions
int isValidPath(FirewallRule rule, char* source_ip, char* dest_ip);

// Implementation of writeOutput function
static inline void writeOutput(FILE* fp, const char* message) {
    if (fp) {
        fprintf(fp, "%s", message);
        fflush(fp);
    }
}

#endif