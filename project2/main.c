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
    newVertex->row = id / numCols;
    newVertex->col = col % numCols;
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
    FILE* file = fopen("matrix.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        exit(EXIT_FAILURE);
    }


    int value;
    int number_row = 0;
    int number_col = 0;

    int id = 0;
    while (fscanf(file, "%d,", &value) == 1) {
        Vertex* newVertex = createVertex(id, number_row, number_col, value);
        newVertex->next = graph->adjacencyList[id];
        graph->adjacencyList[id] = newVertex;

        // Adds new Vertex below current node
        if (id / numCols < numRows - 1) {
            addEdge(graph, id, id + numCols, value);
        }
        // Adds new Vertex below to the right of current node
        if (id % numCols < numCols - 1) {
            addEdge(graph, id, id + 1, value);
        }

        id++;
        number_col++;
        if (number_col == numCols) {
            number_row++;
            number_col = 0;
        }
    }

    fclose(file);
}

void printGraphAsMatrix(Graph* graph) {
    int counter = 0;
    printf("\n");

    for (int i = 0; i <= graph->number_of_nodes; i++) {
        Vertex* temp = graph->adjacencyList[i];
        if(temp == NULL){
            printf("0 ");
        } else {
            printf("%d ", temp->value);
        }
        counter++;
        if (counter == numCols) {
            printf("\n");
            counter = 0;
        }
    }
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->number_of_nodes; i++) {
        // Gets the adjacencyList and atributes it to temp
        Vertex* temp = graph->adjacencyList[i];
        // Prints Node id
        printf("\nAdjacency list of node %d\n head ", i);
        while (temp) {
            // Prints Adjacents nodes id's
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
    printGraphAsMatrix(graph);
    return 0;
}