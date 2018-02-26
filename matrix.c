#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int row = 0;
  int col = 0;

  printf("\n****Matrix:****\n"); 
 
  for (; row < m->rows; row++) {
    // printf("num rows: %d\n", row);
    for (; col < m->lastcol; col++) {
      //printf("num cols: %d\n", col); 
      printf("%06.2lf ", m->m[row][col]);
    }
    col = 0;
    printf("\n"); 
  }
}


/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int row = 0; 
  int col = 0;

  //printf("num rows: %d\n", m->rows);
  //printf("num cols: %d\n", m->cols); 

  for (; row < m->rows; row++) {
    //printf("Running for loop\n");
    //printf("row: %d\n", row);
    for (; col < m->cols; col++) {
      //printf("col: %d\n", col); 

      if (row == col) {
	//printf("Matched!\n");
	m->m[row][col] = 1;
	//printf("value: %.2f\n", m->m[row][col]); 
      }

      else {
	m->m[row][col] = 0;
      }
      
    }
    col = 0;
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {

  //Check
  if (a->cols != b->rows) {
    printf("Error, cannot multiple matrices because they don't fit the dimension requirements\n");
    return;
  }

  else {
    //Storage or temporary matrix
    struct matrix * return_matrix = new_matrix(a->rows, b->cols);

    int rows_a = 0;
    int cols_b = 0;
    int rows_b = 0; 

    int sum = 0;
    
    for (; rows_a < a->rows; rows_a++) {
      //printf("row: %d\n", row);
      for (; cols_b < b->lastcol; cols_b++) {
	//printf("col: %d\n", col); 
	for (; rows_b < b->rows; rows_b++) {
	   //printf("rows_b: %d\n", counter); 
	  sum  += a->m[rows_a][rows_b] * b->m[rows_b][cols_b];
	  //printf("Value: %d\n", return_matrix->m[row][col]);
	}
	return_matrix->m[rows_a][cols_b] = sum; 
	rows_b = 0;
	sum = 0;
      }
      cols_b = 0;
    }

    copy_matrix(return_matrix, b);
    free_matrix(return_matrix);     
  }
}


/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}
