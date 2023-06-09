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

int is_valid(Node *n) {

  int i, j, numSub, k;
  int mapFila[9][9] = {};
  int mapCol[9][9] = {};
  // mapa de repeticiones
  int *submatriz;
  // recorrer cada submatriz de 3x3 en el sudoku

  for (numSub = 0; numSub < 9; numSub++) // indice de la submatriz.
  {

    submatriz = calloc(9, sizeof(int)); // memoria dinamica para poder borrar
                                        // y reinicializar en 0 mas facil.
    for (k = 0; k < 9; k++)             // numeros del 1 al 9
    {
      i = 3 * (numSub / 3) + (k / 3);
      j = 3 * (numSub % 3) + (k % 3); // indice en la matriz del sudoku

      int dato = n->sudo[i][j];
      if (dato == 0)
        continue;

      if (mapFila[i][dato - 1] == 1) // Revisa si se repite en la fila
        return 0;
      else
        mapFila[i][dato - 1] = 1;

      if (mapCol[dato - 1][j] == 1) // revisa si se repite en la columna
        return 0;
      else
        mapCol[dato - 1][j] = 1;

      // Revisar submatriz

      if (submatriz[dato - 1] == 1)
        return 0;
      else
        submatriz[dato - 1] = 1;
    }

    free(submatriz); // so that it can be used malloc again
  }
  return 1;
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
          if (is_valid(new))
            pushBack(list, new);
        }
        return list;
      }
    }
  }

  return list;
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