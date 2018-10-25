#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FPT.h>
#include <math.h>
#include <ctype.h>
#include <D2d_matrix.h>

int npoints, nshapes, shapes[10000][10000] ;
double x[10000], y[10000], shapecolor[10000][3], rotrad[1000] ;
double xcenter, ycenter, sx, sy ;
char what[1000] ;


int read_poly(int n){
  FILE *f = fopen (what, "r") ;
  if(f==NULL) {printf("can't open file %s \n", what) ; exit(0) ; }
  
  fscanf(f, "%d", &npoints) ; // Scan # of points

  for(int i = 0 ; i < npoints ; i++) {fscanf(f, "%lf %lf", &x[i], &y[i]) ; } // Scan all the x,y points
  
  fscanf(f, "%d", &nshapes) ; // Scan # of shapes
  // And scan all the shapes' "pointers"
  for(int i = 0; i < nshapes; i++) { fscanf(f, "%d", &shapes[i][0]) ;
    for(int j = 1 ; j < shapes[i][0]+1; j++){fscanf(f, "%d", &shapes[i][j]) ; } }
  
  for(int i=0; i<nshapes; i++) {
    for(int j=0; j<3; j++) {
      fscanf(f, "%lf", &shapecolor[i][j]) ; // Scan the colors for each shape
    }
    rotrad[i] = 0 ;
  }

  
  return 1;
}


int draw(){
  int k ; // temp miniShape index
  double r,g,b ;
  for(int i=0; i<nshapes; i++) {
    // Load into temp variables this "i" particular shape for modification
    k = shapes[i][0] ;
    double tempX [k] ;
    double tempY [k] ;
    for(int j=1; j<shapes[i][0]+1; j++) {
      k = shapes[i][j] ;
      tempX[j-1] = x[k] ;
      tempY[j-1] = y[k] ;
    }
    r = shapecolor[i][0] ;
    g = shapecolor[i][1] ;
    b = shapecolor[i][2] ;
    G_rgb(r,g,b) ;
    G_fill_polygon(tempX, tempY, shapes[i][0]) ;
  }
  
}

int scale_prep(int nowshown){
  double mat[3][3], matinv[3][3] ;
  double maxx = x[0], minx = x[0], maxy = y[0], miny = y[0], scale ;
  for(int i=0; i<npoints; i++) { // Find max and min to later scale
    if(x[i]>maxx){maxx = x[i] ; }
    if (x[i]<minx){minx = x[i] ; }
    if(y[i]>maxy){maxy = y[i] ; }
    if (y[i]<miny){miny = y[i] ; }
  }
  xcenter = (maxx + minx)/2, ycenter = (maxy + miny)/2 ;

  
  if((maxx-minx) < (maxy-miny)){scale = maxy - miny ; }
  else {scale = maxx - minx ; }
  //sx = 1000/(maxx - minx), sy = 1000/(maxy - minx) ;
  scale = 1000/scale ;

  
  D2d_make_identity(mat) ; D2d_make_identity(matinv) ;
  D2d_translate(mat, matinv, -xcenter, -ycenter) ;
  D2d_scale(mat, matinv, scale, scale) ;
  D2d_translate(mat, matinv, 500, 500) ;
  D2d_print_mat(mat) ;
  // D2d_rotate(mat, matinv, rotrad[nowshown]) ;
  D2d_print_mat(mat) ;
  D2d_mat_mult_points(x, y, mat, x, y, npoints) ;

  return 1 ;
}

int rotate(int nowshown){
  double mat[3][3], matinv[3][3] ;
  
  D2d_make_identity(mat) ; D2d_make_identity(matinv) ;
  D2d_translate(mat, matinv, -500,-500) ;
  D2d_rotate(mat, matinv, 0.1) ;
  D2d_translate(mat, matinv,  500, 500) ;  
  D2d_mat_mult_points(x, y, mat, x, y, npoints) ;
  
}




int main(int argc, char **argv){
  
  if(argc==1){printf("too few arguments in console. are you passing a file at all? \n") ; }
  
  G_init_graphics (1000,1000) ;
 
  char q = '1' ;
  int nowshown = 1 ;
  double mat[3][3], matinv[3][3] ;

  G_rgb(0,0,0) ;
  G_clear() ;
  strcpy(what, argv[nowshown]) ;  
  read_poly(nowshown) ;
  scale_prep(nowshown) ;    
  draw() ;  
  q = G_wait_key() ;
  
  while(q != 'q'){
    //Get a new canvas, do your readings
    G_rgb(0,0,0) ;
    G_clear() ;
    
    rotate(nowshown) ;
    draw() ;
    
    if(isdigit(q)!=0){
      if((q>=argc-1)&&(q!=48)){nowshown = q-48 ;
	strcpy(what, argv[nowshown]) ;
	read_poly(nowshown) ;
	scale_prep(nowshown) ;
	G_rgb(0,0,0) ;
	G_clear() ;
	draw() ;
	printf("here! and nowshown is %d \n", nowshown) ;}}

    //    strcpy(what, argv[nowshown]) ;


    
    q = G_wait_key() ;

    /*
    printf("q is %c \n", q ) ;
    // If you press 0, rotrad will change by .1 radians. Revert to 0 if rotrad gets to 2PI.
    if(q == 0){
      if(rotrad[nowshown] >= 2*M_PI){rotrad[nowshown] = 0 ; }
    }
    // Otherwise i'll check if you want me to show another picture.
    else if(isdigit(q)!=0){
      if(q>=argc-1){nowshown = q-48 ; printf("here! and nowshown is %d \n", nowshown) ;}}
    */
    
  }

  
  
  /*
    
    // Make initial translation matrix (to avoid distortion when scaling)
    // Want a matrix w/ translation to center defined by image
    double mat[3][3], invmat[3][3] ; D2d_make_identity(mat) ; D2d_make_identity(invmat) ;
    D2d_print_mat(mat) ;
    D2d_translate (mat, invmat, -xcenter, -ycenter) ;
    if (sx<sy){double s = sx ; } else {double s = sy ; }
    D2d_scale (mat, invmat, sx, sy) ;
    D2d_print_mat(mat) ;
    D2d_translate(mat, invmat, xcenter, ycenter) ;
    D2d_mat_mult_points(tempX, tempY, mat, tempX, tempY, k) ;
    
   
  

  */
}


/*
  To troubleshoot:
  To make sure values are actually getting what they should  
  printf("%d, %lf, %lf, %d, %d, %lf \n", npoints, x[0], y[37], nshapes, shapes[5][2], shapecolor[2][2]) ;


 */
