#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

//#define DEBUG
//#define EDEBUG

#include "method.c"
#include "variant.c"

int
main()
{
	struct xy xy1;
	/* LW 7 */
	xy1 = find_xy_min_cycle_descent(f_lw7_8, -10.0, -10.0, LOW, HIGH, EPS);
	printf("find_xy_min_cycle_descent: x = %f, y = %f\n", xy1.x, xy1.y);
	xy1 = find_xy_min_quickest_descent(f_lw7_8,
	                                   -10.0, -10.0, LOW, HIGH, EPS, LAMBDA);
	/* LW 9 */
	printf("find_xy_min_quickest_descent: x = %f, y = %f\n", xy1.x, xy1.y);
	xy1 = penalty_functions_method_max(f_lw9_8, g1_lw9_8, g2_lw9_8,
	                                   b1_lw9_8, b2_lw9_8,
	                                   1.0, 1.0, EPS, LAMBDA);
	printf("penalty_functions_method_max: x = %f, y = %f\n", xy1.x, xy1.y);
}
