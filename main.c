#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void print_number(Element element)
{
  if (element == NULL)
  {
    printf("number not found\n");
    return;
  }
  printf("%d\n", *(Int_Ptr)element);
}

Element give_double_of(Element element)
{
  Int_Ptr double_of_number = (Int_Ptr)malloc(sizeof(int));
  *double_of_number = *(Int_Ptr)element * 2;
  return double_of_number;
}

Status is_even(Element element)
{
  if (*(Int_Ptr)element % 2 == 0)
  {
    return Success;
  }
  return Failure;
}

Element add_numbers(Element num1, Element num2)
{
  Int_Ptr sum = (Int_Ptr)malloc(sizeof(int));
  *sum = *(Int_Ptr)num1 + *(Int_Ptr)num2;
  return sum;
}

Status are_numbers_equal(Element num1, Element num2)
{
  if (*(Int_Ptr)num1 == *(Int_Ptr)num2)
  {
    return Success;
  }
  return Failure;
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

  List_ptr even_numbers = filter(list, &is_even);
  printf("even numbers(filter)\n");
  display_list(even_numbers, &print_number);

  Int_Ptr init = malloc(sizeof(int));
  *init = 0;
  Element sum_of_numbers = reduce(list, init, &add_numbers);
  printf("sum of numbers of list(reduce)\n");
  printf("%d\n", *(Int_Ptr)sum_of_numbers);

  printf("printing numbers of list(for_each)\n");
  forEach(list, &print_number);

  Int_Ptr number_to_remove = malloc(sizeof(int));
  *number_to_remove = 4;
  Element removed_element = remove_first_occurrence(list, number_to_remove, &are_numbers_equal);
  printf("removed element(remove_fist_occurrence)\n");
  print_number(removed_element);

  *number_to_remove = 5;
  List_ptr removed_elements_list = remove_all_occurrences(list, number_to_remove, &are_numbers_equal);
  printf("removed elements list(remove_all_occurrences)\n");
  display_list(removed_elements_list, print_number);

  Int_Ptr number_to_add = malloc(sizeof(int));
  *number_to_add = 100;
  status = add_unique(list, number_to_add, &are_numbers_equal);
  printf("adding unique number to the list(add_unique)\n");
  forEach(list, &print_number);

  status = clear_list(list);
  printf("list after clearing(clear_list)\n");
  forEach(list, &print_number);
  return 0;
}
