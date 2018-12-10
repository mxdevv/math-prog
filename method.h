#define POW_2(x) x*x
#define POW_3(x) x*x*x
#define POW_4(x) POW_2(x) * POW_2(x)
#define MAX(x,y) x > y ? x : y
#define MAX4(x,y,z,w) MAX(MAX(x,y),MAX(z,w))

#define EPS 0.001
#define LAMBDA 0.1
#define GOLD 1.6180339887498948482
#define LOW -10.0
#define HIGH 10.0

struct xy;
struct matrix;

double*
el_matr(struct matrix* matr, int n, int m);
struct matrix*
alloc_matr(int n, int m);
void
init_matr_zero(struct matrix* matr);
void
free_matr(struct matrix* matr);
struct matrix*
matr_copy(struct matrix* matr);
struct matrix*
matr_mult(struct matrix* matr1, struct matrix* matr2);
double
df(double (*f)(double x), double x, double eps);
double
dfdx(double (*f)(double x, double y), double x, double y, double eps);
double
dfdy(double (*f)(double x, double y), double x, double y, double eps);

struct xy
find_xy_min_cycle_descent(double (*f)(double x, double y),
                          double x, double y, double low, double high,
                          double eps);
struct xy
find_xy_min_quickest_descent(double (*f)(double x, double y),
                             double x, double y, double low, double high,
                             double eps, double lambda);
double
find_fx_min_x_gold(double (*f)(double x),
                   double low, double high, double eps);
double
find_fxy_min_y_gold(double (*f)(double x, double y), double x,
                    double low, double high, double eps);
double
find_fxy_min_x_gold(double (*f)(double x, double y), double y,
                    double low, double high, double eps);
struct xy
penalty_functions_method_max(double (*f)(double x, double y),
                             double (*g1)(double x, double y),
                             double (*g2)(double x, double y),
                             double b1, double b2,
                             double x, double y, double eps, double lambda);
struct xy
wulff_method(double (*f)(double x, double y),
             double(*g1)(double x, double y), double(*g2)(double x, double y),
             double b1, double b2, struct matrix* xyzw, double eps);
