#ifndef FUNC_PARSER_C
#define FUNC_PARSER_C

#include <ctype.h>
#include <math.h>

#include "cont.c"
#include "util.c"

enum token_type {
  TOKEN_NUMBER, TOKEN_VAR, TOKEN_CONST, TOKEN_OP, TOKEN_OP_BRACKET,
  TOKEN_CL_BRACKET, TOKEN_SIN, TOKEN_COS, TOKEN_SQRT
};                    
                                                                                
struct token {                                                                 
  enum token_type type;                                                        
  void* val;                                                                   
};                                                                              
                                                                                
struct token*                                                                  
token_new(enum token_type type, void* val) {                                 
  struct token* tok = malloc(sizeof(struct token)); 
  tok->type = type;                                                             
  tok->val = val;                                                             
  return tok;                                                                   
}  

void
token_free(struct token* tok) {
  free(tok->val);
  free(tok);
}

void
list_tokens_out(struct list* lst) {
  struct token* tok;
  for(int i = lst->size; i > 0; i--) {
    tok = list_pop_beg(lst);
    switch(tok->type) {
      case TOKEN_NUMBER:     printf("num: %f; ", *(double*)tok->val); break;
      case TOKEN_VAR:        printf("var: %s; ", (char*)tok->val); break;
      case TOKEN_CONST:      printf("const: %s; ", (char*)tok->val); break;
      case TOKEN_OP:         printf("op: %c; ", *(char*)tok->val); break;
      case TOKEN_OP_BRACKET: printf("open bracket; "); break;
      case TOKEN_CL_BRACKET: printf("close bracket; "); break;
      case TOKEN_SIN:        printf("sin; "); break;
      case TOKEN_COS:        printf("cos; "); break;
      case TOKEN_SQRT:       printf("sqrt; "); break;
    }
    list_add_end(lst, tok);
  }
  printf("\n");
}

int
op_precedence(char ch) {
  switch(ch) {
    case '^': return 9;
    case '*':
    case '/': return 8;
    case '+':
    case '-': return 6;
    case '(': return -1;
  }
}

struct list*
expr_to_tokens(char* expr) {
  struct list* lst = list_new();

  enum state { is_empty, is_num, is_str, is_sym }
    state = is_empty, nstate = is_empty;
  struct token* tok;
  double doub;
  char ch;
  char* str;

  for(; *expr; expr++) {
    state = nstate;

    if (isdigit(*expr) || *expr == '.') {
      if (state == is_str) nstate = is_str;
      else nstate = is_num;
    }
    else if (isalpha(*expr)) nstate = is_str;
    else if (!isspace(*expr)) nstate = is_sym;
    else nstate = is_empty;
    
    if (state != nstate) {
      if (nstate == is_num) {
        tok = token_new(TOKEN_NUMBER, malloc(sizeof(double)));
        doub = atof(expr);
        memcpy(tok->val, (void*)&doub, sizeof(double));
        list_add_end(lst, (void*)tok);
      }
      else if (nstate == is_str) {
        str = parse_var(expr);
        /* в будущем strcmp заменить на поиск по "словарю" */
        if (!strcmp(str, "cos")) tok = token_new(TOKEN_COS, (void*)str);
        else if (!strcmp(str, "sin")) tok = token_new(TOKEN_SIN, (void*)str);
        else if (!strcmp(str, "sqrt")) tok = token_new(TOKEN_SQRT, (void*)str);
        else if (!strcmp(str, "e")) tok = token_new(TOKEN_CONST, (void*)str);
        else tok = token_new(TOKEN_VAR, (void*)str);
        list_add_end(lst, (void*)tok);
      }
    }

    if (nstate == is_sym) {
      ch = *expr;
      switch(ch) {
        case '(': tok = token_new(TOKEN_OP_BRACKET, malloc(sizeof(char))); 
          break;
        case ')': tok = token_new(TOKEN_CL_BRACKET, malloc(sizeof(char)));
          break;
        default:  tok = token_new(TOKEN_OP, malloc(sizeof(char)));
          break;
      }
      memcpy(tok->val, (void*)&ch, sizeof(char));
      list_add_end(lst, (void*)tok);
    }
  }

  return lst;
}

struct list*
sort_station(struct list* lst) {
  struct list* stck = list_new();
  struct list* out = list_new();

  struct token* tok, * tok2;
  while(!list_empty(lst)) {
    switch((tok = list_pop_beg(lst))->type) {
      case TOKEN_NUMBER:
      case TOKEN_VAR:
      case TOKEN_CONST:
        list_add_end(out, tok);
        break;
      case TOKEN_OP:
        while(!list_empty(stck)) {
          tok2 = list_pop_end(stck);
          if (op_precedence(*(char*)tok->val)
              <= op_precedence(*(char*)tok2->val)) {
            list_add_end(out, tok2);
          } else {
            list_add_end(stck, tok2);
            break;
          }
        }
        list_add_end(stck, tok);
        break;
      case TOKEN_OP_BRACKET:
        list_add_end(stck, tok);
        break;
      case TOKEN_CL_BRACKET:
        while((tok2 = list_pop_end(stck))->type != TOKEN_OP_BRACKET) {
          list_add_end(out, tok2);
        }
        break;
      case TOKEN_SIN:
      case TOKEN_COS:
      case TOKEN_SQRT:
        list_add_end(stck, tok);
        break;
    }
  }
  while(!list_empty(stck)) {
    tok = list_pop_end(stck);
    list_add_end(out, tok);
  }
  return out;
}

struct param {
  char* name;
  double val;
};

struct param*
param_new(char* name, double val) {
  struct param* prm = malloc(sizeof(struct param));
  prm->name = name;
  prm->val = val;
  return prm;
}

void
param_free(struct param* prm) {
  free(prm->name);
  free(prm);
}

/* не лучшая идея делать prms типа list */
double
calc_rpn(struct list* rpn, struct list* prms) {
  struct list* stck = list_new();
  struct token* tok, * tok2, * tok3;
  struct param* prm;
  double resl;
  while(!list_empty(rpn)) {
    switch((tok = list_pop_beg(rpn))->type) {
      case TOKEN_NUMBER:
        list_add_end(stck, tok);
        break;
      case TOKEN_VAR:
        for(int i = prms->size; i > 0; i--) {
          prm = list_pop_beg(prms);
          if (!strcmp(prm->name, tok->val)) {
            tok->type = TOKEN_NUMBER;
            free(tok->val);
            tok->val = malloc(sizeof(double));
            memcpy(tok->val, (void*)&prm->val, sizeof(double));
          }
          list_add_end(prms, prm);
        }
        list_add_beg(rpn, tok);
        break;
      case TOKEN_CONST:
        if (!strcmp("e", (char*)tok->val)) {
          tok->type = TOKEN_NUMBER;
          free(tok->val);
          tok->val = malloc(sizeof(double));
          resl = M_E;
          memcpy(tok->val, (void*)&resl, sizeof(double));
        }
        list_add_beg(rpn, tok);
        break;
      case TOKEN_OP:
        switch(*(char*)tok->val) {
          /* дублирование(макрос?) */
          case '^':
            tok3 = list_pop_end(stck);
            tok2 = list_pop_end(stck);
            resl = pow(*(double*)tok2->val, *(double*)tok3->val);
            free(tok3);
            memcpy(tok2->val, (void*)&resl, sizeof(double));
            list_add_end(stck, tok2);
            break;
          case '*':
            tok3 = list_pop_end(stck);
            tok2 = list_pop_end(stck);
            resl = *(double*)tok2->val * *(double*)tok3->val;
            free(tok3);
            memcpy(tok2->val, (void*)&resl, sizeof(double));
            list_add_end(stck, tok2);
            break;
          case '/':
            tok3 = list_pop_end(stck);
            tok2 = list_pop_end(stck);
            resl = *(double*)tok2->val / *(double*)tok3->val;
            free(tok3);
            memcpy(tok2->val, (void*)&resl, sizeof(double));
            list_add_end(stck, tok2);
            break;
          case '+':
            tok3 = list_pop_end(stck);
            tok2 = list_pop_end(stck);
            resl = *(double*)tok2->val + *(double*)tok3->val;
            free(tok3);
            memcpy(tok2->val, (void*)&resl, sizeof(double));
            list_add_end(stck, tok2);
            break;
          case '-':
            tok3 = list_pop_end(stck);
            tok2 = list_pop_end(stck);
            resl = *(double*)tok2->val - *(double*)tok3->val;
            free(tok3);
            memcpy(tok2->val, (void*)&resl, sizeof(double));
            list_add_end(stck, tok2);
            break;
        }
        break;
      case TOKEN_OP_BRACKET:
        break;
      case TOKEN_CL_BRACKET:
        break;
      case TOKEN_SIN:
        tok2 = list_pop_end(stck);
        resl = sin(*(double*)tok2->val);
        memcpy(tok2->val, (void*)&resl, sizeof(double));
        list_add_end(stck, tok2);
        break;
      case TOKEN_COS:
        tok2 = list_pop_end(stck);
        resl = sin(*(double*)tok2->val);
        memcpy(tok2->val, (void*)&resl, sizeof(double));
        list_add_end(stck, tok2);
        break;
      case TOKEN_SQRT:
        tok2 = list_pop_end(stck);
        resl = sqrt(*(double*)tok2->val);
        memcpy(tok2->val, (void*)&resl, sizeof(double));
        list_add_end(stck, tok2);
        break;
    }
  }
  return *(double*)(((struct token*)list_pop_end(stck))->val);
}

/* пока не используется */
/* работает, но создаёт лишнии копии, нужен словарь */
struct list*
get_params(struct list* rpn) {
  struct list* prms = list_new();
  struct token* tok;
  struct param* prm;
  double resl;
  while(!list_empty(rpn)) {
    switch((tok = list_pop_beg(rpn))->type) {
      case TOKEN_VAR:
        prm = malloc(sizeof(struct param));
        prm->name = tok->val;
        prm->val = -1.0;
        list_add_end(prms, prm);
        break;
    }
  }
  return prms;
}

typedef double (*_double_fn_2arg)(double x1, double x2);
static void* _expr;

double
adapter_make_x1x2_func_from_expr(double x1, double x2) {
  struct list* toks = expr_to_tokens(_expr);
  struct list* rpn = sort_station(toks);
  struct list* prms = list_new();
  double resl;
  list_add_end(prms, param_new("x1", x1));
  list_add_end(prms, param_new("x2", x2));
  resl = calc_rpn(rpn, prms);
  list_free(toks);
  list_free_with_data(rpn, token_free);
  /* list_free_with_data(prms, param_free) => segmentation failure */
  list_free(prms);
  return resl;
}

_double_fn_2arg
make_func_x1x2_from_expr(char* expr) {
  _expr = expr;
  return adapter_make_x1x2_func_from_expr;
}

#endif
