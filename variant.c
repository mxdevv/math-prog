/* lw6, variant 8 */
double
f_lw6_8(double x)
{
  return pow(M_E,x) + 1.0/x;
}

/* lw7, variant 8 */
double
f_lw7_8(double x, double y)
{
  return POW_2(x) + 3*POW_2(y) + cos(x+y);
}

double
dfdx_lw7_8(double x, double y)
{
  return 2*x - sin(x+y);
}

double
dfdy_lw7_8(double x, double y)
{
  return 6*y - sin(x+y);
}

/* lw9, variant 8 */
double
f_lw9_8(double x, double y)
{
	return 3*POW_2(x) - 3*POW_2(y);
}

double
g1_lw9_8(double x, double y)
{
	return POW_3(x) + POW_4(y) - 3*POW_2(x)*POW_2(y);
}

double
g2_lw9_8(double x, double y)
{
	return POW_2(x) + 5*POW_2(y) - 4*y;
}

const double b1_lw9_8 = 14;
const double b2_lw9_8 = 10;

double
dfdx_lw9_8(double x, double y)
{
	return 6*x;
}

double
dfdy_lw9_8(double x, double y)
{
	return -6*y;
}

double
dg1dx_lw9_8(double x, double y)
{
	return 3*POW_2(x) - 6*x*POW_2(y);
}

double
dg1dy_lw9_8(double x, double y)
{
	return 4*POW_3(y) - 6*POW_2(x)*y;
}

double
dg2dx_lw9_8(double x, double y)
{
	return 2*x;
}

double
dg2dy_lw9_8(double x, double y)
{
	return 10*y - 4;
}
