#ifndef VARIANT_C
#define VARIANT_C

#include "method.c"

#define NOTHING 0

#define COUNT_LW      9
#define COUNT_VARIANT 8

char str_f_lw7_1[] = "f(x)=7*x1^2+2*x1*x2+5*x2^2+x1-10*x2";

double
f_lw7_1(double x, double y)
{
  return 7*POW_2(x) + 2*x*y + 5*POW_2(y) + x - 10*y;
}

char str_f_lw7_2[] = "f(x)=3*x1^2-3*x1*x2+4*x2^2-2*x1+x2";

double
f_lw7_2(double x, double y)
{
  return 3*POW_2(x) - 3*x*y + 4*POW_2(y) - 2*x + y;
}

char str_f_lw7_3[] = "f(x)=x1^2+2*x2^2+e^(x1^2+x2^2)-x1-x2";

double
f_lw7_3(double x, double y)
{
  return POW_2(x) + 2*POW_2(y) + pow(M_E, POW_2(x)+POW_2(y)) - x + y;
}

char str_f_lw7_4[] = "f(x)=√(x1^2+x2^2+1)+1/2*x1-1/2*x2";

double
f_lw7_4(double x, double y)
{
  sqrt(POW_2(x) + POW_2(y) + 1) + 1.0/2.0*x - 1.0/2.0*y;
}

char str_f_lw7_5[] = "f(x)=x1^2+4*x1*x2+13*x1^2+5*x2";

double
f_lw7_5(double x, double y)
{
  return POW_2(x) + 4*x*y + 13*POW_2(x) + 5*y;
}

char str_f_lw7_6[] = "f(x)=5*x1^2-4*x1*x2+5*x2^2-x1-x2";

double
f_lw7_6(double x, double y)
{
  return 5*POW_2(x) - 4*x*y + 5*POW_2(y) - x - y;
}

char str_f_lw7_7[] = "f(x)=x1^4+2*x2^4+x1^2*x2^2+2*x1+x2";

double
f_lw7_7(double x, double y)
{
  return POW_4(x) + 2*POW_4(y) + POW_2(x)*POW_2(y) + 2*x - y;
}

char str_f_lw7_8[] = "f(x)=x1^2+3*x2^2+cos(x1+x2)";

double
f_lw7_8(double x, double y)
{
  return POW_2(x) + 3*POW_2(y) + cos(x+y);
}

char str_f_lw9_1[] = "f(x)=-x1^2-x2^2\n"
                     "(x1-5)^2+(x2-5)^2 <= 8\n"
                     "x1,x2 >= 0";

double
f_lw9_1(double x, double y)
{
  return -POW_2(x) - POW_2(y);
}

double
g1_lw9_1(double x, double y)
{
  return POW_2(x - 5) + POW_2(y - 5);
}

double
g2_lw9_1(double x, double y)
{
  return NOTHING;
}

const double b1_lw9_1 = 8;
const double b2_lw9_1 = NOTHING;

char str_f_lw9_2[] = "f(x)=-x1^2+x2^2\n"
                     "(x1-4)^2-(x2-4)^2 <= 6\n"
                     "x1,x2 >= 0";

double
f_lw9_2(double x, double y)
{
  return -POW_2(x) + POW_2(y);
}

double
g1_lw9_2(double x, double y)
{
  return POW_2(x - 4) - POW_2(y - 4);
}

double
g2_lw9_2(double x, double y)
{
  return NOTHING;
}

const double b1_lw9_2 = 6;
const double b2_lw9_2 = NOTHING;

char str_f_lw9_3[] = "f(x)=-x1^2+x2^2\n"
                     "(x1-8)^2-(x2-8)^2 <= 16\n"
                     "x1,x2 >= 0";

double
f_lw9_3(double x, double y)
{
  return -POW_2(x) + POW_2(y);
}

double
g1_lw9_3(double x, double y)
{
  return POW_2(x - 8) - POW_2(y - 8);
}

double
g2_lw9_3(double x, double y)
{
  return NOTHING;
}

const double b1_lw9_3 = 16;
const double b2_lw9_3 = NOTHING;

char str_f_lw9_4[] = "f(x)=-x1^4-x2^4\n"
                     "(x1-4)^4-(x2-4)^4 <= 6\n"
                     "x1,x2 >= 0";

double
f_lw9_4(double x, double y)
{
  return -POW_4(x) - POW_4(y);
}

double
g1_lw9_4(double x, double y)
{
  return POW_4(x - 4) - POW_4(y - 4);
}

double
g2_lw9_4(double x, double y)
{
  return NOTHING;
}

const double b1_lw9_4 = 6;
const double b2_lw9_4 = NOTHING;

char str_f_lw9_5[] = "f(x)=-x1^2-x2^2+2*x1*x2\n"
                     "(x1-7)^2-(x2-7)^2 <= 8\n"
                     "x1,x2 >= 0";

double
f_lw9_5(double x, double y)
{
  return -POW_2(x) - POW_2(y) + 2*x*y;
}

double
g1_lw9_5(double x, double y)
{
  return POW_2(x - 7) - POW_2(y - 7);
}

double
g2_lw9_5(double x, double y)
{
  return NOTHING;
}

const double b1_lw9_5 = 8;
const double b2_lw9_5 = NOTHING;

char str_f_lw9_6[] = "f(x)=-x1^2-x2^2+2*x1*x2-x2\n"
                     "x1^2-3*x2^2+5*x1*x2 <= 2\n"
                     "x1,x2 >= 0";

double
f_lw9_6(double x, double y)
{
  return -POW_2(x) - POW_2(y) + 2*x*y - y;
}

double
g1_lw9_6(double x, double y)
{
  return POW_2(x) - 3*POW_2(y) + 5*x*y;
}

double
g2_lw9_6(double x, double y)
{
  return NOTHING;
}

const double b1_lw9_6 = 2;
const double b2_lw9_6 = NOTHING;

char str_f_lw9_7[] = "f(x)=7*x1^2+3*x2^2-3*x1-9*x2+6\n"
                     "x1^3+x2^2 <= 11\n"
                     "4*x1^2+x2^2-x2 <= 7\n"
                     "x1,x2 >= 0";

double
f_lw9_7(double x, double y)
{
  return 7*POW_2(x) + 3*POW_2(y) - 3*x - 9*y + 6;
}

double
g1_lw9_7(double x, double y)
{
  return POW_3(x) + POW_2(y);
}

double
g2_lw9_7(double x, double y)
{
  return 4*POW_2(x) + POW_2(y) - y;
}

const double b1_lw9_7 = 11;
const double b2_lw9_7 = 7;

char str_f_lw9_8[] = "f(x)=3*x1^2-3*x2^2\n"
                     "x1^3+x2^4-3*x1^2*x2^2 <= 14\n"
                     "x1^2+5*x2^2-4*x2 <= 10\n"
                     "x1,x2 >= 0";

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

double (*fs_lw7[])(double x, double y) = { f_lw7_1,
                                           f_lw7_2,
                                           f_lw7_3,
                                           f_lw7_4,
                                           f_lw7_5,
                                           f_lw7_6,
                                           f_lw7_7,
                                           f_lw7_8,
                                           NULL
                                         };

double (*fs_lw9[])(double x, double y) = { f_lw9_1,
                                           f_lw9_2,
                                           f_lw9_3,
                                           f_lw9_4,
                                           f_lw9_5,
                                           f_lw9_6,
                                           f_lw9_7,
                                           f_lw9_8,
                                           NULL
                                        };
double (*g1s_lw9[])(double x, double y) = { g1_lw9_1,
                                            g1_lw9_2,
                                            g1_lw9_3,
                                            g1_lw9_4,
                                            g1_lw9_5,
                                            g1_lw9_6,
                                            g1_lw9_7,
                                            g1_lw9_8,
                                            NULL
                                          };
double (*g2s_lw9[])(double x, double y) = { g2_lw9_1,
                                            g2_lw9_2,
                                            g2_lw9_3,
                                            g2_lw9_4,
                                            g2_lw9_5,
                                            g2_lw9_6,
                                            g2_lw9_7,
                                            g2_lw9_8,
                                            NULL
                                          };
double const* b1s_lw9[] = { &b1_lw9_1,
                            &b1_lw9_2,
                            &b1_lw9_3,
                            &b1_lw9_4,
                            &b1_lw9_5,
                            &b1_lw9_6,
                            &b1_lw9_7,
                            &b1_lw9_8,
                            NULL
                          };
double const* b2s_lw9[] = { &b2_lw9_1,
                            &b2_lw9_2,
                            &b2_lw9_3,
                            &b2_lw9_4,
                            &b2_lw9_5,
                            &b2_lw9_6,
                            &b2_lw9_7,
                            &b2_lw9_8,
                            NULL
                          };

char* strs_f_lw1[] = { NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL
                     };
char* strs_f_lw2[] = { NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL
                     };
char* strs_f_lw3[] = { NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL
                     };
char* strs_f_lw4[] = { NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL
                     };
char* strs_f_lw5[] = { NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL
                     };
char* strs_f_lw6[] = { NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL
                     };
char* strs_f_lw7[] = { str_f_lw7_1,
                       str_f_lw7_2,
                       str_f_lw7_3,
                       str_f_lw7_4,
                       str_f_lw7_5,
                       str_f_lw7_6,
                       str_f_lw7_7,
                       str_f_lw7_8,
                       NULL
                     };
char* strs_f_lw8[] = { NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL
                     };
char* strs_f_lw9[] = { str_f_lw9_1,
                       str_f_lw9_2,
                       str_f_lw9_3,
                       str_f_lw9_4,
                       str_f_lw9_5,
                       str_f_lw9_6,
                       str_f_lw9_7,
                       str_f_lw9_8,
                       NULL
                    };

char** strss_f_lw[] = { strs_f_lw1,
                        strs_f_lw2,
                        strs_f_lw3,
                        strs_f_lw4,
                        strs_f_lw5,
                        strs_f_lw6,
                        strs_f_lw7,
                        strs_f_lw8,
                        strs_f_lw9
                      };

char* strs_m_lw1[] = {};
char* strs_m_lw2[] = {};
char* strs_m_lw3[] = {};
char* strs_m_lw4[] = {};
char* strs_m_lw5[] = {};
char* strs_m_lw6[] = {};
char* strs_m_lw7[] = { "Метод циклического покоординатного спуска",
                       "Метод наискорейшего спуска"
                     };
char* strs_m_lw8[] = {};
char* strs_m_lw9[] = {"Метод штрафных функций"};

int strss_m_lw_len[] = { 0,
                         0,
                         0,
                         0,
                         0,
                         0,
                         2,
                         0,
                         1 
                      };

char** strss_m_lw[] = { strs_m_lw1,
                        strs_m_lw2,
                        strs_m_lw3,
                        strs_m_lw4,
                        strs_m_lw5,
                        strs_m_lw6,
                        strs_m_lw7,
                        strs_m_lw8,
                        strs_m_lw9
                      };

#endif
