#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"


int main(){
  struct circular_buffer_t *a;
  int N,e,w,liczba;
  printf("Podaj rozmiar bufora:");
  if(!scanf("%d",&N)){
    printf("Incorrect input");
    return 1;
  }
  if(N<1){
    printf("Incorrect input data");
    return 2;
  }
  e=circular_buffer_create_struct(&a, N);
	if(e!=0){
    printf("Failed to allocate memory");
    return 8;
  }
  do{
    printf("Co chcesz zrobic?");
    if(!scanf("%d",&w)){
      circular_buffer_destroy_struct(&a);
      printf("Incorrect input");
      return 1;
    }

    if(w==1){
      printf("Podaj liczbe");
      if(!scanf("%d",&liczba)){
      circular_buffer_destroy_struct(&a);
      printf("Incorrect input");
      return 1;
    }
      if(circular_buffer_push_back(a,liczba)){
         circular_buffer_destroy_struct(&a);
         printf("Incorrect input");
          return 1;
      }

    }
    else if(w==2){
      liczba=circular_buffer_pop_back(a, &e);
      if(e==2){
        printf("Buffer is empty\n");
      }
      else{printf("%d\n",liczba);}
    }

    else if(w==3){
      liczba=circular_buffer_pop_front(a, &e);
      if(e==2){
        printf("Buffer is empty\n");
      }
      else{printf("%d\n",liczba);}
    }
    else if(w==4){
      if(!circular_buffer_empty(a) || circular_buffer_full(a)){
      circular_buffer_display(a);
      }
      else {printf("Buffer is empty");}
      printf("\n");
    }
    else if(w==5){
      liczba = circular_buffer_empty(a);
      printf("%d\n",liczba);
    }
    else if(w==6){
      liczba = circular_buffer_full(a);
      printf("%d\n",liczba);
    }
    else if(w==0)break;
    else{printf("Incorrect input data\n");}

  }while(w!=0);

  circular_buffer_destroy_struct(&a);
  return 0;
}
