#include <FPT.h>
#include <D2d_matrix.h>
#include <math.h>

int  click_and_save(double a[], double b[]) {
  // Set up screen
  G_rgb(0.2,0.2,0.9) ;
  G_fill_rectangle(0,0,100,100) ;
  int count=0 ;
  double c[2] ;
  G_wait_click(c) ;

  // Dear user, click
  while((c[0]>100)||(c[1]>100)){
    G_rgb(0.9,0.2,0.2);
    G_circle(c[0],c[1],3);
    a[count]=c[0];b[count]=c[1];

    // Draw
    if(count>0){
      G_rgb(0,0,0);
      G_line(a[count-1],b[count-1],a[count],b[count]);
    }

    count=count+1;
    G_wait_click(c);
  }
  return count;
}


int D2d_negate_sincos(double a[3][3], double b[3][3], double sn, double cs){

	double t[3][3] ;
	
	D2d_make_identity(t) ;
	
	t[0][0] = cs-sn ; 
	t[1][1] = sn-cs ;

	D2d_mat_mult(a, t, a) ;

	t[0][0] = cs ; t[0][1] = sn ; 
	t[1][0] = -sn ; t[1][1] = cs ;

	D2d_mat_mult(b, b, t) ;

	return 1;
}


int main(int argc, char **argv){
  G_init_graphics (1000, 1000) ;
  double a[100], b[100], p[2], x1, x2, y1, y2, mat[3][3], invmat[3][3] ;
  int m ;
  
  // What shape would you want?
  m = click_and_save(a,b) ;
  G_fill_polygon(a,b,m) ;
  
  // What line shall it be reflected on?
  G_wait_click(p) ; x1 = p[0] ; y1 = p[1] ;
  G_rgb(1,0.1,0) ;
  G_fill_circle (x1, y1, 2) ;
  
  G_wait_click(p) ; x2 = p[0] ; y2 = p[1] ;
  G_fill_circle (x2, y2, 2) ;
  
  G_line(x1, y1, x2, y2) ;
  
  
  double dx = x2 - x1 ; double dy = y2 - y1 ;
  double hypothenuse = sqrt(dx*dx + dy*dy) ;
  
  double cs = dx/hypothenuse ;
  double sn = dy/hypothenuse ;
  
  
  
  D2d_make_identity(mat) ; D2d_make_identity(invmat) ;
  D2d_negate_sincos(mat, invmat, cs, sn) ;
  D2d_translate(mat, invmat, 300, 0 ) ;
  D2d_mat_mult_points(a, b, mat, a, b, m) ;
  
  /* NEED TO FIND A WAY OF FINDING THE LENGTH BETWEEN THE LINE DRAWN AND
     THE POINTS OF THE SHAPE.
     
     PARAMTRIC EQUATION IS NECESSARY!
     
     
     
     
  */

  
  G_fill_polygon(a,b,m) ;

  printf("here\n") ;
  

  
  G_wait_key() ;
  
}
