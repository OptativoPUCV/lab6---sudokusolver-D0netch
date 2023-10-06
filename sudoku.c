#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {
    int marca_fila[9][10] = {0}; 
    int marca_col[9][10] = {0};  
    int marca_subMatriz[9][10] = {0};  

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];

            if (num == 0)
                continue; 

            if (marca_fila[i][num] == 1)
                return 0;
            marca_fila[i][num] = 1;

            if (marca_col[j][num] == 1)
                return 0; 
            marca_col[j][num] = 1;

            int subMatriz = 3 * (i / 3) + (j / 3);

            if (marca_subMatriz[subMatriz][num] == 1)
                return 0;

            marca_subMatriz[subMatriz][num] = 1;
        }
    }

    return 1;
}

List* get_adj_nodes(Node* n) {
    List* lista_nodos_validos = createList();
    int i, j;
    int fila = -1, col = -1;

    for (i = 0; i < 9 && fila == -1; i++) {
        for (j = 0; j < 9 && col == -1; j++) {
            if (n->sudo[i][j] == 0) {
                fila = i;
                col = j;
            }
        }
    }

    if (fila == -1 || col == -1)
        return lista_nodos_validos;

    for (int k = 1; k <= 9; k++) {
        Node* nodo_adyacente = copy(n);
        nodo_adyacente->sudo[fila][col] = k;

        if (is_valid(nodo_adyacente)) {
            pushBack(lista_nodos_validos, nodo_adyacente);
        } else {
            free(nodo_adyacente);
        }
    }

    return lista_nodos_validos;
}

int is_final(Node* n) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* stack = createStack();
    push(stack, n);

    while (!isEmpty(stack)) {
        (*cont)++;

        Node* current = top(stack);
        pop(stack);

        if (is_final(current)) {
            return current;
        }

        List* adj_nodes = get_adj_nodes(current);
        Node* temp_node = adj_nodes->first;

        while (temp_node != NULL) {
            push(stack, temp_node->data);
            temp_node = temp_node->next;
        }

        free(current);
    }

    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/