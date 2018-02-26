#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {

  //If matrix is too small 
  if (points->lastcol == points->cols) {
    grow_matrix(points, points->cols+1);
  }

  //Setting new points:
  points->m[0][points->lastcol]=x;
  points->m[1][points->lastcol]=y;
  points->m[2][points->lastcol]=z;
  points->m[3][points->lastcol]=1; 

  //Increase lastcol
  points->lastcol++;  
  
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {

  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
  
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {

  int col;
  int x0;
  int y0;
  int x1;
  int y1;
  
  for (col = 0; col < points->lastcol; col+=2){
    x0 = points->m[0][col];
    y0 = points->m[1][col];
    x1 = points->m[0][col+1];
    y1 = points->m[1][col+1];
    
    draw_line(x0, y0, x1, y1,  s, c);
  }
   
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

 //Swap variable values if necessary: 
  if (x0 > x1) {
    int temp = x1;
    x1 = x0;
    x0 = temp;

    temp = y1;
    y1 = y0;
    y0 = temp;
  }

  int x = x0;
  int y = y0;
  
  int a = y1 - y0;
  int b = -1 * (x1 - x0);
  int d; 

  double slope = ( ((double)a) / (x1 - x0) );

  //OCTANT 1 
  if (slope >= 0 && slope <= 1) {
    d = (2 * a) + b;

    while (x <= x1) {
      plot(s, c, x, y);

      if (d > 0) {
	y++;
	d += (2 * b);
      }

      x++;
      d += (2 * a);
    }
  }

  //OCTANT 2
  else if (slope > 1) {
    d = (2 * b) + a;

    while (y <= y1) {
      plot(s, c, x, y);

      if (d < 0) {
	x++;
	d += (2 * a);
      }

      y++;
      d += (2 * b);
    }
  }

  //OCTANT 7
  else if (slope < -1) {
    d = a - (2 * b);

    while (y >= y1) {
      plot(s, c, x, y);

      if (d > 0) {
	x++;
	d += (2 * a);
      }

      y--;
      d -= (2 * b);
    }
  }

  //OCTANT 8
  else if (slope >= -1) {
    d = (2 * a) - b;

    while (x <= x1) {
      plot(s, c, x, y);

      if (d < 0) {
	y--;
	d -= (2 * b);
      }

      x++;
      d += (2 * a);
    }
  }

} //end draw_line
