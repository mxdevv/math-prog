#ifndef VARIANT_C
#define VARIANT_C

#include "method.c"

#define COUNT_LW      9
#define COUNT_VARIANT 9

/*double
f_lw6_8(double x)
{
  return pow(M_E,x) + 1.0/x;
}*/

char str_f_lw7_8[] = "f(x)=x1^2+3*x2^2+cos(x1+x2)";

double
f_lw7_8(double x, double y)
{
  return POW_2(x) + 3*POW_2(y) + cos(x+y);
}

char str_f_lw9_8[] = "f(x)=3*x1^2-3*x2^2\n"
                     "x1^3+x2^4-3*x1^2*x2^2 <= 14\n"
						  			 "x1^2+5*x2^2-4*x2 <= 10";

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

double (*fs_lw7[])(double x, double y) = { NULL,
	                                         NULL,
																					 NULL,
																					 NULL,
																					 NULL,
																					 NULL,
																					 NULL,
																					 f_lw7_8,
																					 NULL
																			   };

double (*fs_lw9[])(double x, double y) = { NULL,
                                           NULL,
																					 NULL,
																					 NULL,
																					 NULL,
																					 NULL,
																					 NULL,
																					 f_lw9_8,
																					 NULL
																				};
double (*g1s_lw9[])(double x, double y) = { NULL,
                                            NULL,
																					  NULL,
																					  NULL,
																					  NULL,
																					  NULL,
																					  NULL,
																					  g1_lw9_8,
																					  NULL
																					};
double (*g2s_lw9[])(double x, double y) = { NULL,
                                            NULL,
																					  NULL,
																					  NULL,
																					  NULL,
																					  NULL,
																					  NULL,
																					  g2_lw9_8,
																					  NULL
																					};
double const* b1s_lw9[] = { NULL,
                            NULL,
										        NULL,
										        NULL,
										        NULL,
										        NULL,
										        NULL,
										        &b1_lw9_8,
										        NULL
									        };
double const* b2s_lw9[] = { NULL,
                            NULL,
										        NULL,
										        NULL,
										        NULL,
										        NULL,
										        NULL,
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
char* strs_f_lw7[] = { NULL,
											 NULL,
											 NULL,
											 NULL,
											 NULL,
											 NULL,
											 NULL,
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
char* strs_f_lw9[] = { NULL,
											 NULL,
											 NULL,
											 NULL,
											 NULL,
											 NULL,
											 NULL,
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

int strss_m_lw_len[] = { 0, /* хей костыль */
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
