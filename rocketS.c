#include <FPT.h>
#include <D2d_matrix.h>
#include <math.h>


// rocket
double rx[8] = {0, 16,  7,  7,  0, -7, -7, -16 } ;
double ry[8] = {0,  0, 15, 35, 50, 35, 15,   0 } ;


int D2d_rotate_sincos(double a[3][3], double b[3][3], double sn, double cs){

	double t[3][3] ;
	
	D2d_make_identity(t) ;
	
	t[0][0] = cs ; t[0][1] = -sn ; 
	t[1][0] = sn ; t[1][1] = cs ;

	D2d_mat_mult(a, t, a) ;

	t[0][0] = cs ; t[0][1] = sn ; 
	t[1][0] = -sn ; t[1][1] = cs ;

	D2d_mat_mult(b, b, t) ;

	return 1;
}



int main()
{
  int q ;
  double c[2], x1, x2, y1, y2 ;

  G_init_graphics(700,700) ;
  G_rgb(0,0,0) ;
  G_clear() ;
  G_rgb(1,0,0) ;
  G_fill_polygon(rx,ry,8) ;

  G_wait_click(c) ; x1 = c[0] ; y1 = c[1] ;
  G_rgb(1, 1, 0) ; G_fill_circle(x1, y1, 2) ;
  
  
  G_wait_click(c) ; x2 = c[0] ; y2 = c[1] ;
  G_fill_circle(x2, y2, 2) ;


  double dx = x2 - x1 ; double dy = y2 - y1 ;
  double hypothenuse = sqrt(dx*dx + dy*dy) ;
  double scale = hypothenuse/50 ;

  double cs = dx/hypothenuse ;
  double sn = dy/hypothenuse ;
  

  double mat[3][3], invmat[3][3] ;
  
  D2d_make_identity(mat) ; D2d_make_identity(invmat) ;
  double rad = -M_PI/2 ;
  D2d_rotate(mat, invmat, rad) ;
  D2d_scale(mat, invmat, scale, scale) ;
  D2d_rotate_sincos(mat, invmat, sn, cs) ;
  D2d_translate(mat, invmat, x1, y1) ;
  D2d_mat_mult_points(rx, ry, mat, rx, ry, 8) ;

  //
  G_rgb(1,0,0) ;
  G_fill_polygon(rx,ry,8) ;
  
  
  
  q = G_wait_key() ;
}





















/*
  Start by finding the delta x and delta y of the two click(p) coordinates
  that towards finding the hypothenuse. the scale factor will be: length/50
  50 because that's the height of this thing...
  D2d_make_identity(m) ;
  D2d_make_identity(minv) ;
  D2d_scale(m, minv, scalefactor, scalefactor)
  

  ok. now rotation. it's smart to lay down the rocket first. 
  after that we apply the rotation...
  NOT BY USING ARCTAN because we can get the same angle in 2 quadrants...
  in C there's an extra function atan2(dy,dx) ;
  that'll give us the correct angle.
  THE BETTER WAY OUT OF THIS
  well, we can compute cos and sin of the right triangle clicks(p)
  in this way we DON'T NEED THE ANGLE, really. we can plug those in
  directly into the matrix that defines the rotation...we can build the
  function into our code!
 */
