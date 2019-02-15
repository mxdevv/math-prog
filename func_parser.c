#ifndef FUNC_PARSER_C
#define FUNC_PARSER_C

#include <ctype.h>

struct stacko*
expr_to_stacko(char* expr) {
  struct stacko* stck = stacko_new();

  enum state { is_empty, is_num, is_str, is_sym }
    state = is_empty, nstate = is_empty;
  char buf[32], * pbuf = buf;

  for(; expr; expr++) {
    state = nstate;
    (isdigit(*expr)) ? (nstate = is_num)
    : (isalpha(*expr)) ? (nstate = is_str)
    : (!isspace(*expr)) ? (nstate = is_sym)
    : (nstate = is_empty);
  
    *pbuf++ = *expr;

    if (state != nstate) {
      ;
    }
  }

  return stck;
}

struct stacko*
sort_station(struct stacko* stck) {
  ;
}

#endif
