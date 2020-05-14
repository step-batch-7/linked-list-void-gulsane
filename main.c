#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void print_number(Element element)
{
  printf("%d\n", *(Int_Ptr)element);
}

Element give_double_of(Element element)
{
  Int_Ptr double_of_number = (Int_Ptr)malloc(sizeof(int));
  *double_of_number = *(Int_Ptr)element * 2;
  return double_of_number;
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

  List_ptr double_of_numbers = map(list, &give_double_of);
  printf("double of numbers(mapping)\n");
  display_list(double_of_numbers, &print_number);
  return 0;
}
