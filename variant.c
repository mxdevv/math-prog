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

/* LW8, variant 8 */
double
f_lw8_8(double x, double y)
{
	return -4*x + 8*y - POW_2(x) - 3.0/2.0*POW_2(y) + 2*x*y;
}

double
g1_lw8_8(double x, double y)
{
	return 3*x + 5*y;
}

double
g2_lw8_8(double x, double y)
{
	return x - y;
}

const double b1_lw8_8 = 15;
const double b2_lw8_8 = 1;

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
