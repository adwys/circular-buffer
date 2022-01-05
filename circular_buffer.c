#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include <ctype.h>



int circular_buffer_create(struct circular_buffer_t *a, int N){
  if(a==NULL || N<1)return 1;
  a->ptr = (int*)malloc(N * sizeof(int));
  if(a->ptr == NULL){circular_buffer_destroy(a);return 2;}
  a->capacity = N;
  a->begin=0;
  a->end=0;
  a->full=0;
  return 0;
}
int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){
  if(cb == NULL || N<1)return 1;
  *cb = (struct circular_buffer_t*)malloc(sizeof(struct circular_buffer_t));
  if(*cb == NULL){free(*cb);return 2;}
  (*cb)->ptr = (int*)malloc(N*sizeof(int));
  if((*cb)->ptr == NULL){free(*cb);return 2;}
  (*cb)->capacity = N;
  (*cb)->begin=0;
  (*cb)->end=0;
  (*cb)->full=0;
  return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a){
  if(a!=NULL)free(a->ptr);
}
void circular_buffer_destroy_struct(struct circular_buffer_t **a){
  if(a!=NULL){free((*a));free((*a)->ptr);}
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
  if(cb==NULL || (cb->end) >= cb->capacity || (cb->begin) >= cb->capacity || cb->capacity<1 || cb->begin<0 || cb->end<0)return 1;
    if(cb->full)
    {
      *(cb->ptr + cb->begin) = value;
      cb->begin = (cb->begin+1) % cb->capacity;
      cb->end = (cb->end+1) % cb->capacity;
    }
    else{
    *(cb->ptr + cb->end) = value;
    cb->end = (cb->end+1) % cb->capacity;
    }
    if((cb->end) == cb->begin)cb->full=1;
    else{cb->full=0;}

  return 0;
}
int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code){
  if(a==NULL || a->end<0 || a->begin<0 || a->capacity<1 || (a->end) >= a->capacity || (a->begin) >= a->capacity ){if(err_code!=NULL)*err_code = 1; return 2137;}
  if(a->begin == a->end && a->full==0){if(err_code!=NULL)*err_code = 2; return 2137;}
  int x = *(a->ptr+a->begin);
  a->begin = (a->begin+1) % a->capacity;
  a->full=0;
  if(err_code!=NULL)*err_code = 0;
  return x;
}
int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code){
  if(a==NULL || a->end<0 || a->begin<0 || a->capacity<1 || (a->end) >= a->capacity || (a->begin) >= a->capacity ){if(err_code!=NULL)*err_code = 1; return 2137;}
  int x;
  if(a->begin == a->end && a->full==0){if(err_code!=NULL)*err_code = 2; return 2137;}
  if(a->end==0) x = *(a->ptr+a->capacity-1);
  else{x = *(a->ptr+a->end-1);}
  if(a->end ==0)a->end = a->capacity-1;
  else{a->end = (a->end-1) % a->capacity;}
  a->full=0;
  if(err_code!=NULL)*err_code = 0;
  return x;
}

int circular_buffer_empty(const struct circular_buffer_t *a){
  if(a == NULL || a->capacity<1 || a->end<0 || a->begin<0 ||a->ptr == NULL || (a->end) >= a->capacity || (a->begin) >= a->capacity)return -1;
  if(a->full ==0 && a->begin == a->end)return 1;
  return 0;
}
int circular_buffer_full(const struct circular_buffer_t *a){
  if(a == NULL || a->capacity<1 || a->end<0 || a->begin<0 ||a->ptr == NULL || (a->end) >= a->capacity || (a->begin) >= a->capacity)return -1;
  if(a->full==1)return 1;
  return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a){
  
  if(circular_buffer_empty(a) || a==NULL || a->capacity<1 || a->end<0 || a->begin<0 ||a->ptr == NULL)return;
  int x;
  int le;
  if(a->begin>a->end)le = a->end+a->capacity-a->begin;
  else if(a->full)le = a->capacity;
  else{le = a->end-a->begin;}
  for(int i=0;i<le;i++){
    x = (a->begin+i)%(a->capacity);
    printf("%d ",*(a->ptr+x));
  }
}


