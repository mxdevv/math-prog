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

#define STACKF_INIT_SIZE 8

struct stackf {
  double* mem_l, * mem_r, * cur;
};

struct stackf*
stackf_alloc(void) {
  return malloc(sizeof(struct stackf));
}

void
stackf_init(struct stackf* stck) {
  stck->mem_l = malloc(STACKF_INIT_SIZE * sizeof(double));
  stck->cur = stck->mem_l;
  stck->mem_r = stck->mem_l + STACKF_INIT_SIZE;
}

void
stackf_free(struct stackf* stck) {
  free(stck->mem_l);
  free(stck);
}

int
stackf_avail(struct stackf* stck) {
  return stck->cur != stck->mem_r;
}

int
stackf_empty(struct stackf* stck) {
  return stck->cur == stck->mem_l;
}

void
stackf_push(struct stackf* stck, double val) {
  if (!stackf_avail(stck)) {
    size_t size = stck->mem_r - stck->mem_l;
    stck->mem_l = realloc(stck->mem_l, size*2 * sizeof(double));
    stck->cur = stck->mem_l + size;
    stck->mem_r = stck->mem_l + size*2;
  }
  *(++stck->cur) = val;
}

double
stackf_pop(struct stackf* stck) {
  return *stck->cur--;
}

#endif
