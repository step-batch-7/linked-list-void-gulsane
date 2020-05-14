#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void print_number(Element element)
{
  printf("%d\n", *(Int_Ptr)element);
}

int main()
{
  Int_Ptr number;
  List_ptr list = create_list();
  Status status;
  for (size_t i = 0; i < 10; i++)
  {
    number = (Int_Ptr)malloc(sizeof(int));
    *number = i + 1;
    status = add_to_list(list, number);
  }
  display_list(list, &print_number);
  return 0;
}
