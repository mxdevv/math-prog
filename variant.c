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
