#include <FPT.h>

// Implement a coarse fill of a coarse clicked polygon :


int swidth, sheight ;
int del = 20 ;

int coarse_click_and_save (double *x, double *y)
{
  int n ;
  int P[2] ;
  int ix,iy ;
  int hdel ;

  hdel = del/2 ;

  G_rgb(0,1,0.5) ;
  G_fill_rectangle(0,0,swidth,20) ;

  G_rgb(0.5,0.5,0.5) ;
  for (ix = 0 ; ix < swidth ; ix += del) {
    G_line(ix,0, ix,sheight) ;
  }
  for (iy = 0 ; iy < swidth ; iy += del) {
    G_line(0,iy, swidth,iy) ;
  }


  G_rgb(1,0,0) ;
  Gi_wait_click(P);  
  P[0] = del*((P[0]+hdel)/del) ; 
  P[1] = del*((P[1]+hdel)/del) ;


  n = 0 ;
  while (P[1] > 20) {
    x[n] = P[0] ;
    y[n] = P[1] ;
    G_fill_circle(x[n],y[n],3) ;
    if (n > 0) { G_line(x[n-1],y[n-1], x[n],y[n]) ;}
    n++ ;
  
    Gi_wait_click(P);
    P[0] = del*((P[0]+hdel)/del) ; 
    P[1] = del*((P[1]+hdel)/del) ;
  }

  G_line(x[0],y[0], x[n-1],y[n-1]) ;
  return n ;
}






void selection_sort (double *x, int n) 
{
  int i,s,j ;
  double tmp ;

  for (i = 0 ; i < n ; i++) {
    s = i ;
    for (j = i+1 ; j < n ; j++) {
      if (x[j] < x[s]) { s = j ; }
    }
    tmp = x[i] ; x[i] = x[s] ; x[s] = tmp ;
  }

}





void coarse_fill_polygon (double *x, double *y, int n)
{
  // you get to write this !!!!!
}





int  main()
{
  int q ;
  double xp[1000],yp[1000] ;
  int np ;

  swidth = 600 ;   sheight = 600 ;
  G_init_graphics (swidth, sheight) ;

  do {
     G_rgb(0,0,0) ;
     G_clear() ;

     np = coarse_click_and_save(xp,yp) ;

     G_rgb(1,1,0) ;
     coarse_fill_polygon(xp,yp,np) ;

     q = G_wait_key() ; 
 } while (q != 'q') ;

}



