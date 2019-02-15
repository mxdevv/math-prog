#ifndef UTIL_C
#define UTIL_C

#include <stdlib.h>
#include <string.h>

char*
concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

enum object_type { OBJECT_DOUBLE, OBJECT_CHAR, OBJECT_STR };

struct object {
  enum object_type type;
  void* data;
};

#define STACK_INIT_SIZE 8

#define STACK(stack, T)                                          \
struct stack {                                                   \
  T* mem_l, * mem_r, * cur;                                      \
};                                                               \
                                                                 \
struct stack*                                                    \
stack##_alloc(void) {                                            \
  return malloc(sizeof(struct stack));                           \
}                                                                \
                                                                 \
void                                                             \
stack##_init(struct stack* stck) {                               \
  stck->mem_l = malloc(STACK_INIT_SIZE * sizeof(T));             \
  stck->cur = stck->mem_l;                                       \
  stck->mem_r = stck->mem_l + STACK_INIT_SIZE;                   \
}                                                                \
                                                                 \
struct stack*                                                    \
stack##_new(void) {                                              \
  struct stack* stck = stack##_alloc();                          \
  stack##_init(stck);                                            \
  return stck;                                                   \
}                                                                \
                                                                 \
void                                                             \
stack##_free(struct stack* stck) {                               \
  free(stck->mem_l);                                             \
  free(stck);                                                    \
}                                                                \
                                                                 \
int                                                              \
stack##_avail(struct stack* stck) {                              \
  return stck->cur != stck->mem_r;                               \
}                                                                \
                                                                 \
int                                                              \
stack##_empty(struct stack* stck) {                              \
  return stck->cur == stck->mem_l;                               \
}                                                                \
                                                                 \
void                                                             \
stack##_push(struct stack* stck, T val) {                        \
  if (!stack##_avail(stck)) {                                    \
    size_t size = stck->mem_r - stck->mem_l;                     \
    stck->mem_l = realloc(stck->mem_l, size*2 * sizeof(T));      \
    stck->cur = stck->mem_l + size;                              \
    stck->mem_r = stck->mem_l + size*2;                          \
  }                                                              \
  *(++stck->cur) = val;                                          \
}                                                                \
                                                                 \
T                                                                \
stack##_pop(struct stack* stck) {                                \
  return *stck->cur--;                                           \
}                                                                

#define LIST(list, T)                                            \
struct el_##list {                                               \
  T data;                                                        \
  struct el_##list* prev, * next;                                \
};                                                               \
                                                                 \
struct el_##list*                                                \
el_##list##_alloc() {                                            \
  return malloc(sizeof(struct el_##list));                       \
}                                                                \
                                                                 \
void                                                             \
el_##list##_init(struct el_##list* el_lst) {                     \
  el_lst->prev = el_lst->next = NULL;                            \
}                                                                \
                                                                 \
void                                                             \
el_##list##_free(struct el_##list* el_lst) {                     \
  free(el_lst);                                                  \
}                                                                \
                                                                 \
struct el_##list*                                                \
el_##list##_new(void) {                                          \
  struct el_##list* el_lst = el_##list##_alloc();                \
  el_##list##_init(el_lst);                                      \
  return el_lst;                                                 \
}                                                                \
                                                                 \
struct list {                                                    \
  struct el_##list* beg, * end;                                  \
  size_t size;                                                   \
};                                                               \
                                                                 \
struct list*                                                     \
list##_alloc(void) {                                             \
  return malloc(sizeof(struct list));                            \
}                                                                \
                                                                 \
void                                                             \
list##_init(struct list* lst) {                                  \
  lst->beg = lst->end = NULL;                                    \
  lst->size = 0;                                                 \
}                                                                \
                                                                 \
struct list*                                                     \
list##_new(void) {                                               \
  struct list* lst = list##_alloc();                             \
  list##_init(lst);                                              \
  return lst;                                                    \
}                                                                \
                                                                 \
int                                                              \
list##_empty(struct list* lst) {                                 \
  return lst->size == 0;                                         \
}                                                                \
                                                                 \
void                                                             \
list##_add_end(struct list* lst, T data) {                       \
  if (!lst->size) {                                              \
    lst->end = lst->beg = el_##list##_new();                     \
    lst->beg->data = data;                                       \
    lst->size = 1;                                               \
  } else {                                                       \
    lst->end->next = el_##list##_new();                          \
    lst->end->next->prev = lst->end;                             \
    lst->end = lst->end->next;                                   \
    lst->end->data = data;                                       \
    lst->size++;                                                 \
  }                                                              \
}                                                                \
                                                                 \
void                                                             \
list##_add_beg(struct list* lst, T data) {                       \
  if (!lst->size) {                                              \
    lst->end = lst->beg = el_##list##_new();                     \
    lst->beg->data = data;                                       \
    lst->size = 1;                                               \
  } else {                                                       \
    lst->beg->prev = el_##list##_new();                          \
    lst->beg->prev->next = lst->beg;                             \
    lst->beg = lst->end->prev;                                   \
    lst->beg->data = data;                                       \
    lst->size++;                                                 \
  }                                                              \
}                                                                \
                                                                 \
T                                                                \
list##_pop_end(struct list* lst) {                               \
  struct el_##list* el_lst = lst->end;                           \
  T data = el_lst->data;                                         \
  lst->end = lst->end->prev;                                     \
  el_##list##_free(el_lst);                                      \
  lst->size--;                                                   \
  return data;                                                   \
}                                                                \
                                                                 \
T                                                                \
list##_pop_beg(struct list* lst) {                               \
  struct el_##list* el_lst = lst->beg;                           \
  T data = el_lst->data;                                         \
  lst->beg = lst->beg->next;                                     \
  el_##list##_free(el_lst);                                      \
  lst->size--;                                                   \
  return data;                                                   \
}                                                                

STACK(stackf, double)
STACK(stackc, char)
STACK(stacki, int)
STACK(stacko, struct object)

LIST(listf, double)
LIST(listc, char)
LIST(listo, struct object)

#endif
