#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        int k;
        for (k = 1; k < 10; k++) {
          Node *new = copy(n);
          new->sudo[i][j] = k;
          pushBack(list, new);
        }
        return list;
      }
    }
  }

  return list;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int revisarFila(int matriz[9][9], int dato,
                int indice) // analiza si esta en la fila
{
  for (int i = 0; i < 9; i++)
    if (matriz[indice][i] == dato)
      return 1;

  return 0;
}

int revisarCol(int matriz[9][9], int dato,
               int indice) // analiza si esta en la columna
{
  for (int i = 0; i < 9; i++)
    if (matriz[i][indice] == dato)
      return 1;

  return 0;
}

int is_valid(Node *n) {
  /*Ver si cada valor es unico en su fila, o su columna*/
  /*no se repita en submatriz:
      Este paso se podria hacer una vez cada que se entre a
      la submatriz*/
  /*Revisar en cada submatriz si es valido, en vez de la matriz
  entera y luego la submatriz*/
  int i, j, k;
  for (k = 1; k <= 9; k++) { // k es la submatriz
    int submatriz[10] = {0, 0, 0, 0, 0,
                         0, 0, 0, 0}; // si una posicion es 1 entonces ya existe

    for (i = 0; i < 3; i++)   // i es la fila
      for (j = 0; j < 3; j++) // j es la columna
      {
        int dato = n->sudo[i][j];
        if (dato == 0)
          continue;
        if (submatriz[dato] == 1)
          return 0;
        submatriz[dato] = 1;
        if (revisarFila(n->sudo, dato, i) == 1)
          return 0;
        if (revisarCol(n->sudo, dato, j) == 1)
          return 0;
      }
  }

  return 1;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/