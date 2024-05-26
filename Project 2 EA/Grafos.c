//
// Created by lucas on 24/05/2024.
//
// Ficheiro principal que contem a maioria das funções relacionadas com a construção do grafo
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Grafos.h"

// Variaveis globais
int nColunas = 0; // numero total de colunas da matriz gerada pelo programa
int nLinhas = 0; // numero total de linhas da matriz gerada pelo programa



// Função para adiconar um valor no topo da pilha
// Mandar para dentro fa função a nossa pilha, um id e um valor
Pilha push(Pilha pilha, int id, int valor){

    // Alocar espaço para a nova instancia na pilha e do vertice
    Pilha newInstance = (Pilha) malloc(sizeof(struct pilha));
    Vertice newVertice = (Vertice) malloc(sizeof(struct vertice));

    // Se existir uma nova instancia
    if (newInstance != NULL && newVertice != NULL){

        // Designar os novos valores
        newInstance->id = id;
        newInstance->Vertice = newVertice;
        newInstance->Vertice->valor = valor;
        newInstance->Vertice->direita = NULL;
        newInstance->Vertice->baixo = NULL;

        // Apontar para a proxima instancia da pilha
        newInstance->proximo = pilha;

        while(pilha != NULL){

            // Se a nova instancia da pilha se encontrar á direita, da instancia atual da pilha, na matriz, criar a ligação da aresta atravez do apontador
            if (newInstance->id == pilha->id + 1 && pilha->id % nColunas != 0){
                    pilha->Vertice->direita = newInstance;
            }
            // Se a nova instancia da pilha se encontrar em baixo, da instancia atual da pilha, na matriz, criar a ligação da aresta atravez do apontador
            else if (newInstance->id == pilha->id + nColunas){
                pilha->Vertice->baixo = newInstance;
            }

            pilha = pilha->proximo;
        }

        // Retornar a nova instancia
        return (newInstance);
    }
    else{
        return (pilha);
    }
}



// Função para remover o valor no topo da pilha
// Mandar para dentro da função a nossa pilha
Pilha pop(Pilha pilha){

    // Criar uma instancia temporaria da pilha
    Pilha aux;

    if(pilha != NULL){
        // Designar a instancia temporaria como a proxima
        aux = pilha->proximo;
        // Libertar a instancia da pilha e do vertice
        free(pilha->Vertice);
        free(pilha);

        return aux;
    }
    else{
        return pilha;
    }
}



// Função para a leitura do ficheiro e carregamento das variaveis necessarias para a contrução dos vertices e da lista
Pilha readAndLoadFile(char *fileName, Pilha pilha){

    // Abir o ficheiro em read mode
    FILE *file = fopen(fileName, "r");

    // Verificar se o ficheiro foi aberto
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo %s.\n", fileName);
        return pilha;
    }

    char line[256];
    char lineCopy[256];
    char *token;
    int id = 0;
    int row = 0;
    int column = 0;
    nColunas = 0;
    nLinhas = 0;

    while (fgets(line, sizeof(line), file)) {

        if (nColunas == 0){
            // Cria uma copia da linha para poder verificar o numero de colunas sem alterar a linha original
            strcpy(lineCopy, line);
            token = strtok(lineCopy, ";");

            while (token != NULL) {
                token = strtok(NULL, ";");
                column++;
            }

            // Igualar o nº de colunas ao nº de colunas da matriz do ficheiro para mais tarde iterar
            nColunas = column;
        }

        // Token = valor do numero, ele considera o valor até ao ";"
        token = strtok(line, ";");

        // Ler os valores até ao final da linha
        while (token != NULL) {
            // printf("%d ", atoi(token));

            pilha = push(pilha, ++id,atoi(token));

            // Ler o proximo valor
            token = strtok(NULL, ";");
        }
        // Adicionar +1 a row para manter a informação dentro dos vertices atualizadas
        row++;
    }

    // Igualar o nº de linhas ao nº de linhas da matriz do ficheiro para mais tarde iterar
    nLinhas = row;

    // Fechar o ficheiro
    fclose(file);

    return pilha;
}



// Função para imprimir a matriz a partir da pilha
void printMatriz(Pilha pilha){

    if(pilha != NULL){

        // Atravez de recursividade representamos a pilha na ordem contraria pois o nosso primeiro valor da matriz encontra-se no fundo da pilha
        printMatriz(pilha->proximo);

        // Print no valor do vertice atual
        printf("%d ", pilha->Vertice->valor);

        // Dar um enter sempre que chefa ao valor final da linha
        if (pilha->id % nColunas == 0){
            printf("\n");
        }
    }
}



void printListaAdjacencia(Pilha pilha){
    if(pilha != NULL){

        // Atravez de recursividade representamos a pilha na ordem contraria pois o nosso primeiro valor da matriz encontra-se no fundo da pilha
        printListaAdjacencia(pilha->proximo);

        // Print no id do vertice atual
        printf("Id Vertice %d\n", pilha->id);

        // Print nas aresta ou caminhos possiveis a tomar a partir do vertice atual
        if(pilha->Vertice->direita != NULL){
            printf("Destino da aresta da direita %d\n", pilha->Vertice->direita->id);
        }
        else{
            printf("Destino da aresta da direita nao existe\n");
        }

        if(pilha->Vertice->baixo != NULL){
            printf("Destino da aresta de baixo %d\n", pilha->Vertice->baixo->id);
        }
        else{
            printf("Destino da aresta de baixo nao existe\n");
        }

        printf("\n");
    }
}



// Função para trocar um valor especifico da matriz
void trocarValor(Pilha pilha, int coluna, int linha, int novoValor){
    if(pilha != NULL){

        // Passar por todos os valores
        while(pilha != NULL){
            // Conta para obter o id certo para a partir da posição da matriz
            if(pilha->id == (linha * nColunas) - (nColunas - coluna)){
                // Atribuir novo valor
                pilha->Vertice->valor = novoValor;
                return; // Parar se encontrou o valor a trocar
            }

            pilha = pilha->proximo;
        }
    }
}



// Função para refazer as arestas atravez do id das instancias da pilha
void refazerArestas(Pilha pilha){
    Pilha tempFirst = pilha;
    Pilha tempSecond = pilha;

    while(tempFirst != NULL) {
        // Caso a instancia seja correspondente a um valor da ultima coluna, dar set da aresta da direita para NULL
        if(tempFirst->id % nColunas == 0){
            //printf("rescrever caminho direita NULL do id: %d\n", tempFirst->id);
            tempFirst->Vertice->direita = NULL;
        }
        // Caso a instancia seja correspondente a um valor da ultima linha, dar set da aresta de baixo para NULL
        if(tempFirst->id > (nLinhas - 1) * nColunas) {
            //printf("rescrever caminho baixo NULL do id: %d\n",  tempFirst->id);
            tempFirst->Vertice->baixo = NULL;
        }

        while (tempSecond != NULL) {
            // Caso a tempSecond seja correspondente ao valor da matriz esquerdo do tempFirst, aresta da direita apontar para tempFirst
            if (tempFirst->id == tempSecond->id + 1 && tempSecond->id % nColunas != 0) {
                //printf("rescrever caminho direita do id: %d - %d\n", tempFirst->id, tempSecond->id);
                tempSecond->Vertice->direita = tempFirst;
            }
            // Caso a tempSecond seja correspondente ao valor da matriz de baixo do tempFirst, aresta de baixo apontar para tempFirst
            else if (tempFirst->id == tempSecond->id + nColunas) {
                //printf("rescrever caminho baixo do id: %d - %d\n", tempFirst->id, tempSecond->id);
                tempSecond->Vertice->baixo = tempFirst;
            }
            tempSecond = tempSecond->proximo;
        }
        // tempSecond volta a apontar para o topo da pilha
        tempSecond = pilha;
        tempFirst = tempFirst->proximo;
    }
}



// Função para criar uma linha com novos valores
Pilha pushLinha(Pilha pilha, int id){
    int novoValor = 0;

    for (int i = 0; i < nColunas; i++){
        printf("\nInsira o novo valor para a %d pos: ", i+1);
        scanf("%d", &novoValor);
        pilha = push(pilha,id + i,novoValor);
    }
    return pilha;
}



// Função para adicionar uma linha á matriz
Pilha adicionarLinha(Pilha pilha, int linha) {
    // Criar uma pilha para retornar o topo
    Pilha returnTopPilha = pilha;
    // Criar uma pilha temporaria
    Pilha tempPilha = NULL;

    if(pilha != NULL){
        // Caso a linha a ser criada seja uma nova ultima linha
        if(linha == nLinhas + 1){
            // Utilizando o pushLinha criar uma nova linha com novos valores no fim da matriz
            // Retornar o novo topo da pilha
            returnTopPilha = pushLinha(pilha, pilha->id+1);
        }
        // Caso a linha a ser criada seja uma nova primeira linha
        else if (linha == 1){
            // Ir até a instancia com id 1
            while (pilha->id > 1){
                // Alterar os ids de todos as instancias anteriores
                pilha->id = pilha->id + nColunas;
                pilha = pilha->proximo;
            }
            // Alterar o id da instancia 1
            pilha->id = pilha->id + nColunas;
            // Utilizando o pushLinha criar uma nova linha com novos valores no inicio da matriz
            pilha->proximo = pushLinha(NULL, 1);
        }
        else {
            // Ir até a instancia com id - 1 da linha a ser criada
            while (pilha->id >= (linha - 1) * nColunas){
                // Se chegarmos á instancia que vair ser a proxima da nova linha criar nova linha e ligar á instancia temporaria
                if (pilha->id == (linha - 1) * nColunas){
                    tempPilha->proximo = pushLinha(pilha, pilha->id+1);
                    break;
                }
                // Alterar os ids das instancias anteriores e guardar um temp para poder ligar a pilha
                else{
                    tempPilha = pilha;
                    pilha->id = pilha->id + nColunas;
                    pilha = pilha->proximo;
                }
            }
        }
    }
    // Retornar o topo da pilha
    return returnTopPilha;
}



// Criar pilha temp global para quando usar recursão não resetar o valor
Pilha temp = NULL;
// Função de remoção de linha
Pilha removerLinha(Pilha pilha, int linha, bool pararRecursao){

    if(pilha != NULL){
        // Se a linha removida for a ultima da matriz
        if (linha == nLinhas){
            // Enquanto que o id for correspondente a um id da ultima linha
            while (pilha->id > (nLinhas - 1) * nColunas){
                // Dar pop do topo da pilha sem retornar
                pilha = pop(pilha);
            }
            // Retornar a pilha alterada sem a ultima linha
            return pilha;
        }
        // Se a linha removida não for a ultima da matriz
        else {

            // Procurar se a instancia atual da pilha é a 1ª instancia asseguir da linha a ser removida
            if (pilha->id == nColunas * (linha - 1)) {
                // Parar de fazer recursão já que não necessitamos de ir mais para a frente na pilha
                pararRecursao = true;
                // Guardar o endereço que vamos ter de fazer ligação com, depois de libertar as instancias que vão ser removidas
                temp = pilha;
                // Retornar a pilha para voltar na recursão
                return pilha;
            }

            // Se necessitar de fazer recursão, entrar na função outra vez com a proxima instancia da pilha
            if (!pararRecursao) {
                removerLinha(pilha->proximo, linha, pararRecursao);
            }

            // Se o id for um dos correspondentes a ser eleminado, pop da instancia atual da pilha e retornar para não continuar a função
            if (pilha->id > nColunas * (linha - 1) && pilha->id <= nColunas * linha) {
                return pop(pilha);
            }

            // Se o id da instancia for correspondente a uma linha superior a que desejamos eleminar
            if (pilha->id > nColunas * linha) {
                // Caso a linha que foi eleminada seja a primeira, o apontador do novo id 1 esta a apontar para o nullo
                if (linha == 1 && pilha->id == (nColunas * linha) + 1){
                    pilha->proximo = NULL;
                }
                // Caso a linha que foi eleminada não seja a primeira, o apontador do novo id da primeira coluna da linha eleminada esta a apontar para o temp
                else if (pilha->id == (nColunas * linha) + 1) {
                    // Dar assing ao proximo da lista como o temporario
                    pilha->proximo = temp;
                }
                // Atualizar os ids conforme o nº de elementos eleminados
                pilha->id = pilha->id - nColunas;
            }
        }
    }
    // Retornar a pilha atualizada
    return pilha;
}



// Função para adicionar uma coluna a matriz
Pilha adicionarColuna(Pilha pilha, int coluna){
    // Criar uma pilha para retornar o topo
    Pilha returnTopPilha = pilha;
    // Estancia temporaria para auxiliar nas ligações da pilha
    Pilha tempColuna = NULL;

    int id = nLinhas * (nColunas + 1);
    int linha = nLinhas;
    int novoValor = 0;

    if (pilha != NULL){
        // Ciclo while para passar por todas as instancias da pilha
        while (pilha != NULL){

            // Caso o id da instancia atual seja da coluna que desejamos trocar para adicionar a nova salvar temporariamente a instancia
            if(pilha->id == coluna + ((linha - 1) * nColunas)){
                tempColuna = pilha;
            }

            // Caso o id da instancia atual seja da coluna - 1 da que queremos adicionar
            if(pilha->id == coluna + ((linha - 1) * nColunas) - 1){
                // Pedir novo valor e criar nova instancia
                printf("\nInsira o novo valor para a %d pos: ", linha);
                scanf("%d", &novoValor);
                pilha = push(pilha,id,novoValor);

                // Caso o novo valor se encontre no topo da pilha
                if (coluna == nColunas + 1 && linha == nLinhas){
                    // Atualizar o topo da pilha
                    returnTopPilha = pilha;
                }
                else{
                    // Atualizar a ligação do proximo
                    tempColuna->proximo = pilha;
                }
                // Atualizar linha atual
                linha--;
            }

            // Atualizar o id da instancia atual
            pilha->id = id;
            id--;

            // Caso o id da instancia atual seja
            if (id == 1 && coluna == 1){
                printf("\nInsira o novo valor para a %d pos: ", linha);
                scanf("%d", &novoValor);
                // Criar nova instancia com id 1
                tempColuna->proximo = push(NULL,id,novoValor);
            }

            pilha = pilha->proximo;
        }
    }
    // Retornar topo da pilha
    return returnTopPilha;
}



// Função para remoção de uma coluna
Pilha removerColuna(Pilha pilha, int coluna){
    // Criar uma pilha para retornar o topo
    Pilha returnTopPilha = pilha;
    // Criar uma pilha temporaria nulla para armazenar o id anterior da coluna a ser removida quando essa for a ultima coluna
    Pilha tempPilha = NULL;
    int linha = nLinhas;

    if(pilha != NULL){

        // Fazer até chegar a coluna da primeira linha
        while(pilha->id >= coluna){

            // Armazenar o id anterior da coluna a ser removida quando essa for a ultima coluna
            if(pilha->id == coluna + 1 + ((linha - 1) * nColunas) && coluna == nColunas) {
                tempPilha = pilha;
            }

            // Se o id da instancia atual for a da coluna a ser removida
            if(pilha->id == coluna + ((linha - 1) * nColunas)){
                // Se estivermos a remover a instancia da lista com o id 1 meter a apontar a instancia anterior para o NULL
                if(coluna == 1 && pilha->id == 1){
                    pilha->Vertice->direita->proximo = NULL;
                }
                // Apontar a aresta direita da proxima instancia para a aresta direita da instancia atual
                else{
                    pilha->proximo->Vertice->direita = pilha->Vertice->direita;
                }

                // Se a coluna a ser removida for a ultima
                if(coluna == nColunas){
                    // E se o id da instancia atual for o ultimo
                    if(nLinhas==linha) {
                        // Retornar igualar o topo da pilha á pilha sem a ultima instancia
                        returnTopPilha = pilha->proximo;
                    }
                    // Caso não seja o ultimo id
                    else {
                        // Rearranjar o caminho para manter a pilha organizada
                        tempPilha->proximo = pilha->proximo;
                    }
                }
                // Se a coluna a ser removida não for a ultima
                else{
                    // Rearranjar o caminho para manter a pilha organizada
                    pilha->Vertice->direita->proximo = pilha->proximo;
                }

                // Remover a instancia da pilha
                pilha = pop(pilha);
                linha--;
                // Para não dar crash caso tenha de remover a instancia com id 1
                if(pilha == NULL){
                    return returnTopPilha;
                }
            }
            // Se a instancia não for uma das que necessitamos de remover
            else{
                // Atualizar os ids
                // Todos os ids que estão para lá da coluna a ser removida retiramos o nº de colunas
                if(pilha->id > coluna + ((linha - 1) * nColunas)) {
                    pilha->id = pilha->id - linha;
                }
                // Todos os ids que estão para cá da coluna a ser removida retiramos o nº de colunas - 1
                else{
                    pilha->id = pilha->id - (linha - 1);
                }

                pilha = pilha->proximo;
            }
        }
    }
    // Retornar o topo da pilha
    return returnTopPilha;
}



// Função principal têm a escolha da matriz inicial e o program loop
int main(void) {
    int escolha = 0;
    int coluna = 0;
    int linha = 0;
    int novoValor = 0;
    bool endProgram = false;

    // Criar uma instancia nulla da pilha para poder adicionar valores
    Pilha pilha = NULL;

    printf("\nEscolha a matriz que deseja para inicar o programa:\n\n");
    printf("A disposição das matrizes é de linha x coluna\n\n");
    printf("1 - Matriz 3x4\n");
    printf("2 - Matriz 3x2\n");
    printf("3 - Matriz 4x5\n\n");

    printf("Insira a sua escolha: ");
    scanf("%d", &escolha);
    printf("\n");

    switch (escolha) {
        case 1:
            pilha = readAndLoadFile("matrix1.txt", pilha);
            break;

        case 2:
            pilha = readAndLoadFile("matrix2.txt", pilha);
            break;

        case 3:
            pilha = readAndLoadFile("matrix3.txt", pilha);
            break;

        default:
            printf("Escolha invalida iniciando o programa com a opção 1...\n\n");
            pilha = readAndLoadFile("matrix1.txt", pilha);
            break;
    }

    do{
        printf("\n");
        printMatriz(pilha);

        printf("\nEscolha o que fazer:\n");
        printf("1. Trocar o valor de um elemento\n");
        printf("2. Adicionar uma linha\n");
        printf("3. Remover uma linha\n");
        printf("4. Adicionar uma coluna\n");
        printf("5. Remover uma coluna\n");
        printf("6. Listar os ids e todos adjacentes\n");
        printf("7. Calcular o caminho com a maior soma\n");
        printf("0. Sair\n\n");
        printf("Insira a sua escolha: ");
        scanf("%d", &escolha);
        printf("\n");

        switch (escolha) {
            case 1:

                printf(" Linha do elemento: ");
                scanf("%d", &linha);
                if (linha > nLinhas && linha < 0){
                    printf("Linha invalida...\n");
                    break;
                }

                printf("Coluna do elemento: ");
                scanf("%d", &coluna);
                if (coluna > nColunas && coluna < 0){
                    printf("Coluna invalida...\n");
                    break;
                }

                printf("Insira o novo valor: ");
                scanf("%d",&novoValor);

                trocarValor(pilha,coluna,linha,novoValor);

                break;

            case 2:
                printf("Insira o numero da linha que deseja adicionar: ");
                scanf("%d", &linha);
                if (linha > nLinhas + 1 && linha < 0){
                    printf("Linha invalida...\n");
                    break;
                }

                pilha = adicionarLinha(pilha,linha);
                nLinhas++;
                refazerArestas(pilha);

                break;

            case 3:
                if (nLinhas == 1) {
                    printf("Nao pode remover a ultima linha!\n");
                    break;
                }

                printf("Insira o numero da linha que deseja remover: ");
                scanf("%d", &linha);
                if (linha > nLinhas && linha < 0){
                    printf("Linha invalida...\n");
                    break;
                }

                pilha = removerLinha(pilha,linha, false);
                nLinhas--;
                refazerArestas(pilha);

                break;

            case 4:
                printf("Insira o numero da coluna que deseja adicionar: ");
                scanf("%d", &coluna);
                if (linha > nColunas + 1 && coluna < 0){
                    printf("Coluna invalida...\n");
                    break;
                }

                pilha = adicionarColuna(pilha,coluna);
                nColunas++;
                refazerArestas(pilha);
                break;

            case 5:
                if (nColunas == 1) {
                    printf("Nao pode remover a ultima coluna!\n");
                    break;
                }

                printf("Insira o numero da coluna que deseja remover: ");
                scanf("%d", &coluna);
                if (coluna > nColunas && coluna < 0){
                    printf("Coluna invalida...\n");
                    break;
                }

                pilha = removerColuna(pilha, coluna);
                nColunas--;

                break;

            case 6:
                printListaAdjacencia(pilha);
                break;

            case 7:

                break;

            case 0:
                endProgram = true;
                break;

            default:
                printf("Escolha invalida...\n\n");
                break;
        }
    }while (endProgram != true);

    return 0;
}