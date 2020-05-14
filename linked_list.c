#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

List_ptr create_list(void)
{
  List_ptr new_list = (List_ptr)malloc(sizeof(LinkedList));
  new_list->first = NULL;
  new_list->last = NULL;
  new_list->length = 0;
  return new_list;
}

Node_ptr create_node(Element element)
{
  Node_ptr new_node = (Node_ptr)malloc(sizeof(Node));
  new_node->element = element;
  new_node->next = NULL;
  return new_node;
}

void display_list(List_ptr list, Displayer displayer)
{
  Node_ptr p_walker = list->first;
  for (size_t i = 0; i < list->length; i++)
  {
    (*displayer)(p_walker->element);
    p_walker = p_walker->next;
  }
}

Status add_to_list(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  if (list->first == NULL)
  {
    list->first = new_node;
  }
  else
  {
    list->last->next = new_node;
  }
  list->last = new_node;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  Node_ptr second_node = list->first;
  list->first = new_node;
  if (list->last == NULL)
  {
    list->last = new_node;
  }
  list->first->next = second_node;
  list->length++;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position)
{
  if (position < 0 || position > list->length)
  {
    return Failure;
  }
  Node_ptr new_node = create_node(element);
  Prev_Current_Pair prev_current_pair;
  prev_current_pair.current = list->first;
  prev_current_pair.prev = NULL;

  while (position != 0)
  {
    prev_current_pair.prev = prev_current_pair.current;
    prev_current_pair.current = prev_current_pair.current->next;
    position--;
  }

  if (prev_current_pair.prev == NULL)
  {
    return add_to_start(list, element);
  }

  prev_current_pair.prev->next = new_node;
  new_node->next = prev_current_pair.current;
  list->length++;
  return Success;
}

List_ptr reverse(List_ptr list)
{
  List_ptr reverse_list = create_list();
  Node_ptr p_walker = list->first;

  for (size_t i = 0; i < list->length; i++)
  {
    add_to_start(reverse_list, p_walker->element);
    p_walker = p_walker->next;
  }

  return reverse_list;
}

List_ptr map(List_ptr list, Mapper mapper)
{
  List_ptr new_list = create_list();
  Node_ptr p_walker = list->first;
  for (size_t i = 0; i < list->length; i++)
  {
    add_to_list(new_list, (*mapper)(p_walker->element));
    p_walker = p_walker->next;
  }
  return new_list;
}
