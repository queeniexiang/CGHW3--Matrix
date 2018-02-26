#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ml6.h"
#include "display.c"
#include "draw.c"
#include "matrix.c"


int main() {

  
  screen s;
  clear_screen(s);
  color c;
  c.red = 255;

  struct matrix * matrix_a = new_matrix(2,2);
  struct matrix * matrix_b = new_matrix(2,2);
  struct matrix * matrix_c = new_matrix(2,2);
  matrix_a->lastcol=2;
  matrix_b->lastcol=2;
  matrix_c->lastcol=2;
  
  printf("\nMaking matrix a into an identity matrix");
  ident(matrix_a);
  print_matrix(matrix_a);

  matrix_b->m[0][0]=1;
  matrix_b->m[0][1]=10;
  matrix_b->m[1][1]=17;
  printf("\nPrinting matrix b with numbers\n");
  print_matrix(matrix_b);
  
  printf("\nTesting matrix multiplication!\n");
  printf("Multiplying matrix b with matrix a: \n");
  matrix_mult(matrix_a, matrix_b);
  printf("Results:\n"); 
  print_matrix(matrix_b);
  
  matrix_c->m[0][0]=1;
  matrix_c->m[0][1]=0;
  matrix_c->m[1][0]=11;
  matrix_c->m[1][1]=3;
  
  printf("\nPrinting matrix c with numbers\n");
  print_matrix(matrix_c);

  printf("\nTesting matrix multiplication with matrix b and c\n");
  matrix_mult(matrix_b, matrix_c);
  printf("\nresult\n");
  print_matrix(matrix_c);

  free_matrix(matrix_b);
  free_matrix(matrix_c);

  struct matrix * edges = new_matrix(4,4);

  srand(time(NULL)); 

  int counter = rand()%100;
  int counter2 = rand()%40;

  for (; counter > 0; counter--) {
    for (; counter2 > 0; counter2--) {
      c.red = rand()%255;
      c.green = rand()%200;
      c.blue = rand()%200; 
      add_edge(edges, counter+500, counter2+500, 0, (counter+rand()%200), (counter+rand()%100), 0); 
      add_edge(edges,counter,counter2,0, (counter+rand()%200), (counter+rand()%100), 0);
      draw_lines(edges, s, c);
    }
  }
  

  print_matrix(edges);
  
  printf("\nDrawing!!"); 
  save_ppm(s,"image.ppm");
  display(s);
  
  free_matrix( edges );

}
