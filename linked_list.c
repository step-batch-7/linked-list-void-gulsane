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