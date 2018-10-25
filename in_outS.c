#include <FPT.h>

int swidth, sheight ;

int click_and_save (double *x, double *y)
{
  int n ;
  double P[2] ;

  G_rgb(0,1,0.5) ;
  G_fill_rectangle(0,0,swidth,20) ;

  G_rgb(1,0,0) ;
  G_wait_click(P);

  n = 0 ;
  while (P[1] > 20) {
    x[n] = P[0] ;
    y[n] = P[1] ;
    G_circle(x[n],y[n],2) ;
    if (n > 0) { G_line(x[n-1],y[n-1], x[n],y[n]) ;}
    n++ ;
    G_wait_click(P) ;
  }

  return n ;
}

void average(double *average, double *x, double *y, int n){
  average[0] = 0 ; average[1] = 0 ;
  for(int i=0; i<n; i++) {
    average[0] += x[i];
    average[1] += y[i];
  }
  average[0] /=n ;
  average[1] /=n ;
  printf("%lf, %lf \n", average[0], average[1]) ;
}



int in_out (double *x, double *y, int n, double P[2])
// return 1 if point P is inside the convex polygon
// else return 0
{
  double av[2] ;
  average(av, xp, yp, n) ;
  //cx and cy are the centers. p[0] and p[1] are the clicks
  int j ;
  double v1, v2 ;
  for(int i = 0 ; i<n+1 ; i++){
    j = (i+1)%n ;
    
    v1 = A
  }
  v1 = A*cx + B*cy + C ;
  v2 = A*p[0] + B*p[1] + C ;
  //if v1 and v2 > 0 {good} else {bad}
}


/*

flag =1 ; //initial belief of inside
for(i =0 ; i< n ;i++){
  j = (i+1)&n ;
}

*/



int main()
{
  double xp[1000],yp[1000] ;
  int n,q ;
  double P[2] ;


  swidth = 700 ; sheight = 700 ;
  G_init_graphics(swidth, sheight) ;
  G_rgb(0,0,0) ;
  G_clear() ;

  G_rgb(1,0,0) ;
  n = click_and_save(xp,yp) ;
  G_rgb(0,1,0) ;
  G_fill_polygon(xp,yp,n) ;


  G_rgb(0.5, 0.5, 0.7) ;
  G_fill_circle(av[0], av[1], 2) ;

  G_wait_click(P) ;



  G_rgb(0,0,1) ;
  G_fill_circle(P[0],P[1],2) ;




  q = G_wait_key() ;
}
