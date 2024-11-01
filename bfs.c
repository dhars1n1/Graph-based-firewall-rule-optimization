#include "graph.h"

// Queue structure for BFS
typedef struct QueueNode {
    int vertex;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode *front, *rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, int vertex) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->vertex = vertex;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    
    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return -1;
    }
    
    QueueNode* temp = queue->front;
    int vertex = temp->vertex;
    
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    return vertex;
}

void BFS(AdjList* graph, int start) {
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
    
    // Create a queue for BFS
    Queue* queue = createQueue();
    
    // Mark the current vertex as visited and enqueue it
    visited[start] = 1;
    enqueue(queue, start);
    
    writeOutput(output, "\nStarting BFS traversal...\n");
    
    while (queue->front != NULL) {
        // Dequeue a vertex and print it
        int vertex = dequeue(queue);
        char message[100];
        sprintf(message, "Visited vertex %d\n", vertex);
        writeOutput(output, message);
        
        // Get all adjacent vertices
        AdjListNode* pCrawl = graph->array[vertex];
        while (pCrawl) {
            if (!visited[pCrawl->dest] && pCrawl->edge.rule.allow) {
                visited[pCrawl->dest] = 1;
                enqueue(queue, pCrawl->dest);
            } else if (!pCrawl->edge.rule.allow) {
                sprintf(message, "Access denied from %d to %d due to firewall rules\n", 
                        vertex, pCrawl->dest);
                writeOutput(output, message);
            }
            pCrawl = pCrawl->next;
        }
    }
    
    free(visited);
    fclose(output);
    free(queue);
}