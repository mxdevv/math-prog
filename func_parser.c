#ifndef FUNC_PARSER_C
#define FUNC_PARSER_C

#include <ctype.h>

struct listo*
expr_to_listo(char* expr) {
  struct listo* lst = listo_new();

  enum state { is_empty, is_num, is_str, is_sym }
    state = is_empty, nstate = is_empty;
  struct object* obj;
  double doub;
  char ch;
  char* str;

  for(; *expr; expr++) {
    state = nstate;

    if (isdigit(*expr) || *expr == '.') nstate = is_num;
    else if (isalpha(*expr)) nstate = is_str;
    else if (!isspace(*expr)) nstate = is_sym;
    else nstate = is_empty;
    
    if (state != nstate) {
      if (nstate == is_num) {
        obj = object_new(OBJECT_DOUBLE, malloc(sizeof(double)));
        doub = atof(expr);
        memcpy(obj->data, (void*)&doub, sizeof(double));
        listo_add_end(lst, obj);
      }
      else if (nstate == is_str) {
        obj = object_new(OBJECT_STR, (void*)parse_alpha(expr));
        listo_add_end(lst, obj);
      }
    }

    if (nstate == is_sym) {
      obj = object_new(OBJECT_CHAR, malloc(sizeof(char)));
      ch = *expr;
      memcpy(obj->data, (void*)&ch, sizeof(char));
      listo_add_end(lst, obj);
    }
  }

  return lst;
}

struct listo*
sort_station(struct listo* lst) {
  ;
}

#endif
