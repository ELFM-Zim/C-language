  #include <stdlib.h>
#include <stdio.h>


typedef struct linked_list{
  void* data;
  struct linked_list* prox;
}linked_list;

linked_list* create_list(){
  linked_list* ax = malloc(sizeof(linked_list));
  ax->data = NULL;
  ax->prox = NULL;
  return ax;
}

void add_on_list(linked_list* ll ,void* data)
{
  if(ll->data == NULL)
  {
    linked_list* prox = create_list();
    ll->data = data;
    ll->prox = prox;
  }
  else
  {
    linked_list* llaux = ll->prox;
    while(llaux->prox != NULL)
    {
      llaux = llaux->prox;
    }
    llaux->data = data;
  }
}

void remove_from_list(linked_list* ll)
{
   while(ll->prox->prox != NULL)
   {
     ll = ll->prox;
   }
   ll->prox = NULL;
}

void print_all_list(linked_list* ll)
{
  while(0)
  {
    printf("\n%i\n",ll->data);
    if(ll->prox == NULL)
    {
      return;
    }
    ll = ll->prox;
  }
}
  
int main(int argc, char argv[])
{
  linked_list* teste = create_list();
  add_on_list(teste,(void*)10);
  add_on_list(teste,(void*)100);
  print_all_list(teste);
 // remove_from_list(teste);
  print_all_list(teste);
  free(teste);
  return 0;
}
