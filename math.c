struct xy { double x; double y; };

struct matrix {
  int n, m;
  double* data;
};

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
    *el_matr(matr3, n3i, m3i) +=
        *el_matr(matr1, i, m3i) * *el_matr(matr2, n3i, i);
  }
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
