#ifndef UTIL_C
#define UTIL_C

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char*                                                                           
itoa(int value, char* result, int base) {                                       
  /* check that the base if valid */                                           
  if (base < 2 || base > 36) { *result = '\0'; return result; }                 
                                                                                
  char* ptr = result, * ptr1 = result, tmp_char;                                 
  int tmp_value;                                                                
                                                                                
  do {                                                                          
    tmp_value = value;                                                          
    value /= base;                                                              
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba"                                       
             "9876543210123456789"                                              
             "abcdefghijklmnopqrstuvwxyz"                                       
             [35 + (tmp_value - value * base)];                                 
  } while(value);                                                            
                                                                                
  /* Apply negative sign */                    
  if (tmp_value < 0) *ptr++ = '-';                                              
  *ptr-- = '\0';                                                                
  while(ptr1 < ptr) {                                                           
    tmp_char = *ptr;                                                            
    *ptr--= *ptr1;                                                              
    *ptr1++ = tmp_char;                                                         
  }                                                                             
  return result;                                                                
}  

char*
parse_var(char* str) {
  char* end = str;
  while(isalpha(*++end) || isdigit(*end));
  char* result = malloc(end - str + 1);
  memcpy(result, str, end - str);
  result[end - str] = '\0';
  return result;
}

char*
concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

#endif
