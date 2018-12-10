#include "method.h"

struct xy { double x; double y; };

struct matrix {
	int n, m;
	double* data;
};

int
cmp_double(const void* a, const void* b)
{
	return (*(double*)a < *(double*)b);
}

double*
el_matr(struct matrix* matr, int n, int m)
{
	return &matr->data[n + m * matr->n];
}

struct matrix*
alloc_matr(int n, int m)
{
	struct matrix* matr = (struct matrix*)malloc(sizeof(struct matrix));
	matr->n = n;
	matr->m = m;
	matr->data = (double*)malloc(n * m * sizeof(double));
	return matr;
}

void
init_matr_zero(struct matrix* matr)
{
	for(int i = 0, j = sizeof(matr->data) / sizeof(matr->data[0]);
			i < j; i++) {
		matr->data[i] = 0.0;
	}
}

void
free_matr(struct matrix* matr)
{
	free(matr->data);
	free(matr);
}

struct matrix*
matr_copy(struct matrix* matr1)
{
	struct matrix* matr2 = alloc_matr(matr1->n, matr1->m);
	for(int i = matr1->n * matr1->m; i --> 0;)
		matr2[i] = matr1[i];
	return matr2;
}

struct matrix*
matr_mult(struct matrix* matr1, struct matrix* matr2)
{
	struct matrix* matr3 = alloc_matr(matr2->n, matr1->m);
	init_matr_zero(matr3);
	for(int m3i = 0; m3i < matr3->m; m3i++)
	for(int n3i = 0; n3i < matr3->n; n3i++)
	for(int i = 0; i < matr1->n; i++) {
	#ifdef EDEBUG
		printf("\e[31m::EDBG el{matr1}=%.1f, el{matr2}=%.1f, el{matr3}=%.1f\e[0m\n",
			*el_matr(matr1, i, m3i), *el_matr(matr2, n3i, i), *el_matr(matr3, n3i, m3i));
	#endif
		*el_matr(matr3, n3i, m3i) += *el_matr(matr1, i, m3i) * *el_matr(matr2, n3i, i);
	}	
#ifdef DEBUG
	printf("\e[32m::DBG natr_mult\n");
	for(int mi = 0; mi < matr3->m; mi++) {
	for(int ni = 0; ni < matr3->n; ni++) {
			printf("%.1f ", *el_matr(matr3, ni, mi));
		}
		printf("\n");
	}
	printf("\e[0m");
#endif
}

double
df(double (*f)(double x), double x, double eps)
{
	return (f(x+eps) - f(x-eps)) / (2.0 * eps);
}

double
dfdx(double (*f)(double x, double y), double x, double y, double eps)
{
	return (f(x+eps,y) - f(x-eps,y)) / (2.0 * eps);
}

double
dfdy(double (*f)(double x, double y), double x, double y, double eps)
{
	return (f(x,y+eps) - f(x,y-eps)) / (2.0 * eps);
}

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
			"i=%d, x=%f, y=%f, xn=%f, yn=%f\e[0m\n",
			    i,    x,    y,    xn,    yn);
		++i;
	#endif
	
	} while(fabs(xn - cx) > eps && fabs(yn - cy) > eps);

	struct xy xy1 = { x, y };
	return xy1;
}

struct xy
wulff_method(double (*f)(double x, double y),
             double(*g1)(double x, double y), double(*g2)(double x, double y),
             double b1, double b2, struct matrix* xyzw, double eps)
{
	double dx, dy, dz, dw, I1, I2, B1, B2, D1, D2;

	double* x = el_matr(xyzw, 0, 0);
	double* y = el_matr(xyzw, 0, 1);
	double* z = el_matr(xyzw, 0, 2);
	double* w = el_matr(xyzw, 0, 3);
	
	for(int i = 0; i < 1; i++) {
		dx = dfdx(f, *x, *y, eps);
		dy = dfdy(f, *x, *y, eps);
		dz = 0.0;
		dw = 0.0;
		{
			double sorted[4];
			for(int i = 4; i --> 0;)
				sorted[i] = *el_matr(xyzw, 0, i);
			qsort(&sorted, 4, sizeof(double), cmp_double);
			I1 = sorted[0];
			I2 = sorted[1];
		}

	#ifdef DEBUG
		printf("\e[32m::DBG "
			"wulff_method: dx=%f, dy=%f, dz=%f, dw=%f\n",
		                    dx,    dy,    dz,    dw);
		printf("      I={%f,%f}\n", I1, I2); 
		printf("\e[0m");
	#endif
	}
}

