#ifndef CONT_C
#define CONT_C

#define STACK_INIT_SIZE 8

struct stack {                                                   
  void** mem_l, ** mem_r, ** cur;                                      
};                                                               
                                                                 
struct stack*                                                    
stack_alloc(void) {                                            
  return malloc(sizeof(struct stack));                           
}                                                                
                                                                 
void                                                             
stack_init(struct stack* stck) {                               
  stck->mem_l = malloc(STACK_INIT_SIZE * sizeof(void*));             
  stck->cur = stck->mem_l;                                       
  stck->mem_r = stck->mem_l + STACK_INIT_SIZE;                   
}                                                                
                                                                 
struct stack*                                                    
stack_new(void) {                                              
  struct stack* stck = stack_alloc();                          
  stack_init(stck);                                            
  return stck;                                                   
}                                                                
                                                                 
void                                                             
stack_free(struct stack* stck) {                               
  free(stck->mem_l);                                             
  free(stck);                                                    
}                                                                
                                                                 
int                                                              
stack_avail(struct stack* stck) {                              
  return stck->cur != stck->mem_r;                               
}                                                                
                                                                 
int                                                              
stack_empty(struct stack* stck) {                              
  return stck->cur == stck->mem_l;                               
}                                                                
                                                                 
void                                                             
stack_push(struct stack* stck, void* val) {                        
  if (!stack_avail(stck)) {                                    
    size_t size = stck->mem_r - stck->mem_l;                     
    stck->mem_l = realloc(stck->mem_l, size*2 * sizeof(void*));      
    stck->cur = stck->mem_l + size;                              
    stck->mem_r = stck->mem_l + size*2;                          
  }                                                              
  *(++stck->cur) = val;                                          
}                                                                
                                                                 
void*                                                                
stack_pop(struct stack* stck) {                                
  return *stck->cur--;                                           
}                                                                

struct el_list {                                               
  void* data;                                                        
  struct el_list* prev, * next;                                
};                                                               
                                                                 
struct el_list*                                                
el_list_alloc() {                                            
  return malloc(sizeof(struct el_list));                       
}                                                                
                                                                 
void                                                             
el_list_init(struct el_list* el_lst) {                     
  el_lst->prev = el_lst->next = NULL;                            
}                                                                
                                                                 
void                                                             
el_list_free(struct el_list* el_lst) {                     
  free(el_lst);                                                  
}                                                                
                                                                 
void
el_list_free_with_data(struct el_list* el_lst, void (*data_free)()) {
  data_free(el_lst->data);
  free(el_lst);
}

struct el_list*                                                
el_list_new(void) {                                          
  struct el_list* el_lst = el_list_alloc();                
  el_list_init(el_lst);                                      
  return el_lst;                                                 
}                                                                
                                                                 
struct list {                                                    
  struct el_list* beg, * end;                                  
  size_t size;                                                   
};                                                               
                                                                 
struct list*                                                     
list_alloc(void) {                                             
  return malloc(sizeof(struct list));                            
}                                                                
                                                                 
void                                                             
list_init(struct list* lst) {                                  
  lst->beg = lst->end = NULL;                                    
  lst->size = 0;                                                 
}                                                                
                                                                 
struct list*                                                     
list_new(void) {                                               
  struct list* lst = list_alloc();                             
  list_init(lst);                                              
  return lst;                                                    
}                                                                
                                                                 
void                                                             
list_free(struct list* lst) {                                  
  struct el_list* el = lst->beg, * el_n;
  while(el) {
    el_n = el->next;
    el_list_free(el);
    el = el_n;
  }
  free(lst);                                                     
}                                                                
                                                                 
void
list_free_with_data(struct list* lst, void (*data_free)()) {
  struct el_list* el = lst->beg, * el_n;
  while(el) {
    el_n = el->next;
    el_list_free_with_data(el, data_free);
    el = el_n;
  }
  free(lst);                                                     
}

int                                                              
list_empty(struct list* lst) {                                 
  return lst->size == 0;                                         
}                                                                
                                                                 
void                                                             
list_add_end(struct list* lst, void* data) {                       
  if (!lst->size) {                                              
    lst->end = lst->beg = el_list_new();                     
    lst->beg->data = data;                                       
    lst->size = 1;                                               
  } else {                                                       
    lst->end->next = el_list_new();                          
    lst->end->next->prev = lst->end;                             
    lst->end = lst->end->next;                                   
    lst->end->data = data;                                       
    lst->size++;                                                 
  }                                                              
}                                                                
                                                                 
void                                                             
list_add_beg(struct list* lst, void* data) {                       
  if (!lst->size) {                                              
    lst->end = lst->beg = el_list_new();                     
    lst->beg->data = data;                                      
    lst->size = 1;                                               
  } else {                                                       
    lst->beg->prev = el_list_new();                          
    lst->beg->prev->next = lst->beg;                             
    lst->beg = lst->beg->prev;                                  
    lst->beg->data = data;                                       
    lst->size++;                                                 
  }                                                              
}                                                                
                                                                 
void*                                                                
list_pop_end(struct list* lst) {                               
  struct el_list* el_lst = lst->end;                           
  void* data = el_lst->data;                                         
  lst->end = lst->end->prev;                                     
  el_list_free(el_lst);                                      
  lst->size--;                                                   
  return data;                                                   
}                                                                
                                                                 
void*                                                                
list_pop_beg(struct list* lst) {                               
  struct el_list* el_lst = lst->beg;                           
  void* data = el_lst->data;                                         
  lst->beg = lst->beg->next;                                     
  el_list_free(el_lst);                                      
  lst->size--;                                                   
  return data;                                                   
}                                                                


#endif
