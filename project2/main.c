#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int numRows = 3;
int numCols = 4;

typedef struct Vertex {
    int id;
    int row;
    int col;
    int value;
    struct Vertex* next;
} Vertex;

typedef struct Graph {
    int number_of_nodes;
    Vertex** adjacencyList;
} Graph;

Vertex* createVertex(int id, int row, int col, int value) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->id = id;
    newVertex->row = row;
    newVertex->col = col;
    newVertex->value = value;
    newVertex->next = NULL;
    return newVertex;
}

Graph* initializeGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->number_of_nodes = numRows * numCols;
    graph->adjacencyList = (Vertex**)malloc(graph->number_of_nodes * sizeof(Vertex*));
    for (int i = 0; i < graph->number_of_nodes; i++) {
        graph->adjacencyList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int value) {
    Vertex* newVertex = createVertex(dest, dest / graph->number_of_nodes + 1, dest % graph->number_of_nodes + 1, value);
    newVertex->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newVertex;
}

void readFile(Graph* graph) {
    FILE* file = fopen("../cmake-build-debug/matrix.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        exit(EXIT_FAILURE);
    }

    int value;
    int id = 0;
    while (fscanf(file, "%d,", &value) == 1) {
        if (value != 0) {
            if (id / numCols < numRows - 1) { // Vertex below current node
                addEdge(graph, id, id + numCols, value);
            }
            if (id % numCols < numCols - 1) { // Vertex to the right of current node
                addEdge(graph, id, id + 1, value);
            }
        }
        id++;
    }

    fclose(file);
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->number_of_nodes; i++) {
        Vertex* temp = graph->adjacencyList[i];
        printf("\n Adjacency list of node %d\n head ", i);
        while (temp) {
            printf("-> %d", temp->id);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    Graph* graph = initializeGraph();
    readFile(graph);
    printGraph(graph);
    return 0;
}