#ifndef METHOD_C
#define METHOD_C

#include <math.h>
#include <stdlib.h>

#include "math.c"
#include "method.h"

struct xy
find_xy_min_cycle_descent(double (*fn)(double x, double y),
                          double x, double y, double low, double high,
                          double eps)
{
	double yn, xn;
	int stat;
	
	while(stat != 2) {
		stat = 0;
		
		yn = find_fxy_min_y_gold(fn, x, low, high, eps);
		if (fabs(yn - y) <= eps)
			++stat;
		y = yn;

		xn = find_fxy_min_x_gold(fn, y, low, high, eps);
		if (fabs(yn -y ) <= eps)
			++stat;
		x = xn;
	}
	struct xy xy1 = { x, y };
	return xy1;
}

struct xy
find_xy_min_quickest_descent(double (*f)(double x, double y),
                             double x, double y, double low, double high,
                             double eps, double lambda)
{
	double dx, dy, xp, yp;
	int stat = 0;

	while(stat != 2) {
		dx = dfdx(f, x, y, eps);
		dy = dfdy(f, x, y, eps);
		xp = x; yp = y;
		x = x - lambda * dx;
		y = y - lambda * dy;
		if (fabs(x - xp) <= eps) ++stat;
		if (fabs(y - yp) <= eps) ++stat;
	}
	struct xy xy1 = { x, y };
	return xy1;
}

double
find_fx_min_x_gold(double (*fn)(double x),
                   double low, double high, double eps)
{
	double a = low, b = high,
		c = b - (b - a) / GOLD,
		d = a + (b - a) / GOLD;

	while(fabs(b - a) > eps) {
		if (fn(c) < fn(d)) {
			b = d;
			d = c;
			// a = a 
			c = a + (b - d);
		} else {
			a = c;
			c = d;
			// b = b
			d = b - (c - a);
		}
	}
	return (d + c) / 2.0;
}

double
find_fxy_min_x_gold(double (*fn)(double x, double y), double y,
                    double low, double high, double eps)
{
	double a = low, b = high,
		c = b - (b - a) / GOLD,
		d = a + (b - a) / GOLD;

	while(fabs(b - a) > eps) {
		if (fn(c, y) < fn(d, y)) {
			b = d;
			d = c;
			// a = a
			c = a + (b - d);
		} else {
			a = c;
			c = d;
			// b = b
			d = b - (c - a);
		}
	}
	return (d + c) / 2.0;
}

double
find_fxy_min_y_gold(double (*fn)(double x, double y), double x,
                    double low, double high, double eps)
{
	double a = low, b = high,
		c = b - (b - a) / GOLD,
		d = a + (b - a) / GOLD;

	while(fabs(b - a) > eps) {
		if (fn(x, c) < fn(x, d)) {
			b = d;
			d = c;
			// a = a
			c = a + (b - d);
		} else {
			a = c;
			c = d;
			// b = b
			d = b - (c - a);
		}
	}
	return (d + c) / 2.0;
}

struct xy
penalty_functions_method_max(double (*f)(double x, double y),
                             double (*g1)(double x, double y),
                             double (*g2)(double x, double y),
                             double b1, double b2,
                             double x, double y, double eps, double lambda)
{
	double xn, yn, cx, cy, a;

#ifdef DEBUG
	int i = 0;
#endif

	xn = x; yn = y;
	do {
		a = eps;
		xn = x + lambda * dfdx(f, x, y, eps);
		yn = y + lambda * dfdy(f, x, y, eps);
		if (xn < 0) xn = 0;
		if (yn < 0) yn = 0;
		cx = x; cy = y;
		x = xn; y = yn;
		while(g1(x, y) > b1 || g2(x, y) > b2) {
			if (a > 0) {
				a += eps;
			} else {
				a -= eps;
			}
			a = -a;
			x = xn; y = yn;
			if (g1(x, y) > b1) {
				x += a * lambda * dfdx(g1, x, y, eps);
				y += a * lambda * dfdy(g1, x, y, eps);
			}
			if (g2(x, y) > b2) {
				x += a * lambda * dfdx(g2, x, y, eps);
				y += a * lambda * dfdy(g2, x, y, eps);
			}
		#ifdef EDEBUG
			printf("\e[31m::EDBG penalty_functions_method_max: a=%f\e[0m\n", a);
		#endif
		}
		xn = x; yn = y;

	#ifdef DEBUG
		printf("\e[32m::DBG penalty_functions_method_max: "
			"i=%d, a=%f, x=%f, y=%f, xn=%f, yn=%f\e[0m\n",
			    i,    a,    x,    y,    xn,    yn);
		++i;
	#endif
	
	} while(fabs(xn - cx) > eps && fabs(yn - cy) > eps);

	struct xy xy1 = { x, y };
	return xy1;
}

#endif
