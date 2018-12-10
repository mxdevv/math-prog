#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#define DEBUG
//#define EDEBUG

#include "method.c"
#include "variant.c"

int
main()
{
	struct xy xy1;
	printf("/* LW 7 */\n");
	xy1 = find_xy_min_cycle_descent(f_lw7_8, -10.0, -10.0, LOW, HIGH, EPS);
	printf("find_xy_min_cycle_descent: x = %f, y = %f\n", xy1.x, xy1.y);
	xy1 = find_xy_min_quickest_descent(f_lw7_8,
	                                   -10.0, -10.0, LOW, HIGH, EPS, LAMBDA);
	printf("/* LW 9 */\n");
	printf("find_xy_min_quickest_descent: x = %f, y = %f\n", xy1.x, xy1.y);
	xy1 = penalty_functions_method_max(f_lw9_8, g1_lw9_8, g2_lw9_8,
	                                   b1_lw9_8, b2_lw9_8,
	                                   1.0, 1.0, EPS, LAMBDA);
	printf("penalty_functions_method_max: x = %f, y = %f\n", xy1.x, xy1.y);

	/*printf("Matrix test\n");
	struct matrix* matr1;
	matr1 = alloc_matr(3, 2);
	matr1->data = (double[]){ 1.0, 2.0, 3.0,
	                          4.0, 5.0, 6.0 };
	struct matrix* matr2;
	matr2 = alloc_matr(2, 3);
	matr2->data = (double[]){ 1.0, 2.0,
	                          3.0, 4.0,
	                          5.0, 6.0 };
	struct matrix* matr3 = matr_mult(matr1, matr2);*/

	printf("/* LW 8 */\n");
	struct matrix* xyzw = alloc_matr(1, 4);
	xyzw->data = (double[]){ 0,
	                         0,
	                         15,
	                         1 };
	xy1 = wulff_method(f_lw8_8, g1_lw8_8, g2_lw8_8, b1_lw8_8, b2_lw8_8,
	                   xyzw, EPS);
	printf("wulff_method: x = %f, y = %f\n", xy1.x, xy1.y);
}
