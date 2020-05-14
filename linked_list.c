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

List_ptr filter(List_ptr list, Predicate predicate)
{
  List_ptr new_list = create_list();
  Node_ptr p_walker = list->first;

  for (size_t i = 0; i < list->length; i++)
  {
    if ((*predicate)(p_walker->element))
    {
      add_to_list(new_list, p_walker->element);
    }
    p_walker = p_walker->next;
  }

  return new_list;
}

Element reduce(List_ptr list, Element initial_element, Reducer reducer)
{
  Element result = initial_element;
  Node_ptr p_walker = list->first;

  for (size_t i = 0; i < list->length; i++)
  {
    result = (*reducer)(result, p_walker->element);
    p_walker = p_walker->next;
  }

  return result;
}

void forEach(List_ptr list, ElementProcessor processor)
{
  Node_ptr p_walker = list->first;
  for (size_t i = 0; i < list->length; i++)
  {
    (*processor)(p_walker->element);
    p_walker = p_walker->next;
  }
}

Element remove_at(List_ptr list, int position)
{
  if (position >= list->length || position < 0)
  {
    return NULL;
  }

  Prev_Current_Pair pre_current_pair;
  pre_current_pair.prev = NULL;
  pre_current_pair.current = list->first;
  while (position > 0)
  {
    pre_current_pair.prev = pre_current_pair.current;
    pre_current_pair.current = pre_current_pair.current->next;
    position--;
  }

  Node_ptr node_to_remove = pre_current_pair.current;
  Node_ptr *ptr_to_set = &list->first;

  if (pre_current_pair.prev != NULL)
  {
    ptr_to_set = &pre_current_pair.prev->next;
  }

  *ptr_to_set = pre_current_pair.current->next;

  if (pre_current_pair.current->next == NULL)
  {
    list->last = pre_current_pair.prev;
  }

  list->length--;
  Element removed_element = node_to_remove->element;
  free(node_to_remove);
  return removed_element;
}

Element remove_from_start(List_ptr list)
{
  return remove_at(list, 0);
}

Element remove_from_end(List_ptr list)
{
  return remove_at(list, list->length - 1);
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walker = list->first;
  for (size_t i = 0; i < list->length; i++)
  {
    if ((*matcher)(p_walker->element, element))
    {
      return remove_at(list, i);
    }
    p_walker = p_walker->next;
  }
  return NULL;
}

List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher)
{
  List_ptr removed_element_list = create_list();

  Prev_Current_Pair pair;
  pair.current = list->first;
  pair.prev = NULL;

  Element removed_element;

  while (pair.current != NULL)
  {
    pair.prev = pair.current;
    pair.current = pair.current->next;
    if ((*matcher)(pair.prev->element, element))
    {
      removed_element = remove_first_occurrence(list, element, matcher);
      add_to_list(removed_element_list, removed_element);
    }
  }

  return removed_element_list;
}

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Status status;
  Node_ptr p_walker = list->first;
  while (p_walker != NULL)
  {
    if ((*matcher)(p_walker->element, element))
    {
      return Failure;
    }
    p_walker = p_walker->next;
  }
  status = add_to_list(list, element);
  return status;
}

Status clear_list(List_ptr list)
{
  if (list->length == 0)
  {
    return Failure;
  }

  Element element_to_remove;
  Node_ptr p_walker = list->first;

  while (p_walker != NULL)
  {
    p_walker = p_walker->next;
    element_to_remove = remove_from_start(list);
    free(element_to_remove);
  }
  return Success;
}