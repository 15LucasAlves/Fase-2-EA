// Created by lucas on 23/05/2024.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create node to store matrix
typedef struct Node {
    int value; // Node numeric value«
    int column; // Node column
    int row; // Node row
} Node;

Node *head = NULL;


// Graph definition
typedef struct Graph {
    Node node;
    int id; // Node "id"
    int numVertices; // Number of existing vertices
    int numConnection; //  Number of connections made to the node

    struct Graph* right;
    struct Graph* down;
} Graph;

void loadMatrixToList(char *filename) {
    //Opens file in read mode
    FILE *file = fopen(filename, "r");

    //Verifies if the file was open
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo %s.\n", filename);
        return;
    }

    //Reads line by line
    //Each line is separated by a enter and each value by ";"
    char line[256];
    int row = 0;
    while (fgets(line, sizeof(line), file)) {

        //Token = number value
        char *token;
        token = strtok(line, ";");
        int column = 0;

        while (token != NULL) {

            //Alloc space
            Node *newNode = (Node *) malloc(sizeof(Node));

            //Create node
            newNode->value = atoi(token); //Value
            newNode->column = column; //Column
            newNode->row = row; //Row
            head = newNode; //Head now points to new node

            //Get next value
            token = strtok(NULL, ";");
            column++;
        }

        //Passar para a proxima linha
        row++;
    }
    //Fechar o ficheiro
    fclose(file);
}

// Create graph
Graph *createGraph(int numVertices, int maxNumConnections);


int main() {
    loadMatrixToList("matrix.txt");

    return 0;
}