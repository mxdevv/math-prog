#define POW_2(x) x*x
#define POW_3(x) x*x*x
#define POW_4(x) POW_2(x) * POW_2(x)

#define EPS 0.001
#define LAMBDA 0.1
#define GOLD 1.6180339887498948482
#define LOW -10.0
#define HIGH 10.0

struct xy;

/* LW 7 */
struct xy
find_xy_min_cycle_descent(double (*f)(double x, double y),
                          double x, double y, double low, double high,
                          double eps);
struct xy
find_xy_min_quickest_descent(double (*f)(double x, double y),
                             double (*dfdx)(double x, double y),
                             double (*dfdy)(double x, double y),
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
double
find_fxy_grad_x_linear(double (*f)(double x, double y), double y,
                       double low, double high, double eps);
double
find_fxy_grad_y_linear(double (*f)(double x, double y), double x,
                       double low, double high, double eps);
struct xy
penalty_functions_method_max(double (*f)(double x, double y),
                             double (*g1)(double x, double y),
                             double (*g2)(double x, double y),
                             double b1, double b2,
                             double (*dfdx)(double x, double y),
                             double (*dfdy)(double x, double y),
                             double (*dg1dx)(double x, double y),
                             double (*dg1dy)(double x, double y),
                             double (*dg2dx)(double x, double y),
                             double (*dg2dy)(double x, double y),
                             double x, double y, double eps, double lambda);
