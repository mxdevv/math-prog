#ifndef FUNC_PARSER_C
#define FUNC_PARSER_C

#include <ctype.h>

enum token_type {
  TOKEN_NUMBER, TOKEN_VAR, TOKEN_OP, TOKEN_OP_BRACKET, TOKEN_CL_BRACKET,
  TOKEN_SIN, TOKEN_COS
};                    
                                                                                
struct token {                                                                 
  enum token_type type;                                                        
  void* val;                                                                   
};                                                                              
                                                                                
struct token*                                                                  
token_new(enum token_type type, void* val) {                                 
  struct token* tkn = malloc(sizeof(struct token)); 
  tkn->type = type;                                                             
  tkn->val = val;                                                             
  return tkn;                                                                   
}  

void
list_tokens_out(struct list* lst) {
  struct token* tkn;
  for(int i = lst->size; i > 0; i--) {
    tkn = list_pop_beg(lst);
    switch(tkn->type) {
      case TOKEN_NUMBER:     printf("num: %f; ", *(double*)tkn->val); break;
      case TOKEN_VAR:        printf("var: %s; ", (char*)tkn->val); break;
      case TOKEN_OP:         printf("op: %c; ", *(char*)tkn->val); break;
      case TOKEN_OP_BRACKET: printf("open bracket; "); break;
      case TOKEN_CL_BRACKET: printf("close bracket; "); break;
      case TOKEN_SIN:        printf("sin; "); break;
      case TOKEN_COS:        printf("cos; "); break;
    }
    list_add_end(lst, tkn);
  }
  printf("\n");
}

int
op_precedence(char ch) {
  switch(ch) {
    case '^': return 9;
    case '*':
    case '/': 
    case '%': return 8;
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
  struct token* tkn;
  double doub;
  char ch;
  char* str;

  for(; *expr; expr++) {
    state = nstate;

    if (isdigit(*expr) || *expr == '.') {
      if (state == is_str)
        nstate = is_str;
      else
        nstate = is_num;
    }
    else if (isalpha(*expr)) nstate = is_str;
    else if (!isspace(*expr)) nstate = is_sym;
    else nstate = is_empty;
    
    if (state != nstate) {
      if (nstate == is_num) {
        tkn = token_new(TOKEN_NUMBER, malloc(sizeof(double)));
        doub = atof(expr);
        memcpy(tkn->val, (void*)&doub, sizeof(double));
        list_add_end(lst, (void*)tkn);
      }
      else if (nstate == is_str) {
        str = parse_var(expr);
        /* в будущем strcmp заменить на поиск по "словарю" */
        if (!strcmp(str, "cos")) tkn = token_new(TOKEN_COS, (void*)str);
        else if (!strcmp(str, "sin")) tkn = token_new(TOKEN_SIN, (void*)str);
        else tkn = token_new(TOKEN_VAR, (void*)str);
        list_add_end(lst, (void*)tkn);
      }
    }

    if (nstate == is_sym) {
      ch = *expr;
      switch(ch) {
        case '(': tkn = token_new(TOKEN_OP_BRACKET, malloc(sizeof(char))); 
          break;
        case ')': tkn = token_new(TOKEN_CL_BRACKET, malloc(sizeof(char)));
          break;
        default:  tkn = token_new(TOKEN_OP, malloc(sizeof(char)));
          break;
      }
      memcpy(tkn->val, (void*)&ch, sizeof(char));
      list_add_end(lst, (void*)tkn);
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
        list_add_end(out, tok);
        break;
      case TOKEN_OP:
        while(!list_empty(stck)) {
          tok2 = list_pop_end(stck);
          if (op_precedence(*(char*)tok->val)
              <= op_precedence(*(char*)(tok2->val))) {
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

#endif
